/**
  ******************************************************************************
  * 文件名 ：   at_command_firmware
  * 作者   ：   Ai Thinker
  * 版本   ：   V4.18_P1.0.0
  * 时间   ：   
  * 文件描述：

*******************************************************************************/
#include "bsp.h"		

#define FIRMWARE_VERSION	"V4.18_P1.1.0"

#define RX_TIMEOUT_ENABLE 1
#define POWER_OFFSET 			27

// 配置数据结构
typedef struct {
    PAN312xRadioInit RadioInit;
		uint8_t tx_mode;
		uint8_t rf_mode;
		uint16_t tx_period;
		uint16_t crc;
} DeviceConfig;

// 全局配置实例
DeviceConfig device_config;

// Flash存储地址定义
#define CONFIG_FLASH_ADDR  0x0800FC00  // 最后一页起始地址
#define CONFIG_FLASH_SIZE  sizeof(DeviceConfig)
	
void DeviceConfig_Init(DeviceConfig *config);
bool DeviceConfig_Save(DeviceConfig *config);
bool DeviceConfig_Load(DeviceConfig *config);
bool DeviceConfig_IsValid(DeviceConfig *config);
uint16_t DeviceConfig_CalculateCRC(DeviceConfig *config);

/********************************************************************************/
//PAN312xRadioInit RadioInit = {
//	433000000,
//	0,
//	0,
//	MOD_2FSK,
//	50000,
//	25000,
//	25000,
//	POWER_LDO_0402,		//DCDC模式下，功率最大13dBm，Ldo模式，功率最大20dBm
//	POWER_20dBm,
//};


PAN312xCrcInit CrcInit = {
	CRC_MODE_16_BIT,
	0x90d9,//0x8005,
	0x0000,//0xffff,
	CRC_BIT_ORDER_MSB_FIRST,
	CRC_BYTE_MSB_FIRST,
	CRC_RANGE_WHOLE_PAYLOAD,
	S_DISABLE,
};

PAN321xPacketInit PacketInit = {
	4,
	PREAMBLE_0101,
	0,				
	4,
	0x2dd42dd4,
	MANCHESTER_ZeroToTwo,
	S_DISABLE,
	MANCHESTER_ZeroToTwo,
	S_DISABLE,
	MANCHESTER_ZeroToTwo,
	S_DISABLE,
	FEC_HAMING_DISABLE,
	WHITENING_DISABLE,
	DATA_MODE_PACKET,
};

volatile SFlagStatus xTxDoneFlag = S_RESET;
volatile SFlagStatus xRxDoneFlag = S_RESET;
volatile SFlagStatus xAckTimeoutFlag = S_RESET;
uint16_t fwid;
//static int16_t tx_period = 50; //发送的时间间隔


/*
 * tx_mode = 0x00: 表示连续发送
 * tx_mode = 0x01：表示发送1000包数
 * tx_mode = 0x02：表示按一次按键发送一次数据
 */
//volatile uint8_t tx_mode = 0x00;

volatile uint32_t tx_cnt = 0;
volatile uint32_t rx_cnt = 0;
volatile uint32_t rx_error_cnt = 0;
volatile uint32_t tx_total_cnt = 0;
volatile uint8_t trigger_cnt = 0;


volatile uint8_t freq_index = 0;
volatile uint8_t datarate_index = 0;
//0:tx;1:rx
volatile uint8_t rf_mode_index = 0;
//volatile uint8_t rf_mode = 0;
volatile bool wakeup_flag = false;
PAN312xIrqs xIrqStatus;


uint16_t nPayloadLength = 37;

uint8_t vectRxBuffer[255];
uint16_t cRxData;


char buffer[20];


const uint8_t vectExpectBuffer[37]={ 
	0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
    0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,
    0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,
    0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,
    0x24,
};

const uint8_t vectTxBuffer[37]={  
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
    0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,
    0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,
    0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,
    0x24,
}; 

TIM_HandleTypeDef TIM2_InitStruct;
static int wakeup_cnt = 0; 
static bool dcdc_enable = false;

#define WAKE_UP_READY  -1
int rssi_value;
volatile int sleep_mode = WAKE_UP_READY;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(DIO8_GetState() == GPIO_PIN_SET)
    {
				PAN312x_Irq_Get_Status(&xIrqStatus);
        if(xIrqStatus.IRQ_STATUS0_F.IRQ_TX_DONE){
            xTxDoneFlag = S_SET;
				}
        
        if(device_config.rf_mode == 3){
            if(xIrqStatus.IRQ_STATUS1_F.IRQ_ACK_TIMEOUT){
                //printf("Ack Timeout\r\n");
                xTxDoneFlag = S_SET;
                xAckTimeoutFlag = S_SET;
            }
        }
          
        if(xIrqStatus.IRQ_STATUS0_F.IRQ_RX_DONE){
//						printf("IRQ_RX_DONE\r\n");
            xRxDoneFlag = S_SET;   
				}
        
        if(xIrqStatus.IRQ_STATUS0_F.IRQ_RX_CRC_ERROR){
//						printf("IRQ_RX_CRC_ERROR\r\n");
            xRxDoneFlag = S_SET;  
						PAN312x_Irq_Clear_RxCrcError_Status();
				}
				
				if(xIrqStatus.IRQ_STATUS1_F.IRQ_WAKEUP) {
//						printf("IRQ_WAKEUP\r\n ");
						wakeup_flag = true;
						wakeup_cnt = 0;
						HAL_TIM_Base_Stop_IT(&TIM2_InitStruct);
				}
    }
}

/*******************************************************************************************************/

// AT指令缓冲区大小
#define AT_CMD_BUF_SIZE 128

// AT指令响应类型
typedef enum {
    AT_RESPONSE_OK,
    AT_RESPONSE_ERROR,
    AT_RESPONSE_BUSY,
    AT_RESPONSE_NO_RESPONSE
} AT_Response_Type;


// AT指令处理函数指针类型
typedef void (*AT_Command_Handler)(const char* params);

// AT指令表项
typedef struct {
    const char* command;
    AT_Command_Handler handler;
    const char* description;
		bool support_query;           // 是否支持查询(?)
    bool support_execution;       // 是否支持执行(无参数)
    bool support_parameters;      // 是否支持带参数(=)
} AT_Command_Entry;

static void Set_PAN312x_RF_Mode_Config(void);
static void AT_Process_Command(const char* command);
static void AT_Send_Response(AT_Response_Type response, const char* message);
static void AT_Test(const char* params);
static void AT_Help(const char* params);
//static void AT_LED_Control(const char* params);
static void AT_RF_Mode(const char* params);
static void AT_Tx_Mode(const char* params);
static void AT_Toggle_DataRate(const char* params);
static void AT_Toggle_FrequencyBase(const char* params);
static void AT_Toggle_PowerdBm(const char* params);
static void AT_Toggle_PowerSelect(const char* params);
static void AT_Enter_Carrier(const char* params);
static void AT_Clear_Count(const char* params);
static void AT_Sleep_Mode(const char* params);
static void AT_Wake_Up(const char* params);
static void AT_Gpio_Set_Mode(const char* params);
static void AT_Gpio_Write(const char* params);
static void AT_Gpio_Read(const char* params);
static void AT_Config_Save(const char* params);
static void AT_Config_Reset(const char* params);
static void AT_Tx_Period(const char* params);
static void AT_Tx_Stop(const char* params);
static void AT_Tx_Start(const char* params);
//static void AT_CPS_Control(const char* params);
static void AT_Module_Reset(const char* params);
static void AT_Factory_Test_Master(const char* params);
static void AT_Factory_Test_Slave(const char* params);


// AT指令缓冲区
static char at_cmd_buf[AT_CMD_BUF_SIZE];
static uint16_t at_cmd_index = 0;
static bool at_cmd_ready = false;

// AT指令表
static const AT_Command_Entry at_command_table[] = {
    {"AT", AT_Test, "Test connection", false, true, false},
//    {"AT+LED", AT_LED_Control, "Control LED", true, true, true},
		{"AT+TXMODE", AT_Tx_Mode, "Send Data Mode", true, false, true},														//切换发包模式
		{"AT+RFMODE", AT_RF_Mode, "RF Mode", true, false, true},																	//切换Tx，Rx模式
		{"AT+DATARATE", AT_Toggle_DataRate, "Toggle DataRate", true, false, true},								//切换速率
		{"AT+FREQUENCYBASE", AT_Toggle_FrequencyBase, "Toggle FrequencyBase", true, false, true},	//切换频点
		{"AT+POWERDBM", AT_Toggle_PowerdBm, "Toggle PowerdBm", true, false, true},								//切换功率
		{"AT+POWERSELECT", AT_Toggle_PowerSelect, "Toggle PowerSelect", true, false, true},				//切换电感参数
		{"AT+ENTERCARRIER", AT_Enter_Carrier, "Enter Carrier", false, true, false},								//使能单载波模式
		{"AT+CLEARCNT", AT_Clear_Count, "Clear Count", true, false, true},												//清除计数
		{"AT+SLEEPMODE", AT_Sleep_Mode, "Sleep Mode", true, false, true},													//睡眠模式
		{"AT+WAKEUP", AT_Wake_Up, "Sleep WakeUp", false, true, false},														//睡眠唤醒
		{"AT+GPIOMODE", AT_Gpio_Set_Mode, "Set Gpio Mode", true, false, true},										//设置GPIO输入输出
		{"AT+GPIOWRITE", AT_Gpio_Write, "Gpio Write", false, false, true},												//设置GPIO输出电平
		{"AT+GPIOREAD", AT_Gpio_Read, "Gpio Read", false, false, true},														//读取GPIO电平
		{"AT+CONFIGSAVE", AT_Config_Save, "Device Config Save", false, true, false},							//保存配置
		{"AT+CONFIGRESET", AT_Config_Reset, "Device Config Reset", false, true, false},						//恢复出厂配置
		{"AT+TXPERIOD", AT_Tx_Period, "Tx Period", true, false, true},														//切换发包模式
		{"AT+TXSTOP", AT_Tx_Stop, "Tx Stop", false, true, false},																	//暂停发送
		{"AT+TXSTART", AT_Tx_Start, "Tx Start", false, true, false},															//开始发送
//		{"AT+CPSCONTROL", AT_CPS_Control, "GC1131 CPS Control", true, false, true},								//GC1131 CPS Control Logic 
		{"AT+RESET", AT_Module_Reset, "Module_Reset", false, true, false},												//模组复位
		{"AT+FTMASTER", AT_Factory_Test_Master, "Factory Test Master", false, true, false},				//产测主机
		{"AT+FTSLAVE", AT_Factory_Test_Slave, "Factory Test Slave", false, true, false},					//产测从机
    {"AT+HELP", AT_Help, "Show help", false, true, false},
//    {"AT+VERSION", AT_Version, "Get firmware version"},
    {NULL, NULL, NULL, false, false, false}  // 结束标记
};

// AT指令初始化
void AT_Command_Init(void)
{
    at_cmd_index = 0;
    at_cmd_ready = false;
    memset(at_cmd_buf, 0, AT_CMD_BUF_SIZE);
}

// AT指令处理主函数
void AT_Command_Process(void)
{
    uint8_t rx_data[64];
    uint16_t rx_count;
    
    // 从串口缓冲区读取数据
    rx_count = USART1_ReceiveData(rx_data, sizeof(rx_data));
    
    for (uint16_t i = 0; i < rx_count; i++) {
        uint8_t data = rx_data[i];
        
        // 检查是否接收到AT指令结束符
        if (data == '\r' || data == '\n') {
            if (at_cmd_index > 0) {
                at_cmd_buf[at_cmd_index] = '\0';
                at_cmd_ready = true;
                at_cmd_index = 0;
            }
        } else if (at_cmd_index < AT_CMD_BUF_SIZE - 1) {
            at_cmd_buf[at_cmd_index++] = data;
        }
    }
    
    // 处理完整的AT指令
    if (at_cmd_ready) {
        AT_Process_Command(at_cmd_buf);
        at_cmd_ready = false;
        memset(at_cmd_buf, 0, AT_CMD_BUF_SIZE);
    }
}

// 解析并处理AT指令
static void AT_Process_Command(const char* input)
{
		char cmd[32] = {0};
    char params[128] = {0};
    bool is_query = false;
    bool has_params = false;
		
		char temp_buf[128] = {0};
		strcpy(temp_buf, input);
    
    // 跳过前导空格
    while (*input == ' ') input++;
    
    // 提取命令部分 (不区分大小写)
    int i = 0;
    while (*input && *input != '?' && *input != '=' && *input != ' ' && i < sizeof(cmd)-1) {
        cmd[i++] = toupper(*input++);
    }
    cmd[i] = '\0';
    
    // 检查操作符
    if (*input == '?') {
        is_query = true;
        input++;
    } else if (*input == '=') {
        has_params = true;
        input++;
    }
    
    // 提取参数
    if (has_params) {
        i = 0;
        // 跳过空格
        while (*input == ' ') input++;
        
        // 复制参数
        while (*input && *input != '\r' && *input != '\n' && i < sizeof(params)-1) {
            params[i++] = *input++;
        }
        params[i] = '\0';
    }
    
    // 查找匹配的命令
    bool found = false;
    for (int j = 0; at_command_table[j].command != NULL; j++) {
        if (strcmp(cmd, at_command_table[j].command) == 0) {
            found = true;
            
            // 检查指令格式是否支持
            if (is_query && !at_command_table[j].support_query) {
								char response[50] = {0};
								snprintf(response, sizeof(response), "\r\n%s:3",at_command_table[j].command+2);
                AT_Send_Response(AT_RESPONSE_ERROR, response);
                return;
            } else if (!is_query && !has_params && !at_command_table[j].support_execution) {
                char response[50] = {0};
								snprintf(response, sizeof(response), "\r\n%s:3",at_command_table[j].command+2);
                AT_Send_Response(AT_RESPONSE_ERROR, response);
                return;
            } else if (has_params && !at_command_table[j].support_parameters) {
                char response[50] = {0};
								snprintf(response, sizeof(response), "\r\n%s:3",at_command_table[j].command+2);
                AT_Send_Response(AT_RESPONSE_ERROR, response);
                return;
            }
            
            // 调用处理函数
            if (is_query) {
                // 查询操作
                at_command_table[j].handler("?");
            } else if (has_params) {
                // 带参数操作
                at_command_table[j].handler(params);
            } else {
                // 无参数执行
                at_command_table[j].handler("");
            }
            
            break;
        }
    }
    
    if (!found) {
				printf("Unknown cmd:%s",temp_buf);
    }
}


// 发送AT响应
static void AT_Send_Response(AT_Response_Type response, const char* message)
{
		if (message != NULL && strlen(message) > 0) {
        printf("%s", message);
    }
	
    switch (response) {
        case AT_RESPONSE_OK:
            printf("\r\nOK\r\n");
            break;
        case AT_RESPONSE_ERROR:
            printf("\r\nERROR\r\n");
            break;
        case AT_RESPONSE_BUSY:
            printf("\r\nBUSY\r\n");
            break;
        case AT_RESPONSE_NO_RESPONSE:
            printf("\r\nNO RESPONSE\r\n");
            break;
    }
}

// AT测试指令
static void AT_Test(const char* params)
{
//    printf("STM32F103 AT Command Interface Ready");
    AT_Send_Response(AT_RESPONSE_OK, NULL);
}

// 帮助指令
static void AT_Help(const char* params)
{
//    printf("Available AT Commands:\r\n");
    
    for (int i = 0; at_command_table[i].command != NULL; i++) {
        printf("\r\n%s - %s", at_command_table[i].command, at_command_table[i].description);
    }
    
    AT_Send_Response(AT_RESPONSE_OK, NULL);
}

#if 0
// LED控制指令
static void AT_LED_Control(const char* params)
{
    if (strcmp(params, "?") == 0) {
        // 查询LED状态
        printf("LED Status: GREEN=%s, BLUE=%s", 
               bsp_IsLedOn(GREEN_LED) ? "ON" : "OFF", 
               bsp_IsLedOn(BLUE_LED) ? "ON" : "OFF");
        AT_Send_Response(AT_RESPONSE_OK, NULL);
    } else if (strlen(params) == 0) {
        // 切换LED状态
        bsp_LedToggle(GREEN_LED);
        bsp_LedToggle(BLUE_LED);
        AT_Send_Response(AT_RESPONSE_OK, "LEDs toggled");
    } else {
        // 解析参数
        char led[10];
        char state[10];
        
        if (sscanf(params, "%9[^,],%9s", led, state) == 2) {
            // 控制指定LED
            if (strcasecmp(led, "GREEN") == 0) {
                if (strcasecmp(state, "ON") == 0) {
                    bsp_LedOn(GREEN_LED);
                    AT_Send_Response(AT_RESPONSE_OK, "Green LED turned on");
                } else if (strcasecmp(state, "OFF") == 0) {
                    bsp_LedOff(GREEN_LED);
                    AT_Send_Response(AT_RESPONSE_OK, "Green LED turned off");
                } else {
                    AT_Send_Response(AT_RESPONSE_ERROR, "Invalid state");
                }
            } else if (strcasecmp(led, "BLUE") == 0) {
                if (strcasecmp(state, "ON") == 0) {
                    bsp_LedOn(BLUE_LED);
                    AT_Send_Response(AT_RESPONSE_OK, "Blue LED turned on");
                } else if (strcasecmp(state, "OFF") == 0) {
                    bsp_LedOff(BLUE_LED);
                    AT_Send_Response(AT_RESPONSE_OK, "Blue LED turned off");
                } else {
                    AT_Send_Response(AT_RESPONSE_ERROR, "Invalid state");
                }
            } else {
                AT_Send_Response(AT_RESPONSE_ERROR, "Invalid LED selection");
            }
        } else {
            AT_Send_Response(AT_RESPONSE_ERROR, "Invalid parameters");
        }
    }
}

static void __PAN312x_Enter_Status(void)
{
		if (device_config.rf_mode == 1) {
			#ifdef RX_TIMEOUT_ENABLE
				PAN312x_Enter_Rx(0, START_COND_ENABLE_TIMEOUT, nPayloadLength);
			#else
				PAN312x_Enter_Rx(0, 0, nPayloadLength);
			#endif
		} else if (device_config.rf_mode == 4) {
				PAN312x_Enter_Rx(0, START_COND_ENABLE_ACK, nPayloadLength);
		}
}
#endif

static void Set_PAN312x_RF_Mode_Config(void)
{
		if (device_config.rf_mode == 1) {	
				if (dcdc_enable) {
						PAN312x_DCDC_Enable();
				} else {
						PAN312x_DCDC_Disable();
				}
				PAN312x_Set_RxPacket_Config(RxFixedPackedCrcEnable);
				PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE | IRQ_MASK_ACK_TIMEOUT), S_DISABLE);
				PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_RX_DONE | IRQ_MASK_RX_CRC_ERROR |IRQ_MASK_WAKEUP), S_ENABLE);  
				PAN312x_Set_RxTimeOut(400000);	//400ms
				PAN312x_Set_RxTimeout_ExitState(STATE_RX);
				PAN312x_Set_RxInvalid_ExitState(STATE_RX);
				PAN312x_Set_RxValid_ExitState(STATE_RX);
				//PAN312x_Enter_Rx(0, 0, 0);
				#ifdef RX_TIMEOUT_ENABLE
				PAN312x_Enter_Rx(0, START_COND_ENABLE_TIMEOUT, nPayloadLength);
				#else
				PAN312x_Enter_Rx(0, 0, nPayloadLength);			
				#endif
				PAN312x_GC1131_Set_Mode(GC1131_MODE_RECEIVE);
		} else if (device_config.rf_mode == 2) {
				if (dcdc_enable) {
						PAN312x_DCDC_Enable();
				} else {
						PAN312x_DCDC_Disable();
				}
				PAN312x_Set_TxPacket_Config(TxFixedPackedCrcEnable);
				PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE |IRQ_MASK_WAKEUP), S_ENABLE);
				PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_RX_DONE | IRQ_MASK_ACK_TIMEOUT), S_DISABLE);
				PAN312x_GC1131_Set_Mode(GC1131_MODE_TRANSMIT);
		} else if (device_config.rf_mode == 3) {
				if (dcdc_enable) {
						PAN312x_DCDC_Enable();
				} else {
						PAN312x_DCDC_Disable();
				}
				//AutoAck config
				PAN312x_Set_AckTimeOut(400000);	//400ms
				PAN312x_Set_AckTimeout_ExitState(STATE_READY);
				PAN312x_Set_TxPacket_Config(TxFixedPackedCrcEnable);
				PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE|IRQ_MASK_ACK_TIMEOUT |IRQ_MASK_WAKEUP), S_ENABLE);
				PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_RX_DONE), S_DISABLE);
				PAN312x_GC1131_Set_Mode(GC1131_MODE_TRANSMIT);
		} else if (device_config.rf_mode == 4) {
				if (dcdc_enable) {
						PAN312x_DCDC_Enable();
				} else {
						PAN312x_DCDC_Disable();
				}
				PAN312x_Set_AckTxDelay2(120);				
				PAN312x_Set_RxPacket_Config(RxFixedPackedCrcEnable);
				PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE), S_DISABLE);
				PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_RX_DONE | IRQ_MASK_RX_CRC_ERROR |IRQ_MASK_WAKEUP), S_ENABLE);
				PAN312x_Set_RxInvalid_ExitState(STATE_RX);
				PAN312x_Set_RxValid_ExitState(STATE_RX);				
				PAN312x_Enter_Rx(0, START_COND_ENABLE_ACK, nPayloadLength);
				PAN312x_GC1131_Set_Mode(GC1131_MODE_RECEIVE);
		}
}

static void AT_RF_Mode(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
        printf("\r\n+RFMODE: %d", device_config.rf_mode);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
        // 解析参数
        int mode; 
        if (sscanf(params, "%d", &mode) == 1) {
//						PAN312x_RadioInit(&device_config.RadioInit);
            if (mode == 1) {	
								device_config.rf_mode = 1;
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
//								bsp_DelayMS(50);
//								PAN312x_RadioInit(&device_config.RadioInit);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
							
            } else if (mode == 2) {
								device_config.rf_mode = 2;
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
//								bsp_DelayMS(50);
//								PAN312x_RadioInit(&device_config.RadioInit);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
            } else if (mode == 3) {
								device_config.rf_mode = 3;
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
//								bsp_DelayMS(50);
//								PAN312x_RadioInit(&device_config.RadioInit);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
            } else if (mode == 4) {
								device_config.rf_mode = 4;
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
//								bsp_DelayMS(50);
//								PAN312x_RadioInit(&device_config.RadioInit);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
            } else {
                AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+RFMODE:4");
            }
        } else {
            AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+RFMODE:3");
        }
    }
}

static void AT_Tx_Mode(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		
		if (strcmp(params, "?") == 0) {
        printf("\r\n+TXMODE: %d", device_config.tx_mode);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
				if((device_config.rf_mode != 2) && (device_config.rf_mode != 3)){
						AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+TXMODE:2");
						return;
				}
				
        // 解析参数
        int mode;
        if (sscanf(params, "%d", &mode) == 1) {
            if (mode == 0) {	
								tx_cnt = 0;
								device_config.tx_mode = 0x00;
								bsp_StartTimer(1, device_config.tx_period);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
            } else if (mode == 1) {
								tx_cnt = 0;
								rx_error_cnt = 0;
								tx_total_cnt = 0;
								device_config.tx_mode = 0x01;
								bsp_StartTimer(1, device_config.tx_period);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
            } else if (mode == 2) {
								device_config.tx_mode = 0x02;
								bsp_StartTimer(1, device_config.tx_period);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
            } else {
                AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+TXMODE:4");
            }
        } else {
            AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+TXMODE:3");
        }
    }
}

static void AT_Toggle_DataRate(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
        printf("\r\n+DATARATE:%"PRIu32" ", device_config.RadioInit.DataRate);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
        // 解析参数
        uint32_t rate;
        
        if (sscanf(params, "%" PRIu32 , &rate) == 1) {
						if (rate == 50000 || rate == 62500 || rate == 80000 || rate == 100000 || rate == 125000 ||  
							  rate == 200000 || rate == 250000 || rate == 400000 || rate == 500000 ) {		
								device_config.RadioInit.DataRate = rate;					
								if(device_config.RadioInit.DataRate >= 20000){
										device_config.RadioInit.RxDeviation = device_config.RadioInit.DataRate / 2;
										device_config.RadioInit.TxDeviation = device_config.RadioInit.DataRate / 2;
								} else{
										device_config.RadioInit.RxDeviation = 10000;
										device_config.RadioInit.TxDeviation = 10000;
								}
								PAN312x_RadioInit(&device_config.RadioInit);	
//								__PAN312x_Enter_Status();
								Set_PAN312x_RF_Mode_Config();
								AT_Send_Response(AT_RESPONSE_OK, NULL);
						} else {
								AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+DATARATE:4");
						}
        } else {
            AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+DATARATE:3");
        }
    }
}

static void AT_Toggle_FrequencyBase(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
        printf("\r\n+FREQUENCYBASE:%"PRIu32"", device_config.RadioInit.FrequencyBase);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
        // 解析参数
        uint32_t frequency;
        
        if (sscanf(params, "%" PRIu32 , &frequency) == 1) {
						if (frequency > 0 && frequency < 4294967295) {			
								device_config.RadioInit.FrequencyBase = frequency;	
								PAN312x_RadioInit(&device_config.RadioInit);
//								__PAN312x_Enter_Status();
								Set_PAN312x_RF_Mode_Config();
								AT_Send_Response(AT_RESPONSE_OK, NULL);
						} else {
								AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+FREQUENCYBASE:4");
						}
        } else {
            AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+FREQUENCYBASE:3");
        }
    }
	
}

static void AT_Toggle_PowerdBm(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
				int power;
				power = (int)(device_config.RadioInit.Power & 0xff) - 20;
        printf("\r\n+POWERDBM:%d", power+POWER_OFFSET);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
        // 解析参数
        int power_dbm;
				uint8_t  new_powerdbm;
        
        if (sscanf(params, "%d", &power_dbm) == 1) {
						if((device_config.RadioInit.PowerSelect == POWER_LDO_0603) || (device_config.RadioInit.PowerSelect == POWER_LDO_0402)) {
								if((power_dbm > 30) || (power_dbm < 7)){
										AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+POWERDBM:4");
								} else {
										power_dbm = power_dbm - POWER_OFFSET;
										new_powerdbm = (power_dbm + 20) & 0xff;
										device_config.RadioInit.Power = (PAN312xPowerdBm)new_powerdbm;
										PAN312x_RadioInit(&device_config.RadioInit);
//										__PAN312x_Enter_Status();
										Set_PAN312x_RF_Mode_Config();
										AT_Send_Response(AT_RESPONSE_OK, NULL);
								}
						} else if ((device_config.RadioInit.PowerSelect == POWER_DCDC_0603) || (device_config.RadioInit.PowerSelect == POWER_DCDC_0402)) {
								if((power_dbm > 30) || (power_dbm < 7)){
										AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+POWERDBM:4");
								}  else {
										power_dbm = power_dbm - POWER_OFFSET;
										new_powerdbm = (power_dbm + 20) & 0xff;
										device_config.RadioInit.Power = (PAN312xPowerdBm)new_powerdbm;
										PAN312x_RadioInit(&device_config.RadioInit);
//										__PAN312x_Enter_Status();
										Set_PAN312x_RF_Mode_Config();
										AT_Send_Response(AT_RESPONSE_OK, NULL);
								}
						} else {
								AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+POWERDBM:4");
						}
        } else {
            AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+POWERDBM:3");
        }
    }
}

#if 1
static void AT_Toggle_PowerSelect(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
        printf("\r\n+POWERSELECT:%d ", (device_config.RadioInit.PowerSelect == POWER_LDO_0402 || device_config.RadioInit.PowerSelect == POWER_LDO_0603) ? 0 : 1);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
        // 解析参数
        int mode;
        
        if (sscanf(params, "%d", &mode) == 1) {
						switch(mode) {
								case 0: {
										device_config.RadioInit.PowerSelect = POWER_LDO_0402;
										dcdc_enable = false;
									break;
								}
								case 1: {
										device_config.RadioInit.PowerSelect = POWER_DCDC_0402;
										dcdc_enable = true;
									break;
								}
								default: {
										AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+POWERDBM:4");
									return;
								}
						}
						PAN312x_RadioInit(&device_config.RadioInit);
//						__PAN312x_Enter_Status();
						Set_PAN312x_RF_Mode_Config();
						AT_Send_Response(AT_RESPONSE_OK, NULL);
        } else {
            AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+POWERDBM:3");
        }
    }
}
#endif

static void AT_Enter_Carrier(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		PAN312x_Enter_Carrier(device_config.RadioInit.FrequencyBase, device_config.RadioInit.FrequencyStep, device_config.RadioInit.FrequencyChannelNumber, device_config.RadioInit.PowerSelect, device_config.RadioInit.Power);
    AT_Send_Response(AT_RESPONSE_OK, NULL);
}

static void AT_Clear_Count(const char* params)
{
		if (strcmp(params, "?") == 0) {
        AT_Send_Response(AT_RESPONSE_OK, NULL);
				printf("\r\n+CLEARCNT:\r\nOk Cnt:%"PRIu16", Err Cnt:%"PRIu16"", tx_cnt, rx_error_cnt);	
    } else {
				int mode = 0;
				if (sscanf(params, "%d", &mode) == 1) {
						if (mode == 1) {
								tx_cnt = 0;
								rx_cnt = 0;
								rx_error_cnt = 0;
								AT_Send_Response(AT_RESPONSE_OK, NULL);
//								printf("Ok Cnt:%" PRIu16 ", Err Cnt:%" PRIu16 "", tx_cnt, rx_error_cnt);
						}	else {
								AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+CLEARCNT:4");
						}
				} else {
						AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+CLEARCNT:3");
				}
		}
}

static void AT_Sleep_Mode(const char* params)
{
		if (strcmp(params, "?") == 0) {	
				printf("\r\n+SLEEPMODE:%s", sleep_mode < 0 ? "WAKE_UP_READY" : (sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode"));	
				AT_Send_Response(AT_RESPONSE_OK, NULL);	
    } else {
					if (sleep_mode == WAKE_UP_READY) {
						int mode = 0;
						if (sscanf(params, "%d", &mode) == 1) {
								if (mode != 0 && mode != 1) {
										AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+SLEEPMODE:4");
										return;
								}
								if (dcdc_enable) {
										PAN312x_DCDC_Disable();
								}
								PAN312x_GC1131_Set_Mode(GC1131_MODE_SHUTDOWN);
								switch (mode) {
										case 0: {
												sleep_mode = SLEEP_MODE;
												PAN312x_Enter_Sleep(SLEEP_MODE, WAKE_UP_STATE_READY);
												break;
										} 
										case 1: {
												sleep_mode = DEEP_SLEEP_MODE;
												PAN312x_Enter_Sleep(DEEP_SLEEP_MODE, WAKE_UP_STATE_READY);
												break;
										}
										default: {
												AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+SLEEPMODE:4");
												return;
										}
								}	
								bsp_DelayUS(120);   
								PAN312x_ClkRcl_Disable();	 
								PAN312x_Set_AllGPIO_Analog();
		//						bsp_DelayMS(100);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
						}	else {
								AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+SLEEPMODE:3");
						}
				} else {
						printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
						AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				}
		}
}

static void AT_Wake_Up(const char* params)
{	
		if (sleep_mode == SLEEP_MODE || sleep_mode == DEEP_SLEEP_MODE) {
				
				PAN312x_SPI_Init();
				PAN312x_DIO8_INPUT();
				DIO8_EnableInterrupt();
				
				bsp_DelayUS(120);
				uint8_t rf_status;
				//判断下PAN312x是否处于sleep模式或deepsleep模式
				PAN312x_Read(R003, &rf_status);
		//						printf("rf status: %x\r\n", rf_status);
				if((rf_status == 0x01) || (rf_status == 0x02)){
						//表示PAN312x处于deepsleep 或者sleep模式
						//执行唤醒指令，将PAN312x唤醒
						PAN312x_ClkRcl_Enable();
						PAN312x_WakeUp_BySpi();
				}
				HAL_TIM_Base_Start_IT(&TIM2_InitStruct);
				
		} else {		
				wakeup_flag = false; 
				sleep_mode = WAKE_UP_READY;
				AT_Send_Response(AT_RESPONSE_OK, NULL);
		}
}

//typedef enum {
//    GPIO_MODE_UNKNOWN = 0,
//    GPIO_MODE_INPUT,
//    GPIO_MODE_OUTPUT
//} PAN312xGpioMode;

#define GPIO_MODE_UNKNOWN 0

// 添加读取函数声明
uint8_t PAN312x_Get_Gpio_Mode(uint16_t GpioPin);

// 读取单个GPIO引脚的模式
uint8_t PAN312x_Get_Gpio_Mode(uint16_t GpioPin)
{
    uint8_t tmp;
		uint8_t GpioPin0_2_11 = 0x00,GpioPin3_10 = 0x00;
    uint16_t mode = GPIO_MODE_UNKNOWN;
    
    // 分离低8位和高8位引脚
    GpioPin0_2_11 = (uint8_t)GpioPin;
    GpioPin3_10 = (uint8_t)(GpioPin >> 8);
//		printf("GpioPin0_2_11:%" PRIu8 ", GpioPin3_10:%" PRIu8 "\r\n", GpioPin0_2_11, GpioPin3_10);
    
    // 检查引脚是否有效
    if (!GpioPin0_2_11 && !GpioPin3_10) {
        return GPIO_MODE_UNKNOWN;
    }
    
    // 处理低8位引脚 (GPIO0, GPIO1, GPIO2, GPIO11)
    if (GpioPin0_2_11) {
        // 读取R1B0寄存器 (0x1B0)
        PAN312x_Get_OP_Reg(R1B0, 1, &tmp);
        
        // 检查每个引脚的模式
        if (GpioPin0_2_11 & PAN312x_GPIO_PIN_0) {
            if (tmp & (1 << 4)) {
								mode = GPIO_OUTPUT_MODE;
						} else if (tmp & (1 << 0)) {
								mode = GPIO_INPUT_MODE;
						}
        } else if (GpioPin0_2_11 & PAN312x_GPIO_PIN_1) {
            if (tmp & (1 << 5)) {
								mode = GPIO_OUTPUT_MODE;
						} else if (tmp & (1 << 1)) {
								mode = GPIO_INPUT_MODE;
						}
        } else if (GpioPin0_2_11 & PAN312x_GPIO_PIN_2) {
            if (tmp & (1 << 6)) {
								mode = GPIO_OUTPUT_MODE;
						} else if (tmp & (1 << 2)) {
								mode = GPIO_INPUT_MODE;
						}
        }
    }
    
    // 处理高8位引脚 (GPIO3-GPIO10)
    if (GpioPin3_10) {
        uint8_t input_enable = 0;
        uint8_t output_enable = 0;
        
        // 读取输入使能寄存器 (R018)
        PAN312x_Get_OP_Reg(R018, 1, &input_enable);
        
        // 读取输出使能寄存器 (R019)
        PAN312x_Get_OP_Reg(R019, 1, &output_enable);
        
        // 检查每个引脚的模式
				if (GpioPin3_10 & 1 << 6) {
						if (output_enable & 1 << 6) {
								mode = GPIO_OUTPUT_MODE;
						} else if (input_enable & 1 << 6) {
								mode = GPIO_INPUT_MODE;
						}
				} else if (GpioPin3_10 & 1 << 7) {
						if (output_enable & 1 << 7) {
								mode = GPIO_OUTPUT_MODE;
						} else if (input_enable & 1 << 7) {
								mode = GPIO_INPUT_MODE;
						}
				}
				
//        for (int i = 0; i < 8; i++) {
//            uint8_t pin_mask = 1 << i;
//            if (GpioPin3_10 & pin_mask) {
//                if (output_enable & pin_mask) {
//                    mode = GPIO_OUTPUT_MODE;
//                } else if (input_enable & pin_mask) {
//                    mode = GPIO_INPUT_MODE;
//                }
//            }
//        }
    }
    
    return mode;
}

static void AT_Gpio_Set_Mode(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
				uint8_t pin0_mode = PAN312x_Get_Gpio_Mode(PAN312x_GPIO_PIN_0);
				uint8_t pin1_mode = PAN312x_Get_Gpio_Mode(PAN312x_GPIO_PIN_1);
				uint8_t pin10_mode = PAN312x_Get_Gpio_Mode(PAN312x_GPIO_PIN_10);
				printf("\r\n+GPIOMODE:");
				printf("\r\npin0:%s", pin0_mode == GPIO_MODE_UNKNOWN ? "GPIO_MODE_UNKNOWN" : (pin0_mode == 0x01 ? "GPIO_OUTPUT_MODE" : "GPIO_INPUT_MODE") );
				printf("\r\npin1:%s", pin1_mode == GPIO_MODE_UNKNOWN ? "GPIO_MODE_UNKNOWN" : (pin1_mode == 0x01 ? "GPIO_OUTPUT_MODE" : "GPIO_INPUT_MODE") );
				printf("\r\npin10:%s", pin10_mode == GPIO_MODE_UNKNOWN ? "GPIO_MODE_UNKNOWN" : (pin10_mode == 0x01 ? "GPIO_OUTPUT_MODE" : "GPIO_INPUT_MODE") );
        AT_Send_Response(AT_RESPONSE_OK, NULL);
				return;
    } else {
        // 解析参数
        int gpio_pin;
				int gpio_mode;
        
        if (sscanf(params, "%d,%d", &gpio_pin, &gpio_mode) == 2) {
						if (gpio_mode != 1 && gpio_mode != 2) {
								AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOMODE:4");
								return;
						}

						if (gpio_pin == 0) {
								if (gpio_mode == 1) {
									PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_0, GPIO_OUTPUT_MODE);
								} else if (gpio_mode == 2) {
									PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_0, GPIO_INPUT_MODE);
								}
						}	else if (gpio_pin == 1) {
								if (gpio_mode == 1) {
									PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_1, GPIO_OUTPUT_MODE);
								} else if (gpio_mode == 2) {
									PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_1, GPIO_INPUT_MODE);
								}
						}	else if (gpio_pin == 10) {
								if (gpio_mode == 1) {
									PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_10, GPIO_OUTPUT_MODE);
								} else if (gpio_mode == 2) {
									PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_10, GPIO_INPUT_MODE);
								}
						} else {
								AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOMODE:4");
								return;
						}
						AT_Send_Response(AT_RESPONSE_OK, NULL);
        } else {
						AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOMODE:3");
				}
    }
}

static void AT_Gpio_Write(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		
		int gpio_pin;
		int gpio_level;
		if (sscanf(params, "%d,%d", &gpio_pin, &gpio_level) == 2) {
				if (gpio_level != 0 && gpio_level != 1) {
						AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOWRITE:4");
						return;
				}
				
				if (gpio_pin == 0) {
						PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_0, GPIO_OUTPUT_MODE);
						if (gpio_level == 0) {
							PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_0, 0);
						} else if (gpio_level == 1) {
							PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_0, 1);
						}
				}	else if (gpio_pin == 1) {
						PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_1, GPIO_OUTPUT_MODE);
						if (gpio_level == 0) {
							PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_1, 0);
						} else if (gpio_level == 1) {
							PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_1, 1);
						}
				}	else if (gpio_pin == 2) {
						PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_2, GPIO_OUTPUT_MODE);
						if (gpio_level == 0) {
							PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_2, 0);
						} else if (gpio_level == 1) {
							PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_2, 1);
						}
				}	else if (gpio_pin == 10) {
						PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_10, GPIO_OUTPUT_MODE);
						if (gpio_level == 0) {
							PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_10, 0);
						} else if (gpio_level == 1) {
							PAN312x_Gpio_Write_Pin(PAN312x_GPIO_PIN_10, 1);
						}
				} else {
						AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOWRITE:4");
						return;
				}
				AT_Send_Response(AT_RESPONSE_OK, NULL);
		} else {
				AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOWRITE:3");
		}
}

static void AT_Gpio_Read(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		
		int gpio_pin;
		uint8_t gpio_level;
		if (sscanf(params, "%d", &gpio_pin) == 1) {
				if (gpio_pin == 0) {
						gpio_level = PAN312x_Gpio_Read_Pin(PAN312x_GPIO_PIN_0);
						printf("\r\n+GPIOREAD:0,%x", gpio_level);
				} else if (gpio_pin == 1) {
						gpio_level = PAN312x_Gpio_Read_Pin(PAN312x_GPIO_PIN_1);
						printf("\r\n+GPIOREAD:1,%x", gpio_level);
				} else if (gpio_pin == 2) {
						gpio_level = PAN312x_Gpio_Read_Pin(PAN312x_GPIO_PIN_2);
						printf("\r\n+GPIOREAD:2,%x", gpio_level);
				} else if (gpio_pin == 10) {
						gpio_level = PAN312x_Gpio_Read_Pin(PAN312x_GPIO_PIN_10);
						printf("\r\n+GPIOREAD:10,%x", gpio_level);
				} else {
						AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOREAD:4");
						return;
				}
				AT_Send_Response(AT_RESPONSE_OK, NULL);
		} else {
				AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOREAD:3");
		}

}

static void AT_Config_Save(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		
		if (DeviceConfig_Save(&device_config)) {
//				PAN312x_RadioInit(&device_config.RadioInit);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
				bsp_DelayMS(100);
				HAL_NVIC_SystemReset();
    } else {
				AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+CONFIGSAVE:32");
    }

}

static void AT_Config_Reset(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		
		DeviceConfig_Init(&device_config);
		if (DeviceConfig_Save(&device_config)) {
//				PAN312x_RadioInit(&device_config.RadioInit);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
				bsp_DelayMS(100);
				HAL_NVIC_SystemReset();
    } else {
				AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+CONFIGRESET:32");
    }
}

static void AT_Tx_Period(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
				printf("\r\n+TXPERIOD:%"PRIu16"", device_config.tx_period);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
				return;
    } else {
        // 解析参数
        uint16_t number;
        
        if (sscanf(params, "%hu", &number) == 1) {
						if (number > 0 && number < 65535) {
								bsp_StopTimer(1);
								device_config.tx_period = number;
//								bsp_StartTimer(1,device_config.tx_period);
						}	else {
								AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOMODE:4");
								return;
						}
						AT_Send_Response(AT_RESPONSE_OK, NULL);
        } else {
						AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOMODE:3");
				}
    }
}

static void AT_Tx_Stop(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		
		bsp_StopTimer(1);
		AT_Send_Response(AT_RESPONSE_OK, NULL);
}

static void AT_Tx_Start(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		
		if(device_config.tx_mode == 0x01){
				//发送500次
				if(tx_total_cnt == 500) {
						//针对TRxMaster的
						tx_cnt = 0;
						rx_error_cnt = 0;
						tx_total_cnt = 0;
				} else if(tx_cnt == 500) {
						//针对Tx的
						tx_cnt = 0;
						rx_error_cnt = 0;
						tx_total_cnt = 0;
				}
		}
		bsp_StartTimer(1, device_config.tx_period);
		AT_Send_Response(AT_RESPONSE_OK, NULL);
}

static void AT_Module_Reset(const char* params)
{
		AT_Send_Response(AT_RESPONSE_OK, NULL);
		bsp_DelayMS(100);
		HAL_NVIC_SystemReset();
}

#if 0
static void AT_CPS_Control(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		
		if (strcmp(params, "?") == 0) {
				printf("\r\n+CPSCONTROL:%d", Get_CPS_Level());
        AT_Send_Response(AT_RESPONSE_OK, NULL);
				return;
    } else {
        // 解析参数
        int gpio_level;
        
        if (sscanf(params, "%d", &gpio_level) == 1) {
						if (gpio_level == 0) {
								GC1131_CPS_Off();
						}	else if (gpio_level == 1) {
								GC1131_CPS_On();
						}	else {
								AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOMODE:4");
								return;
						}
						AT_Send_Response(AT_RESPONSE_OK, NULL);
        } else {
						AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+GPIOMODE:3");
				}
    }
}
#endif

static void AT_Factory_Test_Master(const char* params)
{
				// 首先清零整个结构体（包括填充字节）
    memset(&device_config, 0, sizeof(DeviceConfig));
	
    device_config.RadioInit.FrequencyBase = 491300000;
//    device_config.RadioInit.FrequencyStep = 0;
//    device_config.RadioInit.FrequencyChannelNumber = 0;
//    device_config.RadioInit.ModulationSelect = MOD_2FSK;
    device_config.RadioInit.DataRate = 10000;
    device_config.RadioInit.TxDeviation = 10000;
    device_config.RadioInit.RxDeviation = 10000;
    device_config.RadioInit.PowerSelect = POWER_LDO_0402;
    device_config.RadioInit.Power = POWER_20dBm;
    device_config.tx_mode = 2;
    device_config.rf_mode = 2;
		device_config.tx_period = 250;
	
		PAN312x_RadioInit(&device_config.RadioInit);
		Set_PAN312x_RF_Mode_Config();
		bsp_StartTimer(2,device_config.tx_period);
		bsp_StartTimer(1,5*1000);
	
		bsp_LedOff(BLUE_LED);
		bsp_LedOff(GREEN_LED);
	
		while(1) {
				if((device_config.rf_mode == 1) || (device_config.rf_mode == 4)) {
						if(xRxDoneFlag){
								bsp_LedOn(BLUE_LED);
								xRxDoneFlag = S_RESET;
								rssi_value = PAN312x_GetRSSI();
								cRxData = PAN312x_Get_RxLengthInPacket();
								PAN312x_Read_Fifo(vectRxBuffer, cRxData);
								PAN312x_Irq_Clear_RxDone_Status();
								if(memcmp(vectRxBuffer, vectExpectBuffer, cRxData) == 0){
										rx_cnt ++ ;
								}else{
										rx_error_cnt++;
								}
								printf("Master Rx Ok Cnt:%"PRIu16", Err Cnt:%"PRIu16", Rssi:-%d",rx_cnt, rx_error_cnt, rssi_value);
								bsp_DelayMS(100);
								bsp_LedOff(BLUE_LED);
								
								device_config.rf_mode = 2;
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
								bsp_StartTimer(2,device_config.tx_period);
						}
				}
				
				if((device_config.rf_mode == 2) || (device_config.rf_mode == 3)){
						if(bsp_CheckTimer(2)) {
								bsp_LedOn(GREEN_LED);
								DIO8_EnableInterrupt();
								PAN312x_Flush_TxFifo();
								PAN312x_Reset_Modem();
								PAN312x_Write_Fifo((uint8_t *)vectTxBuffer, nPayloadLength);
								if(device_config.rf_mode == 3){
										PAN312x_Enter_Tx(0, START_COND_ENABLE_ACK, nPayloadLength);
								}else{
										PAN312x_Enter_Tx(0, 0, nPayloadLength);
								}
								while(!xTxDoneFlag);
								xTxDoneFlag = S_RESET;
								if(!xAckTimeoutFlag){
										tx_cnt++;
										printf("Master Tx Ok Cnt:%"PRIu16", Err Cnt:%"PRIu16"", tx_cnt, rx_error_cnt);
								}else{
										xAckTimeoutFlag = S_RESET;
										rx_error_cnt++;
										printf("Master Tx Ok Cnt:%"PRIu16", Err Cnt:%"PRIu16"", tx_cnt, rx_error_cnt);
								}
								
								bsp_LedOff(GREEN_LED);
								
								device_config.rf_mode = 1;
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
								bsp_StopTimer(2);
						}
				}
				
				if ((rx_cnt >= 3) && (tx_cnt >= 3)) {
						rx_cnt = 0;
						tx_cnt = 0;
						PAN312x_Enter_Ready();
						bsp_StopTimer(1);
						bsp_StopTimer(2);
						bsp_LedOn(BLUE_LED);
						bsp_LedOn(GREEN_LED);
						AT_Send_Response(AT_RESPONSE_OK, NULL);
						break;
				}
				
				if(bsp_CheckTimer(1)) {
						bsp_StopTimer(1);
						bsp_StopTimer(2);
						AT_Send_Response(AT_RESPONSE_ERROR, "Timeout\r\n");
						break;
				}
		}
}

static void AT_Factory_Test_Slave(const char* params)
{
		printf("Factory Test Slave\r\n");
		// 首先清零整个结构体（包括填充字节）
    memset(&device_config, 0, sizeof(DeviceConfig));
	
    device_config.RadioInit.FrequencyBase = 491300000;
//    device_config.RadioInit.FrequencyStep = 0;
//    device_config.RadioInit.FrequencyChannelNumber = 0;
//    device_config.RadioInit.ModulationSelect = MOD_2FSK;
    device_config.RadioInit.DataRate = 10000;
    device_config.RadioInit.TxDeviation = 10000;
    device_config.RadioInit.RxDeviation = 10000;
    device_config.RadioInit.PowerSelect = POWER_LDO_0402;
    device_config.RadioInit.Power = POWER_20dBm;
    device_config.tx_mode = 2;
    device_config.rf_mode = 1;
		device_config.tx_period = 250;
	
		PAN312x_RadioInit(&device_config.RadioInit);
		Set_PAN312x_RF_Mode_Config();
	
		while(1) {
				if((device_config.rf_mode == 1) || (device_config.rf_mode == 4)) {
						if(xRxDoneFlag){
								bsp_LedOn(BLUE_LED);
								xRxDoneFlag = S_RESET;
								rssi_value = PAN312x_GetRSSI();
								cRxData = PAN312x_Get_RxLengthInPacket();
								PAN312x_Read_Fifo(vectRxBuffer, cRxData);
								PAN312x_Irq_Clear_RxDone_Status();
								if(memcmp(vectRxBuffer, vectExpectBuffer, cRxData) == 0){
										rx_cnt ++ ;
								}else{
										rx_error_cnt++;
								}
								printf("Slave Ok Cnt:%"PRIu16", Err Cnt:%"PRIu16", Rssi:-%d",rx_cnt, rx_error_cnt, rssi_value);
								bsp_DelayMS(100);
								bsp_LedOff(BLUE_LED);
								
								device_config.rf_mode = 2;
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
								bsp_StartTimer(2,device_config.tx_period);
						}
				}
				
				if(bsp_CheckTimer(2)) 
				{
						if((device_config.rf_mode == 2) || (device_config.rf_mode == 3)){
								bsp_LedOn(GREEN_LED);
								DIO8_EnableInterrupt();
								PAN312x_Flush_TxFifo();
								PAN312x_Reset_Modem();
								PAN312x_Write_Fifo((uint8_t *)vectTxBuffer, nPayloadLength);
								if(device_config.rf_mode == 3){
										PAN312x_Enter_Tx(0, START_COND_ENABLE_ACK, nPayloadLength);
								}else{
										PAN312x_Enter_Tx(0, 0, nPayloadLength);
								}
								while(!xTxDoneFlag);
								xTxDoneFlag = S_RESET;
								if(!xAckTimeoutFlag){
										tx_cnt++;
										printf("Slave Ok Cnt:%"PRIu16", Err Cnt:%"PRIu16"", tx_cnt, rx_error_cnt);
								}else{
										xAckTimeoutFlag = S_RESET;
										rx_error_cnt++;
										printf("Slave Ok Cnt:%"PRIu16", Err Cnt:%"PRIu16"", tx_cnt, rx_error_cnt);
								}
								
								bsp_LedOff(GREEN_LED);
								
								device_config.rf_mode = 1;
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
								bsp_StopTimer(2);
						}
						
				}
//				bsp_DelayMS(10);
		}
	
}

/**********************************************************************************************************/

void MX_TIM2_Init_Ms(uint16_t time)
{
    TIM_ClockConfigTypeDef sClockSourceConfig;
    TIM_MasterConfigTypeDef sMasterConfig;
	
    TIM2_InitStruct.Instance = TIM2;
    TIM2_InitStruct.Init.Prescaler = 7200 - 1;
    TIM2_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM2_InitStruct.Init.Period = (time*10) - 1;
    TIM2_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    if (HAL_TIM_Base_Init(&TIM2_InitStruct) != HAL_OK){
        return;
    }

    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&TIM2_InitStruct, &sClockSourceConfig) != HAL_OK){
        return;
    }

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&TIM2_InitStruct, &sMasterConfig) != HAL_OK){
        return;
    }

}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{
    if(tim_baseHandle->Instance == TIM2){
        __HAL_RCC_TIM2_CLK_ENABLE();
        HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);//TM3中断，先优先级0，从优先级0
        HAL_NVIC_EnableIRQ(TIM2_IRQn);//IRQ通道被使能
    }
}


void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{
    if(tim_baseHandle->Instance == TIM2){
        __HAL_RCC_TIM2_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(TIM2_IRQn);
    }
}


/*******************Callback********************/
//定时器返回函数  /* TIM Update event */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		if (wakeup_cnt < 5) {
				wakeup_cnt++;
				uint8_t rf_status;

				PAN312x_SPI_Init();
				PAN312x_DIO8_INPUT();
				DIO8_EnableInterrupt();
				PAN312x_Read(R003, &rf_status);
//				printf("rf status: %x\r\n", rf_status);
				if((rf_status == 0x01) || (rf_status == 0x02)){
						//表示PAN312x处于deepsleep 或者sleep模式
						//执行唤醒指令，将PAN312x唤醒
						PAN312x_ClkRcl_Enable();
						PAN312x_WakeUp_BySpi();
				}
		} else {
				wakeup_cnt = 0;
				AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+WAKEUP:32");
				HAL_TIM_Base_Stop_IT(&TIM2_InitStruct);
		}
}


void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TIM2_InitStruct);
}
/**********************************************************************************************************/

void DeviceConfig_DebugPrint(DeviceConfig *config)
{
    printf("Config Dump:\r\n");
    printf("Size: %u bytes\r\n", sizeof(DeviceConfig));
    printf("FrequencyBase: %u\r\n", config->RadioInit.FrequencyBase);
    printf("DataRate: %u\r\n", config->RadioInit.DataRate);	
    printf("TX Deviation: %u Hz\r\n", config->RadioInit.TxDeviation);
    printf("RX Deviation: %u Hz\r\n", config->RadioInit.RxDeviation);
		printf("PowerSelect: 0x%02X\r\n", (device_config.RadioInit.PowerSelect == POWER_LDO_0402 || device_config.RadioInit.PowerSelect == POWER_LDO_0603) ? 0 : 1);
		printf("Power: %d dBm\r\n", (int)(device_config.RadioInit.Power & 0xff) - 20 + POWER_OFFSET);
		printf("TX Mode: %u\r\n", config->tx_mode);
    printf("RF Mode: %u\r\n", config->rf_mode);
		printf("tx_period: %hu\r\n", config->tx_period);
    printf("CRC: 0x%04X\r\n", config->crc);
    
    // 打印原始字节数据
//    printf("Raw data: ");
//    uint8_t *data = (uint8_t*)config;
//    for (uint32_t i = 0; i < sizeof(DeviceConfig); i++) {
//        printf("%02X ", data[i]);
//        if ((i + 1) % 16 == 0) printf("\r\n");
//    }
    printf("\r\n");
}

// 默认配置
void DeviceConfig_Init(DeviceConfig *config)
{
		// 首先清零整个结构体（包括填充字节）
    memset(config, 0, sizeof(DeviceConfig));
	
    config->RadioInit.FrequencyBase = 490300000;
    config->RadioInit.FrequencyStep = 0;
    config->RadioInit.FrequencyChannelNumber = 0;
    config->RadioInit.ModulationSelect = MOD_2FSK;
    config->RadioInit.DataRate = 50000;
    config->RadioInit.TxDeviation = 25000;
    config->RadioInit.RxDeviation = 25000;
    config->RadioInit.PowerSelect = POWER_DCDC_0402;
    config->RadioInit.Power = POWER_N5dBm;
    config->tx_mode = 2;
    config->rf_mode = 2;
		config->tx_period = 50;
    config->crc = DeviceConfig_CalculateCRC(config);
}

// 保存配置到Flash
bool DeviceConfig_Save(DeviceConfig *config)
{
    // 计算CRC校验值
    config->crc = DeviceConfig_CalculateCRC(config);
    
    // 擦除目标页
    if (Flash_Erase_Page(CONFIG_FLASH_ADDR) != HAL_OK) {
        return false;
    }
    
    // 写入配置数据
    if (Flash_Write_Data(CONFIG_FLASH_ADDR, config, sizeof(DeviceConfig)) != HAL_OK) {
        return false;
    }
		
//		printf("Saving configuration:\r\n");
//		DeviceConfig_DebugPrint(config);
    
    return true;
}

// 从Flash加载配置
bool DeviceConfig_Load(DeviceConfig *config)
{
    // 读取配置数据
    Flash_Read_Data(CONFIG_FLASH_ADDR, config, sizeof(DeviceConfig));
	
		// 调试输出
//    printf("Loaded configuration:\r\n");
//		DeviceConfig_DebugPrint(config);
    
    // 验证数据有效性
    return DeviceConfig_IsValid(config);
}

// 验证配置数据的有效性
bool DeviceConfig_IsValid(DeviceConfig *config)
{
    // 检查Flash是否为空（全为0xFF）
    if (Flash_Is_Empty(CONFIG_FLASH_ADDR, sizeof(DeviceConfig))) {
        return false;
    }
    
    // 检查CRC校验
    uint16_t stored_crc = config->crc;
    uint16_t calculated_crc = DeviceConfig_CalculateCRC(config);
    
    return (stored_crc == calculated_crc);
}

// 计算配置数据的CRC校验值（简单实现）
uint16_t DeviceConfig_CalculateCRC(DeviceConfig *config)
{
		uint16_t crc = 0;
    
    // 创建临时副本，确保不修改原始数据
    DeviceConfig temp_config = *config;
    
    // 将CRC字段清零，确保计算的一致性
    temp_config.crc = 0;
    
    // 计算所有字段的CRC（除了crc字段本身）
    uint8_t *data = (uint8_t*)&temp_config;
    uint32_t size = sizeof(DeviceConfig) - sizeof(temp_config.crc);
    
    for (uint32_t i = 0; i < size; i++) {
        crc += data[i];
    }
    
    return crc;
}

void Init_PAN312x_Gpio_Mode()
{
		PAN312x_Iomux_Gpio(IOMUX_GPIO0_AS_GPIO);
    PAN312x_Iomux_Gpio(IOMUX_GPIO1_AS_GPIO);
    PAN312x_Iomux_Gpio(IOMUX_GPIO10_AS_GPIO);
    PAN312x_Set_Gpio_Mode((PAN312x_GPIO_PIN_0 | PAN312x_GPIO_PIN_1 | PAN312x_GPIO_PIN_10), GPIO_INPUT_MODE);
}

/**********************************************************************************************************/
static void printf_logo(void)
{
		printf("\r\n");
    printf("################################################\r\n");
    printf("arch             : Ai-SG01-P\r\n");	
		printf("company          : Ai-Thinker\r\n");
    printf("sdk_version      : 0x%04x\r\n", fwid);		
    printf("firmware_version : %s\r\n", FIRMWARE_VERSION);
		printf("compile_time     : %s-%s\r\n", __DATE__, __TIME__);
		printf("\r\n");
		printf("ready\r\n");
    printf("################################################\r\n");
}

/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参: 无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/
int main(void)
{
		bsp_Init();		        /* 硬件初始化 */
    AT_Command_Init();	// 初始化AT指令模块
	
		printf_logo();
	
		if (DeviceConfig_Load(&device_config)) {
        printf("Configuration loaded from Flash\r\n");
				if (device_config.RadioInit.Power > POWER_3dBm) {
						device_config.RadioInit.Power = POWER_3dBm;
				}
				if (device_config.RadioInit.PowerSelect == POWER_DCDC_0402 || 
						device_config.RadioInit.PowerSelect == POWER_DCDC_0603) {
						dcdc_enable = true;
				} else {
						dcdc_enable = false;
				}
    } else {
        printf("No valid configuration found, using defaults\r\n");
        // 使用默认配置
        DeviceConfig_Init(&device_config);
        // 保存默认配置到Flash
        if (DeviceConfig_Save(&device_config)) {
//            printf("Default configuration saved to Flash\r\n");
        } else {
//            printf("Failed to save default configuration!\r\n");
        }
    }
		
		// 打印当前配置
    DeviceConfig_DebugPrint(&device_config);
   
    PAN312x_Fsk_Init();
    PAN312x_Get_FwId(&fwid);
    
    PAN312x_RadioInit(&device_config.RadioInit);
		PAN312x_PktInit(&PacketInit);
		PAN312x_CrcInit(&CrcInit);
	
		PAN312x_System_Ctrl(SYS_CTRL_AUTO_CLEAR_STATUS);
    
    //默认TX
//    device_config.rf_mode = 2;
    
//    PAN312x_Set_TxPacket_Config(TxFixedPackedCrcEnable);
//    PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE | IRQ_MASK_WAKEUP), S_ENABLE);
		
    
    PAN312x_Irq_Clear_AllStatus();
   	
		bsp_StartAutoTimer(0, 1000); /* 启动1个200ms的自动重装的定时器，软件定时器0 */
    DIO8_EnableInterrupt();
		
		Init_PAN312x_Gpio_Mode();	//初始化IO0,1,10为输入模式，规避GPIO一开始设置为输出模式时无法正确读取电平
		
		bsp_InitGC1131();		//放在初始化Ai-SG01-P之后
		
		Set_PAN312x_RF_Mode_Config();
		if (device_config.tx_mode == 0) {
//				device_config.tx_period = 500;
				bsp_StartTimer(1, device_config.tx_period);
		}
		
		MX_TIM2_Init_Ms(100);
		__HAL_TIM_CLEAR_IT(&TIM2_InitStruct, TIM_IT_UPDATE);
    
		while (1)
		{
        /* 判断定时器超时时间 */                                                                                                                                     
//				if (bsp_CheckTimer(0)){
//				/* 心跳 每隔100ms 进来一次 */ 
//						bsp_LedToggle(BLUE_LED); 	
//				}
				
				if (wakeup_flag) {
						if (sleep_mode == DEEP_SLEEP_MODE) {
								PAN312x_Fsk_Init();
								PAN312x_Get_FwId(&fwid);
								PAN312x_RadioInit(&device_config.RadioInit);
								PAN312x_PktInit(&PacketInit);
								PAN312x_CrcInit(&CrcInit);								
								PAN312x_System_Ctrl(SYS_CTRL_AUTO_CLEAR_STATUS);
								PAN312x_Irq_Clear_AllStatus();
							#if 0
								if (device_config.rf_mode == 1) {
										PAN312x_Set_RxPacket_Config(RxFixedPackedCrcEnable);
										PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE | IRQ_MASK_ACK_TIMEOUT), S_DISABLE);
										PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_RX_DONE | IRQ_MASK_RX_CRC_ERROR), S_ENABLE); 
										PAN312x_Set_RxInvalid_ExitState(STATE_RX);
										PAN312x_Set_RxValid_ExitState(STATE_RX);		
										PAN312x_Enter_Rx(0, 0, nPayloadLength);
								} else if (device_config.rf_mode == 2) {
										PAN312x_Set_TxPacket_Config(TxFixedPackedCrcEnable);
										PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE), S_ENABLE);
										PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_RX_DONE | IRQ_MASK_ACK_TIMEOUT), S_DISABLE);
								} else if (device_config.rf_mode == 3) {
										PAN312x_Set_AckTimeOut(400000);	//4s
										PAN312x_Set_AckTimeout_ExitState(STATE_READY);
										PAN312x_Set_TxPacket_Config(TxFixedPackedCrcEnable);
										PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE|IRQ_MASK_ACK_TIMEOUT), S_ENABLE);
										PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_RX_DONE), S_DISABLE);
								} else if (device_config.rf_mode == 4) {
										PAN312x_Set_AckTxDelay2(120);
										PAN312x_Set_RxPacket_Config(RxFixedPackedCrcEnable);
										PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE), S_DISABLE);
										PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_RX_DONE | IRQ_MASK_RX_CRC_ERROR), S_ENABLE);
										PAN312x_Set_RxInvalid_ExitState(STATE_RX);
										PAN312x_Set_RxValid_ExitState(STATE_RX);
										PAN312x_Enter_Rx(0, START_COND_ENABLE_ACK, nPayloadLength);
								}
								#else
//								PAN312x_Iomux_Gpio(IOMUX_GPIO2_AS_GPIO);
//								PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_2, GPIO_INPUT_MODE);
//								bsp_InitGC1131();
//								Set_PAN312x_RF_Mode_Config();
								#endif
//										printf("3333333333333333333\r\n");
						}
						sleep_mode = WAKE_UP_READY;
						wakeup_flag = false;
						bsp_InitGC1131();
						Set_PAN312x_RF_Mode_Config();
						AT_Send_Response(AT_RESPONSE_OK, NULL);
				}

				// 处理AT指令
				AT_Command_Process();
				
				if (sleep_mode == WAKE_UP_READY && !wakeup_flag) {
						if((device_config.rf_mode == 1) || (device_config.rf_mode == 4)){
								
								if(xRxDoneFlag){
										xRxDoneFlag = S_RESET;
										rssi_value = PAN312x_GetRSSI();
										cRxData = PAN312x_Get_RxLengthInPacket();
										PAN312x_Read_Fifo(vectRxBuffer, cRxData);
										PAN312x_Irq_Clear_RxDone_Status();
										if(memcmp(vectRxBuffer, vectExpectBuffer, cRxData) == 0){
												rx_cnt ++ ;
										}else{
												rx_error_cnt++;
										}
										printf("Ok Cnt:%"PRIu16", Err Cnt:%"PRIu16", Rssi:-%d",rx_cnt, rx_error_cnt, rssi_value);
								}
						}
						 
						if(bsp_CheckTimer(1)){
								if((device_config.rf_mode == 2) || (device_config.rf_mode == 3)){
										bsp_LedOn(GREEN_LED);
										DIO8_EnableInterrupt();
										PAN312x_Flush_TxFifo();
										PAN312x_Reset_Modem();
										PAN312x_Write_Fifo((uint8_t *)vectTxBuffer, nPayloadLength);
										if(device_config.rf_mode == 3){
												PAN312x_Enter_Tx(0, START_COND_ENABLE_ACK, nPayloadLength);
										}else{
												PAN312x_Enter_Tx(0, 0, nPayloadLength);
										}
										while(!xTxDoneFlag);
										xTxDoneFlag = S_RESET;
										if(!xAckTimeoutFlag){
												tx_cnt++;
												printf("Ok Cnt:%"PRIu16", Err Cnt:%"PRIu16"", tx_cnt, rx_error_cnt);
										}else{
												xAckTimeoutFlag = S_RESET;
												rx_error_cnt++;
												printf("Ok Cnt:%"PRIu16", Err Cnt:%"PRIu16"", tx_cnt, rx_error_cnt);
										}
										
										if(device_config.rf_mode == 3){
												tx_total_cnt = tx_cnt + rx_error_cnt;
										}
										bsp_LedOff(GREEN_LED);
										
										if(device_config.tx_mode == 0x00){
												//连续发送
												bsp_StartTimer(1, device_config.tx_period);
										}else if(device_config.tx_mode == 0x01){
												//发送500次
												if(tx_total_cnt == 500){
														//针对TRxMaster的
														bsp_StopTimer(1);
												}else if(tx_cnt == 500){
														//针对Tx的
														bsp_StopTimer(1);
												}else{
														bsp_StartTimer(1, device_config.tx_period);
												}
										
										}else if(device_config.tx_mode == 0x02){
												//单次发送
										}
								}		
						}
				}  		
		}

}

