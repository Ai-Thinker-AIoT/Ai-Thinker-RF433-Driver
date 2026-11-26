/**
  ******************************************************************************
  * �ļ��� ��   at_command_firmware
  * ����   ��   Ai Thinker
  * �汾   ��   V4.18_P1.1.1
  * ʱ��   ��   
  * �ļ�������

*******************************************************************************/
#include "bsp.h"		
#include "carrier_config.h"

#define RX_TIMEOUT_ENABLE 1

#define FIRMWARE_VERSION "V4.18_P1.1.2"

// �������ݽṹ
typedef struct {
    PAN312xRadioInit RadioInit;
		uint8_t tx_mode;
		uint8_t rf_mode;
		uint16_t tx_period;
		uint16_t crc;
} DeviceConfig;

// ȫ������ʵ��
DeviceConfig device_config;

// Flash�洢��ַ����
#define CONFIG_FLASH_ADDR  0x0800FC00  // ���һҳ��ʼ��ַ
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
//	POWER_LDO_0402,		//DCDCģʽ�£��������13dBm��Ldoģʽ���������20dBm
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
volatile uint32_t g_rxdone_seen_cnt = 0;   /* [DIAG] latches every RX_DONE bit observation */
uint16_t fwid;
//static int16_t tx_period = 50; //���͵�ʱ����


/*
 * tx_mode = 0x00: ��ʾ��������
 * tx_mode = 0x01����ʾ����1000����
 * tx_mode = 0x02����ʾ��һ�ΰ�������һ������
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

/* ---------- PingPong 对测：角色变量（0=PING 发送者 / 1=PONG 接收者） ---------- */
#ifndef PINGPONG_ROLE_DEFAULT
#define PINGPONG_ROLE_DEFAULT 1
#endif
volatile uint8_t g_pingpong_role = PINGPONG_ROLE_DEFAULT; /* role 1 = PONG build */

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

/* ---- single-carrier (unmodulated CW) transmit mode --------------------
   g_carrier_active latches the AT+ENTERCARRIER state. While it is set,
   neither the PingPong state machine nor the legacy timer driven TX/RX
   loop is allowed to touch the RF working state, so the carrier stays on.
   It is cleared only by an AT command that changes the RF working mode
   (RFMODE / TXSTART / PINGPONG / FACTORY TEST / SLEEPMODE).        */
volatile bool g_carrier_active = false;

/* PingPong run state, declared here instead of next to PingPong_Test so the
   carrier AT commands can stop the state machine: while it keeps running
   every timer tick calls Set_PAN312x_RF_Mode_Config()/PAN312x_Enter_Tx()
   and tears the carrier straight back down. */
typedef enum {
    PP_STATE_DISABLED = 0,   /* PingPong 未激活 */
    PP_STATE_IDLE,           /* 等待 timer2 触发发送（PING 初始 / 收到包后） */
    PP_STATE_RX_WAIT,        /* 等待接收（发送完成后 / PONG 初始） */
} PingPongState;

volatile PingPongState g_pp_state = PP_STATE_DISABLED;
volatile bool g_pp_active = false;   /* PingPong 是否激活运行 */
/* set when the carrier was on before SLEEPMODE, so it can be rebuilt on
   wake-up (the RF block is powered down during sleep, the latch cannot
   simply stay true) */
volatile bool g_carrier_suspended = false;

static void Carrier_Enter_Now(void);
#if CARRIER_AUTO_ON_BOOT
static void Carrier_Enter_Default(void);
#endif
static void Carrier_Refresh_IfActive(void);

#define WAKE_UP_READY  -1
int rssi_value;
volatile int sleep_mode = WAKE_UP_READY;

void HAL_GPIO_EXTI_Callback(void)
{
				PAN312x_Irq_Get_Status(&xIrqStatus);
        if((xIrqStatus.u0.IRQ_STATUS0 & 0x01)){
            xTxDoneFlag = S_SET;
				}
        
        if(device_config.rf_mode == 3){
            if((xIrqStatus.u1.IRQ_STATUS1 & 0x20)){
                //printf("Ack Timeout\r\n");
                xTxDoneFlag = S_SET;
                xAckTimeoutFlag = S_SET;
            }
        }
          
        if((xIrqStatus.u0.IRQ_STATUS0 & 0x02)){
//						printf("IRQ_RX_DONE\r\n");
            xRxDoneFlag = S_SET;   
				}
				
				if((xIrqStatus.u0.IRQ_STATUS0 & 0x10)){
						/* RX timeout is handled by the main state machine. */
//            xRxDoneFlag = S_SET;   
				}
        
        if((xIrqStatus.u0.IRQ_STATUS0 & 0x08)){
//						printf("IRQ_RX_CRC_ERROR\r\n");
            xRxDoneFlag = S_SET;  
						PAN312x_Irq_Clear_RxCrcError_Status();
				}
				
				if((xIrqStatus.u1.IRQ_STATUS1 & 0x10)) {
//						printf("IRQ_WAKEUP\r\n ");
						wakeup_flag = true;
						wakeup_cnt = 0;
						HAL_TIM_Base_Stop_IT(&TIM2_InitStruct);
				}
}

/*******************************************************************************************************/

// ATָ�������С
#define AT_CMD_BUF_SIZE 128

// ATָ����Ӧ����
typedef enum {
    AT_RESPONSE_OK,
    AT_RESPONSE_ERROR,
    AT_RESPONSE_BUSY,
    AT_RESPONSE_NO_RESPONSE
} AT_Response_Type;


// ATָ�������ָ������
typedef void (*AT_Command_Handler)(const char* params);

// ATָ�����
typedef struct {
    const char* command;
    AT_Command_Handler handler;
    const char* description;
		bool support_query;           // �Ƿ�֧�ֲ�ѯ(?)
    bool support_execution;       // �Ƿ�֧��ִ��(�޲���)
    bool support_parameters;      // �Ƿ�֧�ִ�����(=)
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
static void AT_Module_Reset(const char* params);
static void AT_Factory_Test_Master(const char* params);
static void AT_Factory_Test_Slave(const char* params);
static void AT_Read_RSSI(const char* params);
static void AT_PingPong(const char* params);


// ATָ�����
static char at_cmd_buf[AT_CMD_BUF_SIZE];
static uint16_t at_cmd_index = 0;
static bool at_cmd_ready = false;

// ATָ���
static const AT_Command_Entry at_command_table[] = {
    {"AT", AT_Test, "Test connection", false, true, false},
//    {"AT+LED", AT_LED_Control, "Control LED", true, true, true},
		{"AT+TXMODE", AT_Tx_Mode, "Send Data Mode", true, false, true},														//�л�����ģʽ
		{"AT+RFMODE", AT_RF_Mode, "RF Mode", true, false, true},																	//�л�Tx��Rxģʽ
		{"AT+DATARATE", AT_Toggle_DataRate, "Toggle DataRate", true, false, true},								//�л�����
		{"AT+FREQUENCYBASE", AT_Toggle_FrequencyBase, "Toggle FrequencyBase", true, false, true},	//�л�Ƶ��
		{"AT+POWERDBM", AT_Toggle_PowerdBm, "Toggle PowerdBm", true, false, true},								//�л�����
		{"AT+POWERSELECT", AT_Toggle_PowerSelect, "Toggle PowerSelect", true, false, true},				//�л���в���
		{"AT+ENTERCARRIER", AT_Enter_Carrier, "Enter Carrier", false, true, false},								//ʹ�ܵ��ز�ģʽ
		{"AT+CLEARCNT", AT_Clear_Count, "Clear Count", true, false, true},												//�������
		{"AT+SLEEPMODE", AT_Sleep_Mode, "Sleep Mode", true, false, true},													//˯��ģʽ
		{"AT+WAKEUP", AT_Wake_Up, "Sleep WakeUp", false, true, false},														//˯�߻���
		{"AT+GPIOMODE", AT_Gpio_Set_Mode, "Set Gpio Mode", true, false, true},										//����GPIO�������
		{"AT+GPIOWRITE", AT_Gpio_Write, "Gpio Write", false, false, true},												//����GPIO�����ƽ
		{"AT+GPIOREAD", AT_Gpio_Read, "Gpio Read", false, false, true},														//��ȡGPIO��ƽ
		{"AT+CONFIGSAVE", AT_Config_Save, "Device Config Save", false, true, false},							//��������
		{"AT+CONFIGRESET", AT_Config_Reset, "Device Config Reset", false, true, false},						//�ָ���������
		{"AT+TXPERIOD", AT_Tx_Period, "Tx Period", true, false, true},														//�л�����ģʽ
		{"AT+TXSTOP", AT_Tx_Stop, "Tx Stop", false, true, false},																	//��ͣ����
		{"AT+TXSTART", AT_Tx_Start, "Tx Start", false, true, false},															//��ʼ����
		{"AT+RESET", AT_Module_Reset, "Module_Reset", false, true, false},
		{"AT+PINGPONG", AT_PingPong, "PingPong Test (0=PING,1=PONG,?=query, bare=toggle)", true, true, true},												
		{"AT+FTMASTER", AT_Factory_Test_Master, "Factory Test Master", false, true, false},				//��������
		{"AT+FTSLAVE", AT_Factory_Test_Slave, "Factory Test Slave", false, true, false},					//����ӻ�
    {"AT+RSSI", AT_Read_RSSI, "Read current RSSI in RX", false, true, false},
    {"AT+HELP", AT_Help, "Show help", false, true, false},
//    {"AT+VERSION", AT_Version, "Get firmware version"},
    {NULL, NULL, NULL, false, false, false}  // �������
};

// ATָ���ʼ��
void AT_Command_Init(void)
{
    at_cmd_index = 0;
    at_cmd_ready = false;
    memset(at_cmd_buf, 0, AT_CMD_BUF_SIZE);
}

// ATָ���������
void AT_Command_Process(void)
{
    uint8_t rx_data[64];
    uint16_t rx_count;
    uint16_t i;
    
    // �Ӵ��ڻ�������ȡ����
    rx_count = USART1_ReceiveData(rx_data, sizeof(rx_data));
    
    for (i = 0; i < rx_count; i++) {
        uint8_t dat = rx_data[i];
        
        // ����Ƿ���յ�ATָ�������
        if (dat == '\r' || dat == '\n') {
            if (at_cmd_index > 0) {
                at_cmd_buf[at_cmd_index] = '\0';
                at_cmd_ready = true;
                at_cmd_index = 0;
            }
        } else if (at_cmd_index < AT_CMD_BUF_SIZE - 1) {
            at_cmd_buf[at_cmd_index++] = dat;
        }
    }
    
    // ����������ATָ��
    if (at_cmd_ready) {
        AT_Process_Command(at_cmd_buf);
        at_cmd_ready = false;
        memset(at_cmd_buf, 0, AT_CMD_BUF_SIZE);
    }
}

// ����������ATָ��
static void AT_Process_Command(const char* input)
{
		char cmd[32] = {0};
    char params[128] = {0};
    bool is_query = false;
    bool has_params = false;
		bool found = false;
		int i = 0;
		int j = 0;

		char temp_buf[128] = {0};
		strcpy(temp_buf, input);
    
    // ����ǰ���ո�
    while (*input == ' ') input++;
    
    // ��ȡ����� (�����ִ�Сд)
		/* C89: i moved to top of function */
    while (*input && *input != '?' && *input != '=' && *input != ' ' && i < sizeof(cmd)-1) {
        cmd[i++] = toupper(*input++);
    }
    cmd[i] = '\0';
    
    // ��������
    if (*input == '?') {
        is_query = true;
        input++;
    } else if (*input == '=') {
        has_params = true;
        input++;
    }
    
    // ��ȡ����
    if (has_params) {
        i = 0;
        // �����ո�
        while (*input == ' ') input++;
        
        // ���Ʋ���
        while (*input && *input != '\r' && *input != '\n' && i < sizeof(params)-1) {
            params[i++] = *input++;
        }
        params[i] = '\0';
    }
    
    // ����ƥ�������
		/* C89: found moved to top of function */
    for (j = 0; at_command_table[j].command != NULL; j++) {
        if (strcmp(cmd, at_command_table[j].command) == 0) {
            found = true;
            
            // ���ָ���ʽ�Ƿ�֧��
            if (is_query && !at_command_table[j].support_query) {
								char response[50] = {0};
								sprintf(response, "\r\n%s:3",at_command_table[j].command+2);
                AT_Send_Response(AT_RESPONSE_ERROR, response);
                return;
            } else if (!is_query && !has_params && !at_command_table[j].support_execution) {
                char response[50] = {0};
								sprintf(response, "\r\n%s:3",at_command_table[j].command+2);
                AT_Send_Response(AT_RESPONSE_ERROR, response);
                return;
            } else if (has_params && !at_command_table[j].support_parameters) {
                char response[50] = {0};
								sprintf(response, "\r\n%s:3",at_command_table[j].command+2);
                AT_Send_Response(AT_RESPONSE_ERROR, response);
                return;
            }
            
            // ���ô�������
            if (is_query) {
                // ��ѯ����
                at_command_table[j].handler("?");
            } else if (has_params) {
                // ����������
                at_command_table[j].handler(params);
            } else {
                // �޲���ִ��
                at_command_table[j].handler("");
            }
            
            break;
        }
    }
    
    if (!found) {
				printf("Unknown cmd:%s",temp_buf);
    }
}


// ����AT��Ӧ
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

// AT����ָ��
static void AT_Test(const char* params)
{
    AT_Send_Response(AT_RESPONSE_OK, NULL);
}

// ����ָ��
static void AT_Help(const char* params)
{
//    printf("Available AT Commands:\r\n");
    
    uint8_t i;
    for (i = 0; at_command_table[i].command != NULL; i++) {
        printf("\r\n%s - %s", at_command_table[i].command, at_command_table[i].description);
    }
    
    AT_Send_Response(AT_RESPONSE_OK, NULL);
}

#if 0
// LED����ָ��
static void AT_LED_Control(const char* params)
{
    if (strcmp(params, "?") == 0) {
        // ��ѯLED״̬
        printf("LED Status: GREEN=%s, BLUE=%s", 
               bsp_IsLedOn(GREEN_LED) ? "ON" : "OFF", 
               bsp_IsLedOn(BLUE_LED) ? "ON" : "OFF");
        AT_Send_Response(AT_RESPONSE_OK, NULL);
    } else if (strlen(params) == 0) {
        // �л�LED״̬
        bsp_LedToggle(GREEN_LED);
        bsp_LedToggle(BLUE_LED);
        AT_Send_Response(AT_RESPONSE_OK, "LEDs toggled");
    } else {
        // ��������
        char led[10];
        char state[10];
        
        if (sscanf(params, "%9[^,],%9s", led, state) == 2) {
            // ����ָ��LED
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

static int pp_StartRx(uint8_t condition)
{
    int ret;
    uint8_t tries;
    pp_WaitPropReady();
    for (tries = 0; tries < 10; tries++) {
        ret = PAN312x_Enter_Rx(0, condition, nPayloadLength);
        if (ret != -10) break;
        bsp_DelayMS(2);
    }
    if (ret != 0) printf("RX ENTER FAILED ret=%d\r\n", ret);
    return ret;
}

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
				#ifdef RX_TIMEOUT_ENABLE
				pp_StartRx(START_COND_ENABLE_TIMEOUT);
				#else
				pp_StartRx(0);
				#endif
		} else if (device_config.rf_mode == 2) {
				if (dcdc_enable) {
						PAN312x_DCDC_Enable();
				} else {
						PAN312x_DCDC_Disable();
				}
				PAN312x_Set_TxPacket_Config(TxFixedPackedCrcEnable);
				PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE |IRQ_MASK_WAKEUP), S_ENABLE);
				PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_RX_DONE | IRQ_MASK_ACK_TIMEOUT), S_DISABLE);
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
		}
}
/* =====================================================================
 * Single-carrier (unmodulated CW) transmit mode helpers
 * ---------------------------------------------------------------------
 * Carrier_Enter_Now()     : identical sequence to AT+ENTERCARRIER - it
 *                           calls PAN312x_Enter_Carrier() with the current
 *                           device_config radio parameters and clears the
 *                           stale IRQ flags.
 * Carrier_Refresh_IfActive(): used by the radio-parameter AT commands so
 *                           that AT+DATARATE / AT+FREQUENCYBASE /
 *                           AT+POWERDBM / AT+POWERSELECT keep the carrier
 *                           running on the new parameters instead of
 *                           dropping it.
 * ===================================================================== */
/* Enter_Ready retried until the chip accepts it. PAN312x_Enter_Carrier() is a
   bare register sequence: it performs no GO_READY handshake and never checks
   CTS, so when it is called while the chip is still busy in RX/TX every write
   is silently dropped and no carrier is ever emitted (same failure mode
   already handled in PingPong_Step_Ping). */
static void Carrier_Wait_Ready(void)
{
    int rdy = -10, k = 0;

    while (rdy == -10 && k++ < 50) {
        rdy = PAN312x_Enter_Ready();
        if (rdy == -10) {
            bsp_DelayUS(200);
        }
    }
}

static void Carrier_Enter_Now(void)
{
    Carrier_Wait_Ready();
    PAN312x_Enter_Carrier(device_config.RadioInit.FrequencyBase, device_config.RadioInit.FrequencyStep, device_config.RadioInit.FrequencyChannelNumber, device_config.RadioInit.PowerSelect, device_config.RadioInit.Power);
    PAN312x_Irq_Clear_AllStatus();
}

static void Carrier_Refresh_IfActive(void)
{
    if (g_carrier_active) {
        Carrier_Enter_Now();
    }
}

static void AT_RF_Mode(const char* params)
{
    int mode;
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
        printf("\r\n+RFMODE: %d", device_config.rf_mode);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
        // ��������

        if (sscanf(params, "%d", &mode) == 1) {
//						PAN312x_RadioInit(&device_config.RadioInit);
            if (mode == 1) {	
								device_config.rf_mode = 1;
								g_carrier_active = false;   /* RFMODE: leave single-carrier mode */
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
//								bsp_DelayMS(50);
//								PAN312x_RadioInit(&device_config.RadioInit);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
							
            } else if (mode == 2) {
								device_config.rf_mode = 2;
								g_carrier_active = false;   /* RFMODE: leave single-carrier mode */
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
//								bsp_DelayMS(50);
//								PAN312x_RadioInit(&device_config.RadioInit);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
            } else if (mode == 3) {
								device_config.rf_mode = 3;
								g_carrier_active = false;   /* RFMODE: leave single-carrier mode */
								PAN312x_Enter_Ready();
								Set_PAN312x_RF_Mode_Config();
//								bsp_DelayMS(50);
//								PAN312x_RadioInit(&device_config.RadioInit);
								AT_Send_Response(AT_RESPONSE_OK, NULL);
            } else if (mode == 4) {
								device_config.rf_mode = 4;
								g_carrier_active = false;   /* RFMODE: leave single-carrier mode */
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
    int mode;
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
				
        // ��������

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
    uint32_t rate;
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
        printf("\r\n+DATARATE:%"PRIu32" ", device_config.RadioInit.DataRate);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
        // ��������

        
        if (sscanf(params, "%" PRIu32 , &rate) == 1) {
						if (rate >= 2000 && rate <= 500000) {		
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
								Carrier_Refresh_IfActive();
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
    uint32_t frequency;
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
        printf("\r\n+FREQUENCYBASE:%"PRIu32"", device_config.RadioInit.FrequencyBase);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
        // ��������

        
        if (sscanf(params, "%" PRIu32 , &frequency) == 1) {
						if (frequency > 0 && frequency < 4294967295) {			
								device_config.RadioInit.FrequencyBase = frequency;	
								PAN312x_RadioInit(&device_config.RadioInit);
//								__PAN312x_Enter_Status();
								Set_PAN312x_RF_Mode_Config();
								Carrier_Refresh_IfActive();
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
    int power_dbm;
    uint8_t new_powerdbm;
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
				int power;
				power = (int)(device_config.RadioInit.Power & 0xff) - 20;
        printf("\r\n+POWERDBM:%d", power);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
        // ��������


        
        if (sscanf(params, "%d", &power_dbm) == 1) {
						if((device_config.RadioInit.PowerSelect == POWER_LDO_0603) || (device_config.RadioInit.PowerSelect == POWER_LDO_0402)) {
								if((power_dbm > 20) || (power_dbm < -20)){
										AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+POWERDBM:4");
								} else {
										new_powerdbm = (power_dbm + 20) & 0xff;
										device_config.RadioInit.Power = (PAN312xPowerdBm)new_powerdbm;
										PAN312x_RadioInit(&device_config.RadioInit);
//										__PAN312x_Enter_Status();
										Set_PAN312x_RF_Mode_Config();
										Carrier_Refresh_IfActive();
										AT_Send_Response(AT_RESPONSE_OK, NULL);
								}
						} else if ((device_config.RadioInit.PowerSelect == POWER_DCDC_0603) || (device_config.RadioInit.PowerSelect == POWER_DCDC_0402)) {
								if((power_dbm > 13) || (power_dbm < -20)){
										AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+POWERDBM:4");
								}  else {
										new_powerdbm = (power_dbm + 20) & 0xff;
										device_config.RadioInit.Power = (PAN312xPowerdBm)new_powerdbm;
										PAN312x_RadioInit(&device_config.RadioInit);
//										__PAN312x_Enter_Status();
										Set_PAN312x_RF_Mode_Config();
										Carrier_Refresh_IfActive();
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

static void AT_Toggle_PowerSelect(const char* params)
{
    int mode;
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
	
		if (strcmp(params, "?") == 0) {
				printf("\r\n+POWERSELECT:%d ", (device_config.RadioInit.PowerSelect == POWER_LDO_0402 || device_config.RadioInit.PowerSelect == POWER_LDO_0603) ? 0 : 1);
        AT_Send_Response(AT_RESPONSE_OK, NULL);
			
    } else {
        // ��������

        
        if (sscanf(params, "%d", &mode) == 1) {
						switch(mode) {
								case 0: {
										device_config.RadioInit.PowerSelect = POWER_LDO_0402;
										dcdc_enable = false;
									break;
								}
								case 1: {
										device_config.RadioInit.PowerSelect = POWER_DCDC_0402;
										if (device_config.RadioInit.Power > POWER_13dBm) {
												device_config.RadioInit.Power = POWER_13dBm;
										}
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
						Carrier_Refresh_IfActive();
						AT_Send_Response(AT_RESPONSE_OK, NULL);
        } else {
            AT_Send_Response(AT_RESPONSE_ERROR, "\r\n+POWERDBM:3");
        }
    }
}

static void AT_Enter_Carrier(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		/* Stop the PingPong state machine and both timers first: if they keep
		   running the next tick rewrites the RF working state, and because the
		   latch below stays true the legacy TX/RX branch is blocked forever. */
		g_pp_active = false;
		g_pp_state  = PP_STATE_DISABLED;
		bsp_StopTimer(1);
		bsp_StopTimer(2);
		Carrier_Enter_Now();
		/* latch the carrier so that no background logic can undo it */
		g_carrier_active = true;
    AT_Send_Response(AT_RESPONSE_OK, NULL);
}

static void AT_Clear_Count(const char* params)
{
		if (strcmp(params, "?") == 0) {
        AT_Send_Response(AT_RESPONSE_OK, NULL);
				printf("\r\n+CLEARCNT:\r\nOk Cnt:%"PRIu32", Err Cnt:%"PRIu32"", tx_cnt, rx_error_cnt);	
    } else {
				int mode = 0;
				if (sscanf(params, "%d", &mode) == 1) {
						if (mode == 1) {
								tx_cnt = 0;
								rx_cnt = 0;
								rx_error_cnt = 0;
								AT_Send_Response(AT_RESPONSE_OK, NULL);
//								printf("Ok Cnt:%" PRIu32 ", Err Cnt:%" PRIu32 "", tx_cnt, rx_error_cnt);
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
								/* SLEEPMODE: the RF block is powered down so the latch must
								   drop, but remember it - the carrier is rebuilt on wake-up
								   (AT_Wake_Up and the main-loop wake-up branch). */
								g_carrier_suspended = g_carrier_active;
								g_carrier_active = false;
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
    uint8_t rf_status;
		if (sleep_mode == SLEEP_MODE || sleep_mode == DEEP_SLEEP_MODE) {
				
				PAN312x_SPI_Init();
				PAN312x_DIO8_INPUT();
				DIO8_EnableInterrupt();
				
				bsp_DelayUS(120);

				//�ж���PAN312x�Ƿ���sleepģʽ��deepsleepģʽ
				PAN312x_Read(R003, &rf_status);
		//						printf("rf status: %x\r\n", rf_status);
				if((rf_status == 0x01) || (rf_status == 0x02)){
						//��ʾPAN312x����deepsleep ����sleepģʽ
						//ִ�л���ָ���PAN312x����
						PAN312x_ClkRcl_Enable();
						PAN312x_WakeUp_BySpi();
				}
				HAL_TIM_Base_Start_IT(&TIM2_InitStruct);

				/* restore the carrier that was running before sleep */
				if (g_carrier_suspended) {
						g_carrier_suspended = false;
						Carrier_Enter_Now();
						g_carrier_active = true;
				}
				
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

// ���Ӷ�ȡ��������
uint8_t PAN312x_Get_Gpio_Mode(uint16_t GpioPin);

// ��ȡ����GPIO���ŵ�ģʽ
uint8_t PAN312x_Get_Gpio_Mode(uint16_t GpioPin)
{
    uint8_t tmp;
		uint8_t GpioPin0_2_11 = 0x00,GpioPin3_10 = 0x00;
    uint16_t mode = GPIO_MODE_UNKNOWN;
    
    // �����8λ�͸�8λ����
    GpioPin0_2_11 = (uint8_t)GpioPin;
    GpioPin3_10 = (uint8_t)(GpioPin >> 8);
//		printf("GpioPin0_2_11:%" PRIu8 ", GpioPin3_10:%" PRIu8 "\r\n", GpioPin0_2_11, GpioPin3_10);
    
    // ��������Ƿ���Ч
    if (!GpioPin0_2_11 && !GpioPin3_10) {
        return GPIO_MODE_UNKNOWN;
    }
    
    // ������8λ���� (GPIO0, GPIO1, GPIO2, GPIO11)
    if (GpioPin0_2_11) {
        // ��ȡR1B0�Ĵ��� (0x1B0)
        PAN312x_Get_OP_Reg(R1B0, 1, &tmp);
        
        // ���ÿ�����ŵ�ģʽ
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
    
    // ������8λ���� (GPIO3-GPIO10)
    if (GpioPin3_10) {
        uint8_t input_enable = 0;
        uint8_t output_enable = 0;
        
        // ��ȡ����ʹ�ܼĴ��� (R018)
        PAN312x_Get_OP_Reg(R018, 1, &input_enable);
        
        // ��ȡ���ʹ�ܼĴ��� (R019)
        PAN312x_Get_OP_Reg(R019, 1, &output_enable);
        
        // ���ÿ�����ŵ�ģʽ
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
	int gpio_pin;
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				return;
		}
	
		if (strcmp(params, "?") == 0) {
				uint8_t pin0_mode = PAN312x_Get_Gpio_Mode(PAN312x_GPIO_PIN_0);
				uint8_t pin1_mode = PAN312x_Get_Gpio_Mode(PAN312x_GPIO_PIN_1);
				uint8_t pin2_mode = PAN312x_Get_Gpio_Mode(PAN312x_GPIO_PIN_2);
				uint8_t pin10_mode = PAN312x_Get_Gpio_Mode(PAN312x_GPIO_PIN_10);
				printf("\r\n+GPIOMODE:");
				printf("\r\npin0:%s", pin0_mode == GPIO_MODE_UNKNOWN ? "GPIO_MODE_UNKNOWN" : (pin0_mode == 0x01 ? "GPIO_OUTPUT_MODE" : "GPIO_INPUT_MODE") );
				printf("\r\npin1:%s", pin1_mode == GPIO_MODE_UNKNOWN ? "GPIO_MODE_UNKNOWN" : (pin1_mode == 0x01 ? "GPIO_OUTPUT_MODE" : "GPIO_INPUT_MODE") );
				printf("\r\npin2:%s", pin2_mode == GPIO_MODE_UNKNOWN ? "GPIO_MODE_UNKNOWN" : (pin2_mode == 0x01 ? "GPIO_OUTPUT_MODE" : "GPIO_INPUT_MODE") );
				printf("\r\npin10:%s", pin10_mode == GPIO_MODE_UNKNOWN ? "GPIO_MODE_UNKNOWN" : (pin10_mode == 0x01 ? "GPIO_OUTPUT_MODE" : "GPIO_INPUT_MODE") );
        AT_Send_Response(AT_RESPONSE_OK, NULL);
				return;
    } else {
        // ��������
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
						}	else if (gpio_pin == 2) {
								if (gpio_mode == 1) {
									PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_2, GPIO_OUTPUT_MODE);
								} else if (gpio_mode == 2) {
									PAN312x_Set_Gpio_Mode(PAN312x_GPIO_PIN_2, GPIO_INPUT_MODE);
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
	int gpio_pin;
    int gpio_level;
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		


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
	int gpio_pin;
    uint8_t gpio_level;
		if (sleep_mode != WAKE_UP_READY) {
				printf("\r\n+EVENT:%s", sleep_mode > 0 ? "Deep_Sleep_Mode" : "Sleep_Mode");
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		

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
    uint16_t number;
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
        // ��������

        
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
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		
		bsp_StopTimer(1);
		AT_Send_Response(AT_RESPONSE_OK, NULL);
}

static void AT_Tx_Start(const char* params)
{
		if (sleep_mode != WAKE_UP_READY) {
				AT_Send_Response(AT_RESPONSE_ERROR, NULL);
				return;
		}
		
		if (g_carrier_active) {   /* TXSTART: leave single-carrier mode */
				/* Rebuild the normal RF working state: with the latch cleared but
				   the chip still in CW, an RX role never issues Enter_Rx again and
				   the receiver stays dead until the next RFMODE command. */
				g_carrier_active = false;
				Carrier_Wait_Ready();
				Set_PAN312x_RF_Mode_Config();
		}

		if(device_config.tx_mode == 0x01){
				//����500��
				if(tx_total_cnt == 500) {
						//���TRxMaster��
						tx_cnt = 0;
						rx_error_cnt = 0;
						tx_total_cnt = 0;
				} else if(tx_cnt == 500) {
						//���Tx��
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
		HAL_NVIC_SystemReset();
}

static void AT_Read_RSSI(const char* params)
{
    int r;
    /* Force RX on current frequency, settle, then sample RSSI a few times. */
    device_config.rf_mode = 1;
    PAN312x_Enter_Ready();
    Set_PAN312x_RF_Mode_Config();
    bsp_DelayMS(30);
    r = PAN312x_GetRSSI();
    printf("\r\n+RSSI:%ld", (long)r);
    AT_Send_Response(AT_RESPONSE_OK, NULL);
}

static void AT_Factory_Test_Master(const char* params)
{
				// �������������ṹ�壨��������ֽڣ�
	
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
	
		g_carrier_active = false;   /* FACTORY TEST: leave single-carrier mode */
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
								cRxData = nPayloadLength; /* [FIX] fixed-packet: length prop unreliable after RX_DONE */
								PAN312x_Read_Fifo(vectRxBuffer, cRxData);
								PAN312x_Irq_Clear_RxDone_Status();
								if(memcmp(vectRxBuffer, vectExpectBuffer, nPayloadLength) == 0){
										rx_cnt ++ ;
								}else{
										rx_error_cnt++;
								}
								printf("Master Rx Ok Cnt:%"PRIu32", Err Cnt:%"PRIu32", Rssi:-%d",rx_cnt, rx_error_cnt, rssi_value);
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
								{ volatile uint32_t txd_wait_t = 0; while(!xTxDoneFlag){ if(++txd_wait_t > 2000000UL) break; } }
								xTxDoneFlag = S_RESET;
								if(!xAckTimeoutFlag){
										tx_cnt++;
										printf("Master Tx Ok Cnt:%"PRIu32", Err Cnt:%"PRIu32"", tx_cnt, rx_error_cnt);
								}else{
										xAckTimeoutFlag = S_RESET;
										rx_error_cnt++;
										printf("Master Tx Ok Cnt:%"PRIu32", Err Cnt:%"PRIu32"", tx_cnt, rx_error_cnt);
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
	
		g_carrier_active = false;   /* FACTORY TEST: leave single-carrier mode */
		PAN312x_RadioInit(&device_config.RadioInit);
		Set_PAN312x_RF_Mode_Config();
	
		while(1) {
				if((device_config.rf_mode == 1) || (device_config.rf_mode == 4)) {
						if(xRxDoneFlag){
								bsp_LedOn(BLUE_LED);
								xRxDoneFlag = S_RESET;
								rssi_value = PAN312x_GetRSSI();
								cRxData = nPayloadLength; /* [FIX] fixed-packet: length prop unreliable after RX_DONE */
								PAN312x_Read_Fifo(vectRxBuffer, cRxData);
								PAN312x_Irq_Clear_RxDone_Status();
								if(memcmp(vectRxBuffer, vectExpectBuffer, nPayloadLength) == 0){
										rx_cnt ++ ;
								}else{
										rx_error_cnt++;
								}
								printf("Slave Ok Cnt:%"PRIu32", Err Cnt:%"PRIu32", Rssi:-%d",rx_cnt, rx_error_cnt, rssi_value);
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
								{ volatile uint32_t txd_wait_t = 0; while(!xTxDoneFlag){ if(++txd_wait_t > 2000000UL) break; } }
								xTxDoneFlag = S_RESET;
								if(!xAckTimeoutFlag){
										tx_cnt++;
										printf("Slave Ok Cnt:%"PRIu32", Err Cnt:%"PRIu32"", tx_cnt, rx_error_cnt);
								}else{
										xAckTimeoutFlag = S_RESET;
										rx_error_cnt++;
										printf("Slave Ok Cnt:%"PRIu32", Err Cnt:%"PRIu32"", tx_cnt, rx_error_cnt);
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
/* ===================== PingPong 对测（双向收发测试） ===================== */
/* 用一个变量 g_pingpong_role 决定本板角色：
     0 = PING（发送者）：先发，等待对方回 PONG 回声，循环
     1 = PONG（接收者）：先收，收到后回显，循环
   发送内容固定为 vectTxBuffer（与 vectExpectBuffer 内容一致），
   接收端用 memcmp(vectRxBuffer, vectExpectBuffer) 校验，便于直观对测。
   用法：先用 AT 命令配置 频率/速率/功率/间隔，再发送 AT+PINGPONG=0 或 =1 启动。
    也可在编译前修改 PINGPONG_ROLE_DEFAULT，把整块板固定烧成 发送/接收 板。    */

/* ---------- PingPong 非阻塞状态机 ----------
 * 原 PingPong_Test 内部 while(1) 会阻塞主循环，导致 AT 命令无法处理。
 * 现拆为两部分：
 *   PingPong_Test()  —— 只做初始化 + 置 g_pp_active = true + 设定初始状态，立即返回。
 *   PingPong_Step()  —— 在 Firmware_App 主循环中每轮调用一次，执行非阻塞状态机。
 * 这样 PingPong 运行时 AT_Command_Process() 仍能正常收发命令。                */

/* PingPong run state was moved up next to g_carrier_active (see line ~153)
   so that AT_Enter_Carrier can stop the state machine before latching the
   single-carrier mode. */

/* 前向声明，定义在 AT_PingPong 之后 */
void PingPong_Step(void);
static void PingPong_Step_Ping(void);
static void PingPong_Step_Pong(void);
static int pp_EnterReady(void);

/* [FIX] Enter_Ready retried until the chip accepts it: right after RX/TX the
   chip is CTS-busy and a single naked GO_READY is silently dropped by the
   driver, so every following void call in Set_PAN312x_RF_Mode_Config (IRQ
   masks, packet config, Enter_Rx) fails unnoticed - root cause of the
   STM32 PingPong failure. Bounded: 50 tries x 1 ms = ~50 ms cap. */
static int pp_EnterReady(void)
{
    int rdy = -10;
    int k = 0;
    while (rdy == -10 && k++ < 50) {
        rdy = PAN312x_Enter_Ready();
        if (rdy == -10) {
            bsp_DelayMS(1);
        }
    }
    return rdy;
}

/* [DIAG] One-shot full chip snapshot. Every field disambiguates one failure. */
static void pp_Dump(const char *tag)
{
    uint8_t cst;
    uint16_t fifo;
    long rssi;
    PAN312xIrqs st;
    unsigned long mask;
    mask = (unsigned long)PAN312x_Get_GpioIrq_EnableStatus();
    PAN312x_Irq_Get_Status(&st);
    cst = PAN312x_Get_ChipState();
    fifo = PAN312x_Get_RxLengthInFifo();
    rssi = (long)PAN312x_GetRSSI();
    /* C351 printf consumes a 32-bit slot per conversion: every argument is
       widened to (unsigned long)/(long) and read with %lX/%ld. */
    printf("[%s] MASK=%08lX IRQ=%02lX%02lX%02lX%02lX CST=%02lX FIFO=%04lX RSSI=%ld DIO8=%lu P3IE=%02lX IM=%02lX%02lX\r\n",
        tag, mask,
        (unsigned long)st.u0.IRQ_STATUS0, (unsigned long)st.u1.IRQ_STATUS1,
        (unsigned long)st.u2.IRQ_STATUS2, (unsigned long)st.u3.IRQ_STATUS3,
        (unsigned long)cst, (unsigned long)fifo, rssi,
        (unsigned long)DIO8_GetState(), (unsigned long)P3IE,
        (unsigned long)P3IM0, (unsigned long)P3IM1);
}

/* [POLL] The DIO8 -> P3.2 port-interrupt chain never delivers TX_DONE/RX_DONE
   to the software flags on this board. The chip IRQ status register DOES
   reflect events (verified: TXFAIL shows STATUS0.TX_DONE=1). Poll it directly. */
static uint8_t pp_ChipStatus0(void)
{
    PAN312xIrqs st;
    uint8_t s0;
    st.u0.IRQ_STATUS0 = 0;
    PAN312x_Irq_Get_Status(&st);
    s0 = st.u0.IRQ_STATUS0;
    if (s0 & 0x02) g_rxdone_seen_cnt++;   /* [DIAG] RX_DONE was actually present */
    return s0;
}
static bool pp_WaitTxDone(uint32_t timeout_ms)
{
    uint32_t start = HAL_GetTick();
    /* Do NOT hammer the SPI while the PA is transmitting. The chip is busy
       and constant GET_STATUS/CTS reads desync its command layer (observed:
       afterTX every property read returns CTS_ERROR -10). Poll slowly and
       give the radio a settle delay after TX_DONE before touching it again. */
    bsp_DelayMS(2);
    while (HAL_GetTick() - start < timeout_ms) {
        if (pp_ChipStatus0() & 0x01) {   /* TX_DONE */
            bsp_DelayMS(2);             /* let the chip leave TX state */
            return true;
        }
        bsp_DelayMS(2);
    }
    return false;
}
static bool pp_IsRxDone(void)
{
    /* Throttle SPI reads to ~1 per 5 ms. The main loop calls this thousands
       of times per second; reading the chip that fast desyncs its command
       layer (CTS_ERROR -10 afterwards). Cache the result between reads. */
    static uint32_t last = 0;
    static bool cached = false;
    uint32_t now = HAL_GetTick();
    if ((uint32_t)(now - last) >= 5UL) {
        last = now;
        cached = ((pp_ChipStatus0() & 0x02) != 0);
    }
    return cached;
}

/* [HEAL] Port of the STM32 fix that made the link stable: verify the chip
   accepts property WRITES (not just reads), full-reinit if desynced. */
static int pp_WaitPropReady(void)
{
    unsigned long m = 0, r = 0;
    int k = 0, round;
    for (round = 0; round < 2; round++) {
        k = 0;
        for (;;) {
            m = (unsigned long)PAN312x_Get_GpioIrq_EnableStatus();
            if ((m & 0x1000UL) && (m < 0x10000UL)) {
                PAN312x_GpioIrq_EnableStatus(m);
                r = (unsigned long)PAN312x_Get_GpioIrq_EnableStatus();
                if (r == m) return round;
            }
            if (++k >= 200) break;
            bsp_DelayUS(500);
        }
        if (round == 0) {
            printf("WARN: prop layer stuck rd=%lX wr=%lX reinit\r\n", m, r);
            PAN312x_RadioInit(&device_config.RadioInit);
            PAN312x_PktInit(&PacketInit);
            PAN312x_CrcInit(&CrcInit);
            PAN312x_System_Ctrl((PAN312xSysCtrl)0); /* [FIX] no auto-clear: keep RX_DONE latched for the 5ms poll */
            PAN312x_Irq_Clear_AllStatus();
            bsp_DelayMS(2);
        }
    }
    return -1;
}


static void PingPong_Test(void)
{
    g_carrier_active = false;   /* PingPong start leaves single-carrier mode */
    tx_cnt = 0; rx_cnt = 0; rx_error_cnt = 0; tx_total_cnt = 0;
    xRxDoneFlag = S_RESET; xTxDoneFlag = S_RESET; xAckTimeoutFlag = S_RESET;

    /* [RF] Force the exact radio parameters from the factory test that is
       proven working on these two boards (Master+Slave both use these),
       bypassing whatever stale config was loaded from Flash. */
    device_config.RadioInit.FrequencyBase = 491300000;
    device_config.RadioInit.FrequencyStep = 0;
    device_config.RadioInit.FrequencyChannelNumber = 0;
    device_config.RadioInit.ModulationSelect = MOD_2FSK;
    device_config.RadioInit.DataRate = 10000;
    device_config.RadioInit.TxDeviation = 10000;
    device_config.RadioInit.RxDeviation = 10000;
    device_config.RadioInit.PowerSelect = POWER_LDO_0402;
    device_config.RadioInit.Power = POWER_20dBm;
    device_config.tx_mode = 2;
    device_config.tx_period = 50;
    printf("RF: freq=%lu rate=%lu dev=%lu\r\n",
        (unsigned long)device_config.RadioInit.FrequencyBase,
        (unsigned long)device_config.RadioInit.DataRate,
        (unsigned long)device_config.RadioInit.TxDeviation);

    PAN312x_RadioInit(&device_config.RadioInit);
    { uint8_t fb[4]={0,0,0,0}; PAN312x_Get_OP_Reg(0x0195,4,fb);
      printf("FREQ-WORD: %02lX%02lX%02lX%02lX\r\n", (unsigned long)fb[3],(unsigned long)fb[2],(unsigned long)fb[1],(unsigned long)fb[0]); }
    /* RadioInit 会复位芯片，需重做 packet/CRC/IRQ-auto-clear 配置，
       否则 IRQ 线持续拉高，后续 DIO8 边沿中断不再触发（RX 看起来完全死）。 */
    PAN312x_PktInit(&PacketInit);
    PAN312x_CrcInit(&CrcInit);
    PAN312x_System_Ctrl((PAN312xSysCtrl)0); /* [FIX] no auto-clear: keep RX_DONE latched for the 5ms poll */

    device_config.tx_mode = 2;          /* match factory test: manual FIFO + Enter_Tx */
    /* [FIX] removed the Set_PAN312x_RF_Mode_Config() that was here: the role
       branch below configures right after it, and the back-to-back double
       call made the 2nd Enter_Rx come back CTS -10 - the first rejected
       command that desyncs the chip command layer (seen on STM32). */

    printf("PingPong start, role=%s, tx_period=%u\r\n",
           g_pingpong_role == 0 ? "PING(send)" : "PONG(recv)", device_config.tx_period);

    if (g_pingpong_role == 0) {
        device_config.rf_mode = 2;          /* PING 先发 */
        Set_PAN312x_RF_Mode_Config();
        bsp_StartTimer(2, device_config.tx_period);
        g_pp_state = PP_STATE_IDLE;
        pp_Dump("PING-boot");
    } else {
        device_config.rf_mode = 1;          /* PONG 先收 */
        Set_PAN312x_RF_Mode_Config();
        bsp_StartTimer(1, 5 * 1000);
        g_pp_state = PP_STATE_RX_WAIT;
        pp_Dump("PONG-boot");
    }

    /* PingPong 状态机在 Firmware_App 主循环中周期调用 PingPong_Step()，
       非阻塞运行，不占用主循环，AT 命令可正常处理。
       以下 while(0) 循环体已整体移至 PingPong_Step()。 */
    g_pp_active = true;
    return;
    while (0) {
        if ((device_config.rf_mode == 1) || (device_config.rf_mode == 4)) {
            if (xRxDoneFlag) {
                bsp_LedOn(BLUE_LED);
                xRxDoneFlag = S_RESET;
                rssi_value = PAN312x_GetRSSI();
                cRxData = nPayloadLength;
                PAN312x_Read_Fifo(vectRxBuffer, cRxData);
                PAN312x_Irq_Clear_RxDone_Status();
                if (memcmp(vectRxBuffer, vectExpectBuffer, nPayloadLength) == 0)
                    rx_cnt++;
                else
                    rx_error_cnt++;
                printf("Role %s Rx Ok:%"PRIu32" Err:%"PRIu32" Rssi:-%d\r\n",
                       g_pingpong_role == 0 ? "PING" : "PONG", rx_cnt, rx_error_cnt, rssi_value);
                bsp_DelayMS(100);
                bsp_LedOff(BLUE_LED);

                device_config.rf_mode = 2;
                PAN312x_Enter_Ready();
                Set_PAN312x_RF_Mode_Config();
                bsp_StartTimer(2, device_config.tx_period);
            }
        }

        if ((device_config.rf_mode == 2) || (device_config.rf_mode == 3)) {
            if (bsp_CheckTimer(2)) {
                bsp_LedOn(GREEN_LED);
                DIO8_EnableInterrupt();
                PAN312x_Flush_TxFifo();
                PAN312x_Reset_Modem();
                PAN312x_Write_Fifo((uint8_t *)vectTxBuffer, nPayloadLength);
                PAN312x_Enter_Tx(0, 0, nPayloadLength);
                { uint32_t txd_wait_t = 0; while (!xTxDoneFlag) { if (++txd_wait_t > 3600000UL) break; } }
                xTxDoneFlag = S_RESET;
                tx_cnt++;
                printf("Role %s Tx Ok:%"PRIu32" Err:%"PRIu32"\r\n",
                       g_pingpong_role == 0 ? "PING" : "PONG", tx_cnt, rx_error_cnt);
                bsp_LedOff(GREEN_LED);

                device_config.rf_mode = 1;
                PAN312x_Enter_Ready();
                Set_PAN312x_RF_Mode_Config();
                bsp_StopTimer(2);
                /* 进入接收前启动链路看门狗：5s 内未收到回包则判定链路异常 */
                bsp_StartTimer(1, 5 * 1000);
            }
        }

        if (bsp_CheckTimer(1)) {
            bsp_StopTimer(1);
            bsp_StopTimer(2);
            if (g_pingpong_role == 0) {
                printf("PingPong PING timeout: ping=%"PRIu32" pong=%"PRIu32" err=%"PRIu32"\r\n",
                       tx_cnt, rx_cnt, rx_error_cnt);
                AT_Send_Response(AT_RESPONSE_ERROR, "Timeout\r\n");
                break;
            }
            /* PONG 作为接收端不退出，重新计时继续等待 */
            bsp_StartTimer(1, 5 * 1000);
        }
    }
}

/* Power-up default entry: enter the unmodulated carrier and freeze every
   mechanism that could later rewrite the RF working state. */
#if CARRIER_AUTO_ON_BOOT
static void Carrier_Enter_Default(void)
{
    g_pp_active      = false;
    g_pp_state       = PP_STATE_DISABLED;
    bsp_StopTimer(1);
    bsp_StopTimer(2);
    wakeup_flag      = false;
    Carrier_Enter_Now();
    g_carrier_active = true;
    g_carrier_suspended = false;
}
#endif /* CARRIER_AUTO_ON_BOOT */

static void AT_PingPong(const char* params)
{
    /* 查询模式 AT+PINGPONG? —— 报告当前角色和运行状态 */
    if (strcmp(params, "?") == 0) {
        printf("\r\n+PINGPONG:%d,%s", g_pingpong_role,
               g_pp_active ? "active" : "idle");
        AT_Send_Response(AT_RESPONSE_OK, NULL);
        return;
    }

    if (strlen(params) == 0) {
        /* 执行模式 AT+PINGPONG（无参数）—— 切换：激活则停止，未激活则启动 */
        if (g_pp_active) {
            g_pp_active = false;
            g_pp_state = PP_STATE_DISABLED;
            printf("PingPong stopped\r\n");
        } else {
            PingPong_Test();
            printf("PingPong started, role=%s\r\n",
                   g_pingpong_role == 0 ? "PING(send)" : "PONG(recv)");
        }
        AT_Send_Response(AT_RESPONSE_OK, NULL);
        return;
    }

    /* 设置角色并启动：AT+PINGPONG=0 / AT+PINGPONG=1 */
    if (params[0] == '0') {
        g_pingpong_role = 0;
    } else if (params[0] == '1') {
        g_pingpong_role = 1;
    } else {
        AT_Send_Response(AT_RESPONSE_ERROR, "Role must be 0 (PING) or 1 (PONG)\r\n");
        return;
    }
    PingPong_Test();
    AT_Send_Response(AT_RESPONSE_OK, NULL);
}

/* ============================================================
 * PingPong 非阻塞状态机：在 Firmware_App 主循环中每轮调用一次
 * ============================================================ */
void PingPong_Step(void)
{
    if (!g_pp_active) {
        return;
    }

    if (g_pingpong_role == 0) {
        PingPong_Step_Ping();
    } else {
        PingPong_Step_Pong();
    }
}

/* PING 发送端状态机 */
static void PingPong_Step_Ping(void)
{
    if (g_pp_state == PP_STATE_IDLE) {
        /* 等待 timer2 触发发送 */
        if (bsp_CheckTimer(2)) {
            bsp_LedOn(GREEN_LED);
            /* [FIX] wait until the chip takes GO_READY before touching the FIFO:
               otherwise the write lands on a busy chip and START_TX runs empty
               (accepted, but never transmits: no TX_DONE, peer hears nothing). */
            pp_EnterReady();
            xTxDoneFlag = S_RESET;
            PAN312x_Irq_Clear_AllStatus();
            DIO8_EnableInterrupt();
            PAN312x_Flush_TxFifo();
            PAN312x_Reset_Modem();
            PAN312x_Write_Fifo((uint8_t *)vectTxBuffer, nPayloadLength);
            { int txr = -10; int tk = 0;
              while (txr == -10 && tk++ < 50) {
                  txr = PAN312x_Enter_Tx(0, 0, nPayloadLength);
                  if (txr == -10) {
                      bsp_DelayMS(1);
                  }
              } }
            {
              if (pp_WaitTxDone(1000UL)) tx_cnt++;
              else {
                  rx_error_cnt++;
                  printf("TX FAILED: IRQ timeout\r\n");
                  pp_Dump("TXFAIL");
              }
            }
            xTxDoneFlag = S_RESET;
            printf("PING Tx Ok:%"PRIu32" Err:%"PRIu32"\r\n",
                   tx_cnt, rx_error_cnt);
            bsp_LedOff(GREEN_LED);

            device_config.rf_mode = 1;
            pp_EnterReady();
            Set_PAN312x_RF_Mode_Config();
            bsp_StopTimer(2);
            /* 进入接收前启动链路看门狗：5s 内未收到回包则重试 */
            bsp_StartTimer(1, 5 * 1000);
            g_pp_state = PP_STATE_RX_WAIT;
        }
    } else if (g_pp_state == PP_STATE_RX_WAIT) {
        if (pp_IsRxDone()) {
            bsp_LedOn(BLUE_LED);
            xRxDoneFlag = S_RESET;
            rssi_value = PAN312x_GetRSSI();
            pp_Dump("RXDONE");
            /* [FIX] fixed-packet mode: the length property reads as garbage
               right after RX_DONE (STM32 measured 0xFFF6) and memcmp with
               that value reads out of bounds. Peer always sends
               nPayloadLength bytes - read/compare that directly. */
            cRxData = nPayloadLength;
            PAN312x_Read_Fifo(vectRxBuffer, cRxData);
            PAN312x_Irq_Clear_RxDone_Status();
            if (memcmp(vectRxBuffer, vectExpectBuffer, nPayloadLength) == 0)
                rx_cnt++;
            else
                rx_error_cnt++;
            printf("PING Rx Ok:%"PRIu32" Err:%"PRIu32" Rssi:-%d\r\n",
                   rx_cnt, rx_error_cnt, rssi_value);
            bsp_DelayMS(100);
            bsp_LedOff(BLUE_LED);

            device_config.rf_mode = 2;
            pp_EnterReady();
            Set_PAN312x_RF_Mode_Config();
            bsp_StartTimer(2, device_config.tx_period);
            g_pp_state = PP_STATE_IDLE;
        } else if (bsp_CheckTimer(1)) {
            /* 5s 看门狗超时：重试发送（不退出，持续对测） */
            bsp_StopTimer(1);
            bsp_StopTimer(2);
            printf("PING timeout: tx=%"PRIu32" rx=%"PRIu32" err=%"PRIu32" -- retry\r\n",
                   tx_cnt, rx_cnt, rx_error_cnt);
            device_config.rf_mode = 2;
            pp_EnterReady();
            Set_PAN312x_RF_Mode_Config();
            bsp_StartTimer(2, device_config.tx_period);
            g_pp_state = PP_STATE_IDLE;
        }
    }
}

/* PONG 接收端状态机 */
static void PingPong_Step_Pong(void)
{
    if (g_pp_state == PP_STATE_RX_WAIT) {
        if (pp_IsRxDone()) {
            bsp_LedOn(BLUE_LED);
            xRxDoneFlag = S_RESET;
            rssi_value = PAN312x_GetRSSI();
            pp_Dump("RXDONE");
            /* [FIX] fixed-packet mode: the length property reads as garbage
               right after RX_DONE (STM32 measured 0xFFF6) and memcmp with
               that value reads out of bounds. Peer always sends
               nPayloadLength bytes - read/compare that directly. */
            cRxData = nPayloadLength;
            PAN312x_Read_Fifo(vectRxBuffer, cRxData);
            PAN312x_Irq_Clear_RxDone_Status();
            if (memcmp(vectRxBuffer, vectExpectBuffer, nPayloadLength) == 0)
                rx_cnt++;
            else
                rx_error_cnt++;
            printf("PONG Rx Ok:%"PRIu32" Err:%"PRIu32" Rssi:-%d\r\n",
                   rx_cnt, rx_error_cnt, rssi_value);
            bsp_DelayMS(100);
            bsp_LedOff(BLUE_LED);

            device_config.rf_mode = 2;
            pp_EnterReady();
            Set_PAN312x_RF_Mode_Config();
            bsp_StartTimer(2, device_config.tx_period);
            g_pp_state = PP_STATE_IDLE;
        } else if (bsp_CheckTimer(1)) {
            /* 看门狗到期：重计时，继续等待接收（不退出） */
            bsp_StopTimer(1);
            printf("PONG keep waiting: rx=%"PRIu32" err=%"PRIu32" rxdseen=%"PRIu32"\r\n",
                   rx_cnt, rx_error_cnt, g_rxdone_seen_cnt);
            pp_Dump("PONG-HB");
            { uint8_t peek[8] = {0,0,0,0,0,0,0,0};
              PAN312x_Read_Fifo(peek, 8);
              printf("FIFO-PEEK: %02lX%02lX%02lX%02lX%02lX%02lX%02lX%02lX\r\n",
                (unsigned long)peek[0],(unsigned long)peek[1],(unsigned long)peek[2],(unsigned long)peek[3],
                (unsigned long)peek[4],(unsigned long)peek[5],(unsigned long)peek[6],(unsigned long)peek[7]); }
            device_config.rf_mode = 1;
            pp_EnterReady();
            Set_PAN312x_RF_Mode_Config();
            PAN312x_Irq_Clear_AllStatus();
            DIO8_EnableInterrupt();
            bsp_StartTimer(1, 5 * 1000);
            /* g_pp_state 保持 PP_STATE_RX_WAIT */
        }
    } else if (g_pp_state == PP_STATE_IDLE) {
        /* 等待 timer2 触发回包发送 */
        if (bsp_CheckTimer(2)) {
            bsp_LedOn(GREEN_LED);
            /* [FIX] wait until the chip takes GO_READY before touching the FIFO:
               otherwise the write lands on a busy chip and START_TX runs empty
               (accepted, but never transmits: no TX_DONE, peer hears nothing). */
            pp_EnterReady();
            xTxDoneFlag = S_RESET;
            PAN312x_Irq_Clear_AllStatus();
            DIO8_EnableInterrupt();
            PAN312x_Flush_TxFifo();
            PAN312x_Reset_Modem();
            PAN312x_Write_Fifo((uint8_t *)vectTxBuffer, nPayloadLength);
            { int txr = -10; int tk = 0;
              while (txr == -10 && tk++ < 50) {
                  txr = PAN312x_Enter_Tx(0, 0, nPayloadLength);
                  if (txr == -10) {
                      bsp_DelayMS(1);
                  }
              } }
            {
              if (pp_WaitTxDone(1000UL)) tx_cnt++;
              else {
                  rx_error_cnt++;
                  printf("TX FAILED: IRQ timeout\r\n");
                  pp_Dump("TXFAIL");
              }
            }
            xTxDoneFlag = S_RESET;
            printf("PONG Tx Ok:%"PRIu32" Err:%"PRIu32"\r\n",
                   tx_cnt, rx_error_cnt);
            bsp_LedOff(GREEN_LED);

            device_config.rf_mode = 1;
            pp_EnterReady();
            Set_PAN312x_RF_Mode_Config();
            bsp_StopTimer(2);
            bsp_StartTimer(1, 5 * 1000);
            g_pp_state = PP_STATE_RX_WAIT;
        }
    }
}

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
        HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);//TM3�жϣ������ȼ�0�������ȼ�0
        HAL_NVIC_EnableIRQ(TIM2_IRQn);//IRQͨ����ʹ��
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
//��ʱ�����غ���  /* TIM Update event */
void HAL_TIM_PeriodElapsedCallback(void)
{
    uint8_t rf_status;
		if (wakeup_cnt < 5) {
				wakeup_cnt++;


				PAN312x_SPI_Init();
				PAN312x_DIO8_INPUT();
				DIO8_EnableInterrupt();
				PAN312x_Read(R003, &rf_status);
//				printf("rf status: %x\r\n", rf_status);
				if((rf_status == 0x01) || (rf_status == 0x02)){
						//��ʾPAN312x����deepsleep ����sleepģʽ
						//ִ�л���ָ���PAN312x����
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
    printf("Config: size=%lu freq=%lu rate=%lu txdev=%lu rxdev=%lu\r\n",
        (unsigned long)sizeof(DeviceConfig), (unsigned long)config->RadioInit.FrequencyBase,
        (unsigned long)config->RadioInit.DataRate, (unsigned long)config->RadioInit.TxDeviation,
        (unsigned long)config->RadioInit.RxDeviation);
    printf("Config: txmode=%lu rfmode=%lu period=%lu crc=%04lX\r\n",
        (unsigned long)config->tx_mode, (unsigned long)config->rf_mode,
        (unsigned long)config->tx_period, (unsigned long)config->crc);
}

// Ĭ������
void DeviceConfig_Init(DeviceConfig *config)
{
		// �������������ṹ�壨��������ֽڣ�
    memset(config, 0, sizeof(DeviceConfig));
	
    config->RadioInit.FrequencyBase = 490300000;
    config->RadioInit.FrequencyStep = 0;
    config->RadioInit.FrequencyChannelNumber = 0;
    config->RadioInit.ModulationSelect = MOD_2FSK;
    config->RadioInit.DataRate = 50000;
    config->RadioInit.TxDeviation = 25000;
    config->RadioInit.RxDeviation = 25000;
    config->RadioInit.PowerSelect = POWER_LDO_0402;
    config->RadioInit.Power = POWER_20dBm;
    config->tx_mode = 2;
    config->rf_mode = 2;
		config->tx_period = 50;
    config->crc = DeviceConfig_CalculateCRC(config);
}

// �������õ�Flash
bool DeviceConfig_Save(DeviceConfig *config)
{
    // ����CRCУ��ֵ
    config->crc = DeviceConfig_CalculateCRC(config);
    
    // ����Ŀ��ҳ
    if (Flash_Erase_Page(CONFIG_FLASH_ADDR) != HAL_OK) {
        return false;
    }
    
    // д����������
    if (Flash_Write_Data(CONFIG_FLASH_ADDR, config, sizeof(DeviceConfig)) != HAL_OK) {
        return false;
    }
		
//		printf("Saving configuration:\r\n");
//		DeviceConfig_DebugPrint(config);
    
    return true;
}

// ��Flash��������
bool DeviceConfig_Load(DeviceConfig *config)
{
    // ��ȡ��������
    Flash_Read_Data(CONFIG_FLASH_ADDR, config, sizeof(DeviceConfig));
	
		// �������
//    printf("Loaded configuration:\r\n");
//		DeviceConfig_DebugPrint(config);
    
    // ��֤������Ч��
    return DeviceConfig_IsValid(config);
}

// ��֤�������ݵ���Ч��
bool DeviceConfig_IsValid(DeviceConfig *config)
{
    uint16_t stored_crc;
    uint16_t calculated_crc;
    stored_crc = config->crc;
    // ���Flash�Ƿ�Ϊ�գ�ȫΪ0xFF��
    if (Flash_Is_Empty(CONFIG_FLASH_ADDR, sizeof(DeviceConfig))) {
        return false;
    }
    
    // ���CRCУ��
    calculated_crc = DeviceConfig_CalculateCRC(config);
    
    return (stored_crc == calculated_crc);
}

// �����������ݵ�CRCУ��ֵ����ʵ�֣�
uint16_t DeviceConfig_CalculateCRC(DeviceConfig *config)
{
		uint16_t crc = 0;
		uint8_t *dat;
		uint32_t size;
		uint32_t i;
    
    // ������ʱ������ȷ�����޸�ԭʼ����
    DeviceConfig temp_config;
    temp_config = *config; /* C89: no variable aggregate initializer */
    
    // ��CRC�ֶ����㣬ȷ�������һ����
    temp_config.crc = 0;
    
    // ���������ֶε�CRC������crc�ֶα�����
    dat = (uint8_t*)&temp_config;
    size = sizeof(DeviceConfig) - sizeof(temp_config.crc);
    
    for (i = 0; i < size; i++) {
        crc += dat[i];
    }
    
    return crc;
}

void Init_PAN312x_Gpio_Mode()
{
		PAN312x_Iomux_Gpio(IOMUX_GPIO0_AS_GPIO);
    PAN312x_Iomux_Gpio(IOMUX_GPIO1_AS_GPIO);
    PAN312x_Iomux_Gpio(IOMUX_GPIO2_AS_GPIO);
    PAN312x_Iomux_Gpio(IOMUX_GPIO10_AS_GPIO);
    PAN312x_Set_Gpio_Mode((PAN312x_GPIO_PIN_0 | PAN312x_GPIO_PIN_1 |PAN312x_GPIO_PIN_2 | PAN312x_GPIO_PIN_10), GPIO_INPUT_MODE);
}

/**********************************************************************************************************/
static void printf_logo(void)
{
		printf("\r\n");
    printf("################################################\r\n");
    printf("arch             : Ai-SG01\r\n");	
		printf("company          : Ai-Thinker\r\n");
    printf("sdk_version      : pending radio init\r\n");		
    printf("firmware_version : %s\r\n", FIRMWARE_VERSION);
		printf("compile_time     : %s-%s\r\n", __DATE__, __TIME__);
		printf("\r\n");
		printf("ready\r\n");
    printf("################################################\r\n");
}

/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    ��: ��
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
void Firmware_App(void)
{
		bsp_Init();		        /* Ӳ����ʼ�� */
    AT_Command_Init();	// ��ʼ��ATָ��ģ��
	
		printf_logo();
	
		if (DeviceConfig_Load(&device_config)) {
        printf("Configuration loaded from Flash\r\n");
				if (device_config.RadioInit.PowerSelect == POWER_DCDC_0402 || 
						device_config.RadioInit.PowerSelect == POWER_DCDC_0603) {
						dcdc_enable = true;
				} else {
						dcdc_enable = false;
				}
    } else {
        printf("No valid configuration found, using defaults\r\n");
        // ʹ��Ĭ������
        DeviceConfig_Init(&device_config);
        // ����Ĭ�����õ�Flash
        if (DeviceConfig_Save(&device_config)) {
//            printf("Default configuration saved to Flash\r\n");
        } else {
//            printf("Failed to save default configuration!\r\n");
        }
    }
		
		// ��ӡ��ǰ����
    DeviceConfig_DebugPrint(&device_config);
   
    PAN312x_Fsk_Init();
    { int fwret = PAN312x_Get_FwId(&fwid);
      printf("RADIO: fwid_ret=%ld fwid=%lu DIO8=%lu\r\n", (long)fwret, (unsigned long)fwid, (unsigned long)DIO8_GetState()); }
    /* [SPI-SELFTEST] Read the firmware-ID register 20 times. It is a fixed
       value (3). If SPI wiring is sound and stable, all 20 reads agree.
       Any jump / zero / mismatch => MISO/CSN/SCK wiring or timing fault. */
    { int k, good=0, ret; uint16_t v;
      for (k=0; k<20; k++) {
        v=0; ret=PAN312x_Get_FwId(&v);
        if (ret==0 && v==3) good++;
        bsp_DelayUS(200);
      }
      printf("SPI-TEST: fwid_ok=%d/20 (expect 20)\r\n", good);
    }
    
    PAN312x_RadioInit(&device_config.RadioInit);
		PAN312x_PktInit(&PacketInit);
		PAN312x_CrcInit(&CrcInit);
        { uint8_t r195[4]={0,0,0,0}; PAN312x_Get_OP_Reg(0x0195,4,r195);
          printf("BOOT: R195=%02lX%02lX%02lX%02lX fwid=%lu\r\n", (unsigned long)r195[3],(unsigned long)r195[2],(unsigned long)r195[1],(unsigned long)r195[0],(unsigned long)fwid); }
	
		PAN312x_System_Ctrl((PAN312xSysCtrl)0); /* [FIX] no auto-clear: keep RX_DONE latched for the 5ms poll */
    
    //Ĭ��TX
//    device_config.rf_mode = 2;
    
//    PAN312x_Set_TxPacket_Config(TxFixedPackedCrcEnable);
//    PAN312x_GpioIrq_Config((PAN312xIrqList)(IRQ_MASK_TX_DONE | IRQ_MASK_WAKEUP), S_ENABLE);
		Set_PAN312x_RF_Mode_Config();
		if (device_config.tx_mode == 0) {
//				device_config.tx_period = 500;
				bsp_StartTimer(1, device_config.tx_period);
		}
    
    PAN312x_Irq_Clear_AllStatus();
   	
		bsp_StartAutoTimer(0, 1000); /* ����1��200ms���Զ���װ�Ķ�ʱ����������ʱ��0 */
    DIO8_EnableInterrupt();
		
		Init_PAN312x_Gpio_Mode();	//��ʼ��IO0,1,2,10Ϊ����ģʽ�����GPIOһ��ʼ����Ϊ���ģʽʱ�޷���ȷ��ȡ��ƽ
		
		MX_TIM2_Init_Ms(100);
		__HAL_TIM_CLEAR_IT(&TIM2_InitStruct, TIM_IT_UPDATE);

#if CARRIER_AUTO_ON_BOOT
		/* CARRIER build: the power-up default is the unmodulated single
		   carrier (CW) transmit mode - the very state that AT+ENTERCARRIER
		   produces. PingPong is NOT started here, otherwise its state
		   machine would rewrite the RF state right after boot. It can
		   still be started manually with AT+PINGPONG. */
		printf("Carrier auto-start on power-up (AT+ENTERCARRIER equivalent)\r\n");
		Carrier_Enter_Default();
#else
		/* PingPong auto-start on power-up; role comes from PINGPONG_ROLE_DEFAULT.
		   Boards flashed with 0 and 1 start sending/receiving immediately,
		   without waiting for any AT command. */
		printf("PingPong auto-start, role=%s (0=PING send, 1=PONG recv)\r\n",
		       g_pingpong_role == 0 ? "PING" : "PONG");
		PingPong_Test();
#endif

		while (1)
		{
        /* �ж϶�ʱ����ʱʱ�� */                                                                                                                                     
//				if (bsp_CheckTimer(0)){
//				/* ���� ÿ��100ms ����һ�� */ 
//						bsp_LedToggle(BLUE_LED); 	
//				}
				
				if (wakeup_flag && !g_pp_active) {
						if (sleep_mode == DEEP_SLEEP_MODE) {
								PAN312x_RadioInit(&device_config.RadioInit);
								PAN312x_PktInit(&PacketInit);
								PAN312x_CrcInit(&CrcInit);								
								PAN312x_System_Ctrl((PAN312xSysCtrl)0); /* [FIX] no auto-clear: keep RX_DONE latched for the 5ms poll */
								PAN312x_Irq_Clear_AllStatus();
														
//								Set_PAN312x_RF_Mode_Config();
//										printf("3333333333333333333\r\n");
						}
						sleep_mode = WAKE_UP_READY;
						wakeup_flag = false;
						if (g_carrier_active || g_carrier_suspended) {
							/* CARRIER build: a wake-up IRQ must not drop the carrier and
							   must not print an unsolicited +OK. Also rebuilds the carrier
							   after a SLEEPMODE / wake-up cycle. */
							g_carrier_suspended = false;
							Carrier_Enter_Now();
							g_carrier_active = true;
						} else {
							Set_PAN312x_RF_Mode_Config();
							AT_Send_Response(AT_RESPONSE_OK, NULL);
						}
				}

				// ����ATָ��
                AT_Command_Process();

                /* PingPong non-blocking state machine (runs when active, does not block AT commands) */
                PingPong_Step();

                if (!g_carrier_active && !g_pp_active && sleep_mode == WAKE_UP_READY && !wakeup_flag) {
						if((device_config.rf_mode == 1) || (device_config.rf_mode == 4)){
								
								if(xRxDoneFlag){
										xRxDoneFlag = S_RESET;
										rssi_value = PAN312x_GetRSSI();
										cRxData = nPayloadLength; /* [FIX] fixed-packet: length prop unreliable after RX_DONE */
										PAN312x_Read_Fifo(vectRxBuffer, cRxData);
										PAN312x_Irq_Clear_RxDone_Status();
										if(memcmp(vectRxBuffer, vectExpectBuffer, nPayloadLength) == 0){
												rx_cnt ++ ;
										}else{
												rx_error_cnt++;
										}
										printf("Ok Cnt:%"PRIu32", Err Cnt:%"PRIu32", Rssi:-%d",rx_cnt, rx_error_cnt, rssi_value);
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
										{ volatile uint32_t txd_wait_t = 0; while(!xTxDoneFlag){ if(++txd_wait_t > 2000000UL) break; } }
										xTxDoneFlag = S_RESET;
										if(!xAckTimeoutFlag){
												tx_cnt++;
												printf("Ok Cnt:%"PRIu32", Err Cnt:%"PRIu32"", tx_cnt, rx_error_cnt);
										}else{
												xAckTimeoutFlag = S_RESET;
												rx_error_cnt++;
												printf("Ok Cnt:%"PRIu32", Err Cnt:%"PRIu32"", tx_cnt, rx_error_cnt);
										}
										
										if(device_config.rf_mode == 3){
												tx_total_cnt = tx_cnt + rx_error_cnt;
										}
										bsp_LedOff(GREEN_LED);
										
										if(device_config.tx_mode == 0x00){
												//��������
												bsp_StartTimer(1, device_config.tx_period);
										}else if(device_config.tx_mode == 0x01){
												//����500��
												if(tx_total_cnt == 500){
														//���TRxMaster��
														bsp_StopTimer(1);
												}else if(tx_cnt == 500){
														//���Tx��
														bsp_StopTimer(1);
												}else{
														bsp_StartTimer(1, device_config.tx_period);
												}
										
										}else if(device_config.tx_mode == 0x02){
												//���η���
										}
								}		
						}
				}  		
		}

}

