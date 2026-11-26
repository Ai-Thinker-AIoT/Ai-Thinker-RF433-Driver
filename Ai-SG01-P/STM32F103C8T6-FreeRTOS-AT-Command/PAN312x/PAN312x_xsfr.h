/***************************************************************************************************
 * @file : PAN312X_xsfr.h
 * @brief: xdata区寄存器定义
 * @desc : 1. 所有寄存器定义前缀组成为Rxxx_, 其中xxx表示寄存器地址的16进制形式
 *         2. 32位寄存器无后缀:
 *            (1). 拆分为2个16位寄存器, 后缀为_L16和_H16, 前缀与16位寄存器地址保持一致
 *            (2). 拆分为4个8位寄存器, 后缀为_L1, _L2, _L3和_H, 前缀与8位寄存器地址保持一致
 *         3. 16为寄存器无后缀:
 *            (1). 拆分为2个8位寄存器, 后缀为_L和_H, 前缀与8位寄存器地址保持一致
 **************************************************************************************************/
#ifndef __PAN312X_XSFR_H
#define __PAN312X_XSFR_H

//--------------------------------------------------------------------------------------------------
#define   R000                                   0x000

#define  R000_WORK_MODE_Pos                     0
#define  R000_WORK_MODE_Msk                     (0x0f << R000_WORK_MODE_Pos)

#define  R000_OTP_LOAD_DONE_Pos                 6
#define  R000_OTP_LOAD_DONE_Msk                 (0x01 << R000_OTP_LOAD_DONE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R100                                   0x100

#define  R100_REG_SOFT_RST_Pos                  7
#define  R100_REG_SOFT_RST_Msk                  (0x01 << R100_REG_SOFT_RST_Pos)

//--------------------------------------------------------------------------------------------------
#define   R081_FIFO                              0x081
#define   R081                                   0x081

//--------------------------------------------------------------------------------------------------
#define   R002                                   0x002

#define  R002_REG_OPERATE_MODE_Pos              0
#define  R002_REG_OPERATE_MODE_Msk              (0x07 << R002_REG_OPERATE_MODE_Pos)

#define  R002_EN_LS_3V_Pos                      3
#define  R002_EN_LS_3V_Msk                      (0x01 << R002_EN_LS_3V_Pos)

#define  R002_REG_LDO_LOW_EN_Pos                4
#define  R002_REG_LDO_LOW_EN_Msk                (0x01 << R002_REG_LDO_LOW_EN_Pos)

#define  R002_REG_TESTMODE_EN_Pos               5
#define  R002_REG_TESTMODE_EN_Msk               (0x01 << R002_REG_TESTMODE_EN_Pos)

#define  R002_FSM_CTRL_BYPASS_Pos               6
#define  R002_FSM_CTRL_BYPASS_Msk               (0x01 << R002_FSM_CTRL_BYPASS_Pos)

#define  R002_FSM_ISO_BYPASS_Pos                7
#define  R002_FSM_ISO_BYPASS_Msk                (0x01 << R002_FSM_ISO_BYPASS_Pos)

//--------------------------------------------------------------------------------------------------
#define   R003_REG_FSM_CTRL                      0x003
#define   R003                                   0x003

//--------------------------------------------------------------------------------------------------
#define   R004                                   0x004

#define  R004_SLEEP_MODE_Pos                    0
#define  R004_SLEEP_MODE_Msk                    (0x03 << R004_SLEEP_MODE_Pos)

#define  R004_PIC_CLK_EN_Pos                    2
#define  R004_PIC_CLK_EN_Msk                    (0x01 << R004_PIC_CLK_EN_Pos)

#define  R004_REG_NRST_PIC_Pos                  3
#define  R004_REG_NRST_PIC_Msk                  (0x01 << R004_REG_NRST_PIC_Pos)

#define  R004_REG_NRST_L_Pos                    4
#define  R004_REG_NRST_L_Msk                    (0x01 << R004_REG_NRST_L_Pos)

#define  R004_REG_ENRCH_SEL_Pos                 6
#define  R004_REG_ENRCH_SEL_Msk                 (0x01 << R004_REG_ENRCH_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R005_REG_PAGE_SEL                      0x005
#define   R005                                   0x005

//--------------------------------------------------------------------------------------------------
#define   R006                                   0x006

#define  R006_LDOL_LDOH_DELAY_Pos               0
#define  R006_LDOL_LDOH_DELAY_Msk               (0x0f << R006_LDOL_LDOH_DELAY_Pos)

#define  R006_EN_PIC_PWR_Pos                    4
#define  R006_EN_PIC_PWR_Msk                    (0x01 << R006_EN_PIC_PWR_Pos)

#define  R006_EN_OTP_PWR_Pos                    5
#define  R006_EN_OTP_PWR_Msk                    (0x01 << R006_EN_OTP_PWR_Pos)

#define  R006_EN_DIG_COREPOWER_Pos              6
#define  R006_EN_DIG_COREPOWER_Msk              (0x01 << R006_EN_DIG_COREPOWER_Pos)

#define  R006_EN_DCDC_Pos                       7
#define  R006_EN_DCDC_Msk                       (0x01 << R006_EN_DCDC_Pos)

//--------------------------------------------------------------------------------------------------
#define   R007                                   0x007

#define  R007_SPI_WKTRIG_Pos                    0
#define  R007_SPI_WKTRIG_Msk                    (0x01 << R007_SPI_WKTRIG_Pos)

#define  R007_SPI_WKEN_Pos                      1
#define  R007_SPI_WKEN_Msk                      (0x01 << R007_SPI_WKEN_Pos)

#define  R007_MFSM_CLK_EN_Pos                   2
#define  R007_MFSM_CLK_EN_Msk                   (0x01 << R007_MFSM_CLK_EN_Pos)

#define  R007_REG_RCH_EN_Pos                    3
#define  R007_REG_RCH_EN_Msk                    (0x01 << R007_REG_RCH_EN_Pos)

#define  R007_EN_LPLDO2_3V_Pos                  4
#define  R007_EN_LPLDO2_3V_Msk                  (0x01 << R007_EN_LPLDO2_3V_Pos)

#define  R007_PIC_32K_EN_Pos                    5
#define  R007_PIC_32K_EN_Msk                    (0x01 << R007_PIC_32K_EN_Pos)

#define  R007_CLK32K_SEL_Pos                    6
#define  R007_CLK32K_SEL_Msk                    (0x03 << R007_CLK32K_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R008_WUT_CLEAR                         0x008
#define   R008                                   0x008

#define  R008_WUT_CLEAR_Pos                     0
#define  R008_WUT_CLEAR_Msk                     (0x01 << R008_WUT_CLEAR_Pos)

//--------------------------------------------------------------------------------------------------
#define   R009                                   0x009

#define  R009_CE_INT_Pos                        0
#define  R009_CE_INT_Msk                        (0x01 << R009_CE_INT_Pos)

#define  R009_PWR_UP_Pos                        1
#define  R009_PWR_UP_Msk                        (0x01 << R009_PWR_UP_Pos)

#define  R009_EN_LDO_HP_Pos                     2
#define  R009_EN_LDO_HP_Msk                     (0x01 << R009_EN_LDO_HP_Pos)

#define  R009_EN_PM_Pos                         3
#define  R009_EN_PM_Msk                         (0x01 << R009_EN_PM_Pos)

#define  R009_XTH_ACTIVE_EN_Pos                 4
#define  R009_XTH_ACTIVE_EN_Msk                 (0x01 << R009_XTH_ACTIVE_EN_Pos)

#define  R009_ENTER_PROG_EN_Pos                 5
#define  R009_ENTER_PROG_EN_Msk                 (0x01 << R009_ENTER_PROG_EN_Pos)

#define  R009_EN_LPLDO_ENHENCE_Pos              6
#define  R009_EN_LPLDO_ENHENCE_Msk              (0x01 << R009_EN_LPLDO_ENHENCE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R00A_WK_REQ_FLAG                       0x00a
#define   R00A                                   0x00a

#define  R00A_WK_REQ_FLAG_Pos                   0
#define  R00A_WK_REQ_FLAG_Msk                   (0x01 << R00A_WK_REQ_FLAG_Pos)

//--------------------------------------------------------------------------------------------------
#define   R00B_RCLTRIM_CNT_CLR                   0x00b
#define   R00B                                   0x00b

#define  R00B_RCLTRIM_CNT_CLR_Pos               0
#define  R00B_RCLTRIM_CNT_CLR_Msk               (0x01 << R00B_RCLTRIM_CNT_CLR_Pos)

//--------------------------------------------------------------------------------------------------
#define   R00C                                   0x00c

#define  R00C_RCLTRIM_CNT_EN_Pos                0
#define  R00C_RCLTRIM_CNT_EN_Msk                (0x01 << R00C_RCLTRIM_CNT_EN_Pos)

#define  R00C_RCLTRIM_CNT_WKEN_Pos              1
#define  R00C_RCLTRIM_CNT_WKEN_Msk              (0x01 << R00C_RCLTRIM_CNT_WKEN_Pos)

#define  R00C_RCLTRIM_CNT_INTEN_Pos             2
#define  R00C_RCLTRIM_CNT_INTEN_Msk             (0x01 << R00C_RCLTRIM_CNT_INTEN_Pos)

#define  R00C_RCLTRIM_CNT_INTF_MASK_Pos         3
#define  R00C_RCLTRIM_CNT_INTF_MASK_Msk         (0x01 << R00C_RCLTRIM_CNT_INTF_MASK_Pos)

//--------------------------------------------------------------------------------------------------
#define   R00D_RCLTRIM_CNT_OVR                   0x00d
#define   R00D                                   0x00d

//--------------------------------------------------------------------------------------------------
#define   R00E                                   0x00e

#define  R00E_XTL_QUICK_CLKEN_Pos               0
#define  R00E_XTL_QUICK_CLKEN_Msk               (0x01 << R00E_XTL_QUICK_CLKEN_Pos)

#define  R00E_XTL_QUICK_CLKSEL_Pos              1
#define  R00E_XTL_QUICK_CLKSEL_Msk              (0x01 << R00E_XTL_QUICK_CLKSEL_Pos)

#define  R00E_SPI3_EN_Pos                       2
#define  R00E_SPI3_EN_Msk                       (0x01 << R00E_SPI3_EN_Pos)

#define  R00E_RCL_XTL_TST_SEL_Pos               3
#define  R00E_RCL_XTL_TST_SEL_Msk               (0x01 << R00E_RCL_XTL_TST_SEL_Pos)

#define  R00E_GPIO3_MUX15_SEL_Pos               4
#define  R00E_GPIO3_MUX15_SEL_Msk               (0x03 << R00E_GPIO3_MUX15_SEL_Pos)

#define  R00E_EN_XTL_3V_Pos                     6
#define  R00E_EN_XTL_3V_Msk                     (0x01 << R00E_EN_XTL_3V_Pos)

#define  R00E_EN_RCL_3V_Pos                     7
#define  R00E_EN_RCL_3V_Msk                     (0x01 << R00E_EN_RCL_3V_Pos)

//--------------------------------------------------------------------------------------------------
#define   R00F                                   0x00f

#define  R00F_BOD_VSEL_V2_3V_Pos                0
#define  R00F_BOD_VSEL_V2_3V_Msk                (0x1f << R00F_BOD_VSEL_V2_3V_Pos)

#define  R00F_BOD_VSEL_3V_Pos                   5
#define  R00F_BOD_VSEL_3V_Msk                   (0x07 << R00F_BOD_VSEL_3V_Pos)

//--------------------------------------------------------------------------------------------------
#define   R010                                   0x010

#define  R010_BOD_VREF_TRIM_3V_Pos              0
#define  R010_BOD_VREF_TRIM_3V_Msk              (0x07 << R010_BOD_VREF_TRIM_3V_Pos)

#define  R010_EN_BOD_3V_Pos                     3
#define  R010_EN_BOD_3V_Msk                     (0x01 << R010_EN_BOD_3V_Pos)

#define  R010_BOD_NRST_BYPASS_Pos               4
#define  R010_BOD_NRST_BYPASS_Msk               (0x01 << R010_BOD_NRST_BYPASS_Pos)

#define  R010_LVD_WKEN_Pos                      5
#define  R010_LVD_WKEN_Msk                      (0x01 << R010_LVD_WKEN_Pos)

#define  R010_LVD_WKF_Pos                       6
#define  R010_LVD_WKF_Msk                       (0x01 << R010_LVD_WKF_Pos)

//--------------------------------------------------------------------------------------------------
#define   R011                                   0x011

#define  R011_EN_LVR_3V_Pos                     0
#define  R011_EN_LVR_3V_Msk                     (0x01 << R011_EN_LVR_3V_Pos)

#define  R011_LVR_NRST_BYPASS_Pos               1
#define  R011_LVR_NRST_BYPASS_Msk               (0x01 << R011_LVR_NRST_BYPASS_Pos)

//--------------------------------------------------------------------------------------------------
#define   R012                                   0x012

#define  R012_WUTCMP0_INTF_Pos                  0
#define  R012_WUTCMP0_INTF_Msk                  (0x01 << R012_WUTCMP0_INTF_Pos)

#define  R012_WUTCMP1_INTF_Pos                  1
#define  R012_WUTCMP1_INTF_Msk                  (0x01 << R012_WUTCMP1_INTF_Pos)

#define  R012_WUTCMP2_INTF_Pos                  2
#define  R012_WUTCMP2_INTF_Msk                  (0x01 << R012_WUTCMP2_INTF_Pos)

#define  R012_RCLTRIM_CNT_INTF_Pos              3
#define  R012_RCLTRIM_CNT_INTF_Msk              (0x01 << R012_RCLTRIM_CNT_INTF_Pos)

#define  R012_GPIO0_WKF_Pos                     4
#define  R012_GPIO0_WKF_Msk                     (0x01 << R012_GPIO0_WKF_Pos)

#define  R012_GPIO1_WKF_Pos                     5
#define  R012_GPIO1_WKF_Msk                     (0x01 << R012_GPIO1_WKF_Pos)

#define  R012_GPIO2_WKF_Pos                     6
#define  R012_GPIO2_WKF_Msk                     (0x01 << R012_GPIO2_WKF_Pos)

#define  R012_GPIO11_WKF_Pos                    7
#define  R012_GPIO11_WKF_Msk                    (0x01 << R012_GPIO11_WKF_Pos)

//--------------------------------------------------------------------------------------------------
#define   R013                                   0x013

#define  R013_GPIO3_WKF_Pos                     0
#define  R013_GPIO3_WKF_Msk                     (0x01 << R013_GPIO3_WKF_Pos)

#define  R013_GPIO4_WKF_Pos                     1
#define  R013_GPIO4_WKF_Msk                     (0x01 << R013_GPIO4_WKF_Pos)

#define  R013_GPIO5_WKF_Pos                     2
#define  R013_GPIO5_WKF_Msk                     (0x01 << R013_GPIO5_WKF_Pos)

#define  R013_GPIO6_WKF_Pos                     3
#define  R013_GPIO6_WKF_Msk                     (0x01 << R013_GPIO6_WKF_Pos)

#define  R013_GPIO7_WKF_Pos                     4
#define  R013_GPIO7_WKF_Msk                     (0x01 << R013_GPIO7_WKF_Pos)

#define  R013_GPIO8_WKF_Pos                     5
#define  R013_GPIO8_WKF_Msk                     (0x01 << R013_GPIO8_WKF_Pos)

#define  R013_GPIO9_WKF_Pos                     6
#define  R013_GPIO9_WKF_Msk                     (0x01 << R013_GPIO9_WKF_Pos)

#define  R013_GPIO10_WKF_Pos                    7
#define  R013_GPIO10_WKF_Msk                    (0x01 << R013_GPIO10_WKF_Pos)

//--------------------------------------------------------------------------------------------------
#define   R014                                   0x014

#define  R014_GPIO3_MUX_Pos                     0
#define  R014_GPIO3_MUX_Msk                     (0x0f << R014_GPIO3_MUX_Pos)

#define  R014_CSK_MUX_Pos                       4
#define  R014_CSK_MUX_Msk                       (0x07 << R014_CSK_MUX_Pos)

#define  R014_GPIO4_MUX_Pos                     R014_CSK_MUX_Pos
#define  R014_GPIO4_MUX_Msk                     R014_CSK_MUX_Msk

#define  R014_SPI_WKF_Pos                       7
#define  R014_SPI_WKF_Msk                       (0x01 << R014_SPI_WKF_Pos)

//--------------------------------------------------------------------------------------------------
#define   R015                                   0x015

#define  R015_MOSI_MUX_Pos                      0
#define  R015_MOSI_MUX_Msk                      (0x07 << R015_MOSI_MUX_Pos)

#define  R015_GPIO6_MUX_Pos                     R015_MOSI_MUX_Pos
#define  R015_GPIO6_MUX_Msk                     R015_MOSI_MUX_Msk

#define  R015_CSN_MUX_Pos                       3
#define  R015_CSN_MUX_Msk                       (0x07 << R015_CSN_MUX_Pos)

#define  R015_GPIO5_MUX_Pos                     R015_CSN_MUX_Pos
#define  R015_GPIO5_MUX_Msk                     R015_CSN_MUX_Msk

#define  R015_XTL0_MUX_Pos                      6
#define  R015_XTL0_MUX_Msk                      (0x03 << R015_XTL0_MUX_Pos)

#define  R015_GPIO9_MUX_Pos                     R015_XTL0_MUX_Pos
#define  R015_GPIO9_MUX_Msk                     R015_XTL0_MUX_Msk

//--------------------------------------------------------------------------------------------------
#define   R016                                   0x016

#define  R016_IRQ_MUX_Pos                       0
#define  R016_IRQ_MUX_Msk                       (0x07 << R016_IRQ_MUX_Pos)

#define  R016_GPIO8_MUX_Pos                     R016_IRQ_MUX_Pos
#define  R016_GPIO8_MUX_Msk                     R016_IRQ_MUX_Msk

#define  R016_MISO_MUX_Pos                      3
#define  R016_MISO_MUX_Msk                      (0x07 << R016_MISO_MUX_Pos)

#define  R016_GPIO7_MUX_Pos                     R016_MISO_MUX_Pos
#define  R016_GPIO7_MUX_Msk                     R016_MISO_MUX_Msk

#define  R016_XTL1_MUX_Pos                      6
#define  R016_XTL1_MUX_Msk                      (0x03 << R016_XTL1_MUX_Pos)

#define  R016_GPIO10_MUX_Pos                    R016_XTL1_MUX_Pos
#define  R016_GPIO10_MUX_Msk                    R016_XTL1_MUX_Msk

//--------------------------------------------------------------------------------------------------
#define   R017                                   0x017

#define  R017_GPIO3_REG_Pos                     0
#define  R017_GPIO3_REG_Msk                     (0x01 << R017_GPIO3_REG_Pos)

#define  R017_GPIO4_REG_Pos                     1
#define  R017_GPIO4_REG_Msk                     (0x01 << R017_GPIO4_REG_Pos)

#define  R017_GPIO5_REG_Pos                     2
#define  R017_GPIO5_REG_Msk                     (0x01 << R017_GPIO5_REG_Pos)

#define  R017_GPIO6_REG_Pos                     3
#define  R017_GPIO6_REG_Msk                     (0x01 << R017_GPIO6_REG_Pos)

#define  R017_GPIO7_REG_Pos                     4
#define  R017_GPIO7_REG_Msk                     (0x01 << R017_GPIO7_REG_Pos)

#define  R017_GPIO8_REG_Pos                     5
#define  R017_GPIO8_REG_Msk                     (0x01 << R017_GPIO8_REG_Pos)

#define  R017_GPIO9_REG_Pos                     6
#define  R017_GPIO9_REG_Msk                     (0x01 << R017_GPIO9_REG_Pos)

#define  R017_GPIO10_REG_Pos                    7
#define  R017_GPIO10_REG_Msk                    (0x01 << R017_GPIO10_REG_Pos)

//--------------------------------------------------------------------------------------------------
#define   R018                                   0x018

#define  R018_GPIO3_DIEN_Pos                    0
#define  R018_GPIO3_DIEN_Msk                    (0x01 << R018_GPIO3_DIEN_Pos)

#define  R018_GPIO4_DIEN_Pos                    1
#define  R018_GPIO4_DIEN_Msk                    (0x01 << R018_GPIO4_DIEN_Pos)

#define  R018_GPIO5_DIEN_Pos                    2
#define  R018_GPIO5_DIEN_Msk                    (0x01 << R018_GPIO5_DIEN_Pos)

#define  R018_GPIO6_DIEN_Pos                    3
#define  R018_GPIO6_DIEN_Msk                    (0x01 << R018_GPIO6_DIEN_Pos)

#define  R018_GPIO7_DIEN_Pos                    4
#define  R018_GPIO7_DIEN_Msk                    (0x01 << R018_GPIO7_DIEN_Pos)

#define  R018_GPIO8_DIEN_Pos                    5
#define  R018_GPIO8_DIEN_Msk                    (0x01 << R018_GPIO8_DIEN_Pos)

#define  R018_GPIO9_DIEN_Pos                    6
#define  R018_GPIO9_DIEN_Msk                    (0x01 << R018_GPIO9_DIEN_Pos)

#define  R018_GPIO10_DIEN_Pos                   7
#define  R018_GPIO10_DIEN_Msk                   (0x01 << R018_GPIO10_DIEN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R019                                   0x019

#define  R019_GPIO3_OE_Pos                      0
#define  R019_GPIO3_OE_Msk                      (0x01 << R019_GPIO3_OE_Pos)

#define  R019_GPIO4_OE_Pos                      1
#define  R019_GPIO4_OE_Msk                      (0x01 << R019_GPIO4_OE_Pos)

#define  R019_GPIO5_OE_Pos                      2
#define  R019_GPIO5_OE_Msk                      (0x01 << R019_GPIO5_OE_Pos)

#define  R019_GPIO6_OE_Pos                      3
#define  R019_GPIO6_OE_Msk                      (0x01 << R019_GPIO6_OE_Pos)

#define  R019_GPIO7_OE_Pos                      4
#define  R019_GPIO7_OE_Msk                      (0x01 << R019_GPIO7_OE_Pos)

#define  R019_GPIO8_OE_Pos                      5
#define  R019_GPIO8_OE_Msk                      (0x01 << R019_GPIO8_OE_Pos)

#define  R019_GPIO9_OE_Pos                      6
#define  R019_GPIO9_OE_Msk                      (0x01 << R019_GPIO9_OE_Pos)

#define  R019_GPIO10_OE_Pos                     7
#define  R019_GPIO10_OE_Msk                     (0x01 << R019_GPIO10_OE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R01A                                   0x01a

#define  R01A_GPIO3_PUEN_Pos                    0
#define  R01A_GPIO3_PUEN_Msk                    (0x01 << R01A_GPIO3_PUEN_Pos)

#define  R01A_GPIO4_PUEN_Pos                    1
#define  R01A_GPIO4_PUEN_Msk                    (0x01 << R01A_GPIO4_PUEN_Pos)

#define  R01A_GPIO5_PUEN_Pos                    2
#define  R01A_GPIO5_PUEN_Msk                    (0x01 << R01A_GPIO5_PUEN_Pos)

#define  R01A_GPIO6_PUEN_Pos                    3
#define  R01A_GPIO6_PUEN_Msk                    (0x01 << R01A_GPIO6_PUEN_Pos)

#define  R01A_GPIO7_PUEN_Pos                    4
#define  R01A_GPIO7_PUEN_Msk                    (0x01 << R01A_GPIO7_PUEN_Pos)

#define  R01A_GPIO8_PUEN_Pos                    5
#define  R01A_GPIO8_PUEN_Msk                    (0x01 << R01A_GPIO8_PUEN_Pos)

#define  R01A_GPIO9_PUEN_Pos                    6
#define  R01A_GPIO9_PUEN_Msk                    (0x01 << R01A_GPIO9_PUEN_Pos)

#define  R01A_GPIO10_PUEN_Pos                   7
#define  R01A_GPIO10_PUEN_Msk                   (0x01 << R01A_GPIO10_PUEN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R01B                                   0x01b

#define  R01B_GPIO3_PDEN_Pos                    0
#define  R01B_GPIO3_PDEN_Msk                    (0x01 << R01B_GPIO3_PDEN_Pos)

#define  R01B_GPIO4_PDEN_Pos                    1
#define  R01B_GPIO4_PDEN_Msk                    (0x01 << R01B_GPIO4_PDEN_Pos)

#define  R01B_GPIO5_PDEN_Pos                    2
#define  R01B_GPIO5_PDEN_Msk                    (0x01 << R01B_GPIO5_PDEN_Pos)

#define  R01B_GPIO6_PDEN_Pos                    3
#define  R01B_GPIO6_PDEN_Msk                    (0x01 << R01B_GPIO6_PDEN_Pos)

#define  R01B_GPIO7_PDEN_Pos                    4
#define  R01B_GPIO7_PDEN_Msk                    (0x01 << R01B_GPIO7_PDEN_Pos)

#define  R01B_GPIO8_PDEN_Pos                    5
#define  R01B_GPIO8_PDEN_Msk                    (0x01 << R01B_GPIO8_PDEN_Pos)

#define  R01B_GPIO9_PDEN_Pos                    6
#define  R01B_GPIO9_PDEN_Msk                    (0x01 << R01B_GPIO9_PDEN_Pos)

#define  R01B_GPIO10_PDEN_Pos                   7
#define  R01B_GPIO10_PDEN_Msk                   (0x01 << R01B_GPIO10_PDEN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R01C                                   0x01c

#define  R01C_GPIO3_WKEN_Pos                    0
#define  R01C_GPIO3_WKEN_Msk                    (0x01 << R01C_GPIO3_WKEN_Pos)

#define  R01C_GPIO4_WKEN_Pos                    1
#define  R01C_GPIO4_WKEN_Msk                    (0x01 << R01C_GPIO4_WKEN_Pos)

#define  R01C_GPIO5_WKEN_Pos                    2
#define  R01C_GPIO5_WKEN_Msk                    (0x01 << R01C_GPIO5_WKEN_Pos)

#define  R01C_GPIO6_WKEN_Pos                    3
#define  R01C_GPIO6_WKEN_Msk                    (0x01 << R01C_GPIO6_WKEN_Pos)

#define  R01C_GPIO7_WKEN_Pos                    4
#define  R01C_GPIO7_WKEN_Msk                    (0x01 << R01C_GPIO7_WKEN_Pos)

#define  R01C_GPIO8_WKEN_Pos                    5
#define  R01C_GPIO8_WKEN_Msk                    (0x01 << R01C_GPIO8_WKEN_Pos)

#define  R01C_GPIO9_WKEN_Pos                    6
#define  R01C_GPIO9_WKEN_Msk                    (0x01 << R01C_GPIO9_WKEN_Pos)

#define  R01C_GPIO10_WKEN_Pos                   7
#define  R01C_GPIO10_WKEN_Msk                   (0x01 << R01C_GPIO10_WKEN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R01D                                   0x01d

#define  R01D_GPIO3_WAKEUP_MODE_Pos             0
#define  R01D_GPIO3_WAKEUP_MODE_Msk             (0x01 << R01D_GPIO3_WAKEUP_MODE_Pos)

#define  R01D_GPIO4_WAKEUP_MODE_Pos             1
#define  R01D_GPIO4_WAKEUP_MODE_Msk             (0x01 << R01D_GPIO4_WAKEUP_MODE_Pos)

#define  R01D_GPIO5_WAKEUP_MODE_Pos             2
#define  R01D_GPIO5_WAKEUP_MODE_Msk             (0x01 << R01D_GPIO5_WAKEUP_MODE_Pos)

#define  R01D_GPIO6_WAKEUP_MODE_Pos             3
#define  R01D_GPIO6_WAKEUP_MODE_Msk             (0x01 << R01D_GPIO6_WAKEUP_MODE_Pos)

#define  R01D_GPIO7_WAKEUP_MODE_Pos             4
#define  R01D_GPIO7_WAKEUP_MODE_Msk             (0x01 << R01D_GPIO7_WAKEUP_MODE_Pos)

#define  R01D_GPIO8_WAKEUP_MODE_Pos             5
#define  R01D_GPIO8_WAKEUP_MODE_Msk             (0x01 << R01D_GPIO8_WAKEUP_MODE_Pos)

#define  R01D_GPIO9_WAKEUP_MODE_Pos             6
#define  R01D_GPIO9_WAKEUP_MODE_Msk             (0x01 << R01D_GPIO9_WAKEUP_MODE_Pos)

#define  R01D_GPIO10_WAKEUP_MODE_Pos            7
#define  R01D_GPIO10_WAKEUP_MODE_Msk            (0x01 << R01D_GPIO10_WAKEUP_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R01E                                   0x01e

#define  R01E_GPIO0_WKEN_Pos                    0
#define  R01E_GPIO0_WKEN_Msk                    (0x01 << R01E_GPIO0_WKEN_Pos)

#define  R01E_GPIO1_WKEN_Pos                    1
#define  R01E_GPIO1_WKEN_Msk                    (0x01 << R01E_GPIO1_WKEN_Pos)

#define  R01E_GPIO2_WKEN_Pos                    2
#define  R01E_GPIO2_WKEN_Msk                    (0x01 << R01E_GPIO2_WKEN_Pos)

#define  R01E_VPP_WKEN_Pos                      3
#define  R01E_VPP_WKEN_Msk                      (0x01 << R01E_VPP_WKEN_Pos)

#define  R01E_GPIO11_WKEN_Pos                   R01E_VPP_WKEN_Pos
#define  R01E_GPIO11_WKEN_Msk                   R01E_VPP_WKEN_Msk

#define  R01E_GPIO0_WAKEUP_MODE_Pos             4
#define  R01E_GPIO0_WAKEUP_MODE_Msk             (0x01 << R01E_GPIO0_WAKEUP_MODE_Pos)

#define  R01E_GPIO1_WAKEUP_MODE_Pos             5
#define  R01E_GPIO1_WAKEUP_MODE_Msk             (0x01 << R01E_GPIO1_WAKEUP_MODE_Pos)

#define  R01E_GPIO2_WAKEUP_MODE_Pos             6
#define  R01E_GPIO2_WAKEUP_MODE_Msk             (0x01 << R01E_GPIO2_WAKEUP_MODE_Pos)

#define  R01E_VPP_WAKEUP_MODE_Pos               7
#define  R01E_VPP_WAKEUP_MODE_Msk               (0x01 << R01E_VPP_WAKEUP_MODE_Pos)

#define  R01E_GPIO11_WAKEUP_MODE_Pos            R01E_VPP_WAKEUP_MODE_Pos
#define  R01E_GPIO11_WAKEUP_MODE_Msk            R01E_VPP_WAKEUP_MODE_Msk

//--------------------------------------------------------------------------------------------------
#define   R01F                                   0x01f

#define  R01F_DVDD_PIC_TO_DVDD_ISO_EN_Pos       1
#define  R01F_DVDD_PIC_TO_DVDD_ISO_EN_Msk       (0x01 << R01F_DVDD_PIC_TO_DVDD_ISO_EN_Pos)

#define  R01F_DVDD_PIC_TO_DVDD_SPI_ISO_EN_Pos   2
#define  R01F_DVDD_PIC_TO_DVDD_SPI_ISO_EN_Msk   (0x01 << R01F_DVDD_PIC_TO_DVDD_SPI_ISO_EN_Pos)

#define  R01F_DVDD_TO_DVDD_PIC_ISO_EN_Pos       3
#define  R01F_DVDD_TO_DVDD_PIC_ISO_EN_Msk       (0x01 << R01F_DVDD_TO_DVDD_PIC_ISO_EN_Pos)

#define  R01F_DVDD_TO_DVDD_SPI_ISO_EN_Pos       4
#define  R01F_DVDD_TO_DVDD_SPI_ISO_EN_Msk       (0x01 << R01F_DVDD_TO_DVDD_SPI_ISO_EN_Pos)

#define  R01F_DVDD_SPI_TO_3V_ISO_EN_Pos         5
#define  R01F_DVDD_SPI_TO_3V_ISO_EN_Msk         (0x01 << R01F_DVDD_SPI_TO_3V_ISO_EN_Pos)

#define  R01F_DVDD_PIC_TO_3V_ISO_EN_Pos         6
#define  R01F_DVDD_PIC_TO_3V_ISO_EN_Msk         (0x01 << R01F_DVDD_PIC_TO_3V_ISO_EN_Pos)

#define  R01F_DVDD_TO_3V_ISO_EN_Pos             7
#define  R01F_DVDD_TO_3V_ISO_EN_Msk             (0x01 << R01F_DVDD_TO_3V_ISO_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R020_RCL_FREQ_COARSE_3V                0x020
#define   R020                                   0x020

#define  R020_RCL_FREQ_COARSE_3V_Pos            0
#define  R020_RCL_FREQ_COARSE_3V_Msk            (0x0f << R020_RCL_FREQ_COARSE_3V_Pos)

//--------------------------------------------------------------------------------------------------
#define   R021_RCL_FREQ_FINE_3V                  0x021
#define   R021                                   0x021

//--------------------------------------------------------------------------------------------------
#define   R022_WUTCMP0_OVR0                      0x022
#define   R022                                   0x022

//--------------------------------------------------------------------------------------------------
#define   R023_WUTCMP0_OVR1                      0x023
#define   R023                                   0x023

//--------------------------------------------------------------------------------------------------
#define   R024_WUTCMP0_OVR2                      0x024
#define   R024                                   0x024

//--------------------------------------------------------------------------------------------------
#define   R025_WUTCMP1_OVR0                      0x025
#define   R025                                   0x025

//--------------------------------------------------------------------------------------------------
#define   R026_WUTCMP1_OVR1                      0x026
#define   R026                                   0x026

//--------------------------------------------------------------------------------------------------
#define   R027_WUTCMP1_OVR2                      0x027
#define   R027                                   0x027

//--------------------------------------------------------------------------------------------------
#define   R028_WUTCMP2_OVR0                      0x028
#define   R028                                   0x028

//--------------------------------------------------------------------------------------------------
#define   R029_WUTCMP2_OVR1                      0x029
#define   R029                                   0x029

//--------------------------------------------------------------------------------------------------
#define   R02A_WUTCMP2_OVR2                      0x02a
#define   R02A                                   0x02a

//--------------------------------------------------------------------------------------------------
#define   R02B_WUTCNT0                           0x02b
#define   R02B                                   0x02b

//--------------------------------------------------------------------------------------------------
#define   R02C_WUTCNT1                           0x02c
#define   R02C                                   0x02c

//--------------------------------------------------------------------------------------------------
#define   R02D_WUTCNT2                           0x02d
#define   R02D                                   0x02d

//--------------------------------------------------------------------------------------------------
#define   R02E                                   0x02e

#define  R02E_WUT_DIVSEL_Pos                    0
#define  R02E_WUT_DIVSEL_Msk                    (0x0f << R02E_WUT_DIVSEL_Pos)

#define  R02E_WUTCMP0_INTF_MASK_Pos             4
#define  R02E_WUTCMP0_INTF_MASK_Msk             (0x01 << R02E_WUTCMP0_INTF_MASK_Pos)

#define  R02E_WUTCMP1_INTF_MASK_Pos             5
#define  R02E_WUTCMP1_INTF_MASK_Msk             (0x01 << R02E_WUTCMP1_INTF_MASK_Pos)

#define  R02E_WUTCMP2_INTF_MASK_Pos             6
#define  R02E_WUTCMP2_INTF_MASK_Msk             (0x01 << R02E_WUTCMP2_INTF_MASK_Pos)

//--------------------------------------------------------------------------------------------------
#define   R02F                                   0x02f

#define  R02F_WUTCMP0_INTEN_Pos                 0
#define  R02F_WUTCMP0_INTEN_Msk                 (0x01 << R02F_WUTCMP0_INTEN_Pos)

#define  R02F_WUTCMP1_INTEN_Pos                 1
#define  R02F_WUTCMP1_INTEN_Msk                 (0x01 << R02F_WUTCMP1_INTEN_Pos)

#define  R02F_WUTCMP2_INTEN_Pos                 2
#define  R02F_WUTCMP2_INTEN_Msk                 (0x01 << R02F_WUTCMP2_INTEN_Pos)

#define  R02F_WUT_EN_Pos                        3
#define  R02F_WUT_EN_Msk                        (0x01 << R02F_WUT_EN_Pos)

#define  R02F_WUTCMP0_WKEN_Pos                  4
#define  R02F_WUTCMP0_WKEN_Msk                  (0x01 << R02F_WUTCMP0_WKEN_Pos)

#define  R02F_WUTCMP1_WKEN_Pos                  5
#define  R02F_WUTCMP1_WKEN_Msk                  (0x01 << R02F_WUTCMP1_WKEN_Pos)

#define  R02F_WUTCMP2_WKEN_Pos                  6
#define  R02F_WUTCMP2_WKEN_Msk                  (0x01 << R02F_WUTCMP2_WKEN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R030_PIC_RESTART_FLAG                  0x030
#define   R030                                   0x030

#define  R030_PIC_RESTART_FLAG_Pos              0
#define  R030_PIC_RESTART_FLAG_Msk              (0x0f << R030_PIC_RESTART_FLAG_Pos)

//--------------------------------------------------------------------------------------------------
#define   R031                                   0x031

#define  R031_LVR_OUT_3V_Pos                    0
#define  R031_LVR_OUT_3V_Msk                    (0x01 << R031_LVR_OUT_3V_Pos)

#define  R031_BOD_OUT_3V_Pos                    1
#define  R031_BOD_OUT_3V_Msk                    (0x01 << R031_BOD_OUT_3V_Pos)

#define  R031_XTL_RDY_Pos                       2
#define  R031_XTL_RDY_Msk                       (0x01 << R031_XTL_RDY_Pos)

#define  R031_RCL_RDY_Pos                       3
#define  R031_RCL_RDY_Msk                       (0x01 << R031_RCL_RDY_Pos)

//--------------------------------------------------------------------------------------------------
#define   R032                                   0x032

#define  R032_LP_VREF_LDO2_TRIM_3V_Pos          0
#define  R032_LP_VREF_LDO2_TRIM_3V_Msk          (0x07 << R032_LP_VREF_LDO2_TRIM_3V_Pos)

#define  R032_LP_VREF_TEMP_TRIM_3V_Pos          3
#define  R032_LP_VREF_TEMP_TRIM_3V_Msk          (0x03 << R032_LP_VREF_TEMP_TRIM_3V_Pos)

//--------------------------------------------------------------------------------------------------
#define   R033                                   0x033

#define  R033_RCL_RDY_TRIM_3V_Pos               0
#define  R033_RCL_RDY_TRIM_3V_Msk               (0x03 << R033_RCL_RDY_TRIM_3V_Pos)

#define  R033_XTL_RDY_TRIM_3V_Pos               2
#define  R033_XTL_RDY_TRIM_3V_Msk               (0x03 << R033_XTL_RDY_TRIM_3V_Pos)

#define  R033_XTL_BC_3V_Pos                     4
#define  R033_XTL_BC_3V_Msk                     (0x07 << R033_XTL_BC_3V_Pos)

//--------------------------------------------------------------------------------------------------
#define   R034                                   0x034

#define  R034_SPI_DRV_SEL_3V_Pos                0
#define  R034_SPI_DRV_SEL_3V_Msk                (0x03 << R034_SPI_DRV_SEL_3V_Pos)

#define  R034_GPIO3V_DRV_SEL_3V_Pos             2
#define  R034_GPIO3V_DRV_SEL_3V_Msk             (0x03 << R034_GPIO3V_DRV_SEL_3V_Pos)

#define  R034_XTL1_CHEN_3V_Pos                  4
#define  R034_XTL1_CHEN_3V_Msk                  (0x01 << R034_XTL1_CHEN_3V_Pos)

#define  R034_XTL0_CHEN_3V_Pos                  5
#define  R034_XTL0_CHEN_3V_Msk                  (0x01 << R034_XTL0_CHEN_3V_Pos)

#define  R034_GPIO3_CHEN_3V_Pos                 6
#define  R034_GPIO3_CHEN_3V_Msk                 (0x01 << R034_GPIO3_CHEN_3V_Pos)

//--------------------------------------------------------------------------------------------------
#define   R106                                   0x106

#define  R106_M802_CRC_MANUE_Pos                0
#define  R106_M802_CRC_MANUE_Msk                (0x01 << R106_M802_CRC_MANUE_Pos)

#define  R106_REG_AFC_VLD_Pos                   1
#define  R106_REG_AFC_VLD_Msk                   (0x01 << R106_REG_AFC_VLD_Pos)

#define  R106_REG_HAMMING_EN_Pos                2
#define  R106_REG_HAMMING_EN_Msk                (0x01 << R106_REG_HAMMING_EN_Pos)

#define  R106_REG_FEC_TYPE_Pos                  3
#define  R106_REG_FEC_TYPE_Msk                  (0x03 << R106_REG_FEC_TYPE_Pos)

#define  R106_REG_INT_EN_Pos                    5
#define  R106_REG_INT_EN_Msk                    (0x01 << R106_REG_INT_EN_Pos)

#define  R106_REG_MBUS_MSB_OUT_SEL_Pos          6
#define  R106_REG_MBUS_MSB_OUT_SEL_Msk          (0x01 << R106_REG_MBUS_MSB_OUT_SEL_Pos)

#define  R106_REG_HAMMING_MODE_Pos              7
#define  R106_REG_HAMMING_MODE_Msk              (0x01 << R106_REG_HAMMING_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R107                                   0x107

#define  R107_REG_PRE_MAN_EN_Pos                0
#define  R107_REG_PRE_MAN_EN_Msk                (0x01 << R107_REG_PRE_MAN_EN_Pos)

#define  R107_REG_PRE_MAN_MODE_Pos              1
#define  R107_REG_PRE_MAN_MODE_Msk              (0x01 << R107_REG_PRE_MAN_MODE_Pos)

#define  R107_REG_PRE_SEL_Pos                   2
#define  R107_REG_PRE_SEL_Msk                   (0x03 << R107_REG_PRE_SEL_Pos)

#define  R107_REG_PRE_BIT_MODE_Pos              4
#define  R107_REG_PRE_BIT_MODE_Msk              (0x01 << R107_REG_PRE_BIT_MODE_Pos)

#define  R107_REG_DIRECT_MODE_Pos               5
#define  R107_REG_DIRECT_MODE_Msk               (0x01 << R107_REG_DIRECT_MODE_Pos)

#define  R107_REG_DIRECT_TX_EN_Pos              6
#define  R107_REG_DIRECT_TX_EN_Msk              (0x01 << R107_REG_DIRECT_TX_EN_Pos)

#define  R107_REG_DIRECT_RX_EN_Pos              7
#define  R107_REG_DIRECT_RX_EN_Msk              (0x01 << R107_REG_DIRECT_RX_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R108_REG_PRE_PAT                       0x108
#define  R108_REG_PRE_PAT_L16                   0x108
#define  R10A_REG_PRE_PAT_H16                   0x10a

#define   R108_REG_PRE_PAT_L1                    0x108
#define   R108                                   0x108

#define   R109_REG_PRE_PAT_L2                    0x109
#define   R109                                   0x109

#define   R10A_REG_PRE_PAT_L3                    0x10a
#define   R10A                                   0x10a

#define   R10B_REG_PRE_PAT_H                     0x10b
#define   R10B                                   0x10b

//--------------------------------------------------------------------------------------------------
#define   R10C_REG_PREAMBLE_LEN                  0x10c
#define   R10C                                   0x10c

//--------------------------------------------------------------------------------------------------
#define   R10D                                   0x10d

#define  R10D_REG_SYNC_LEN_Pos                  0
#define  R10D_REG_SYNC_LEN_Msk                  (0x07 << R10D_REG_SYNC_LEN_Pos)

#define  R10D_REG_SYNC_MAN_EN_Pos               3
#define  R10D_REG_SYNC_MAN_EN_Msk               (0x01 << R10D_REG_SYNC_MAN_EN_Pos)

#define  R10D_REG_SYNC_MAN_MODE_Pos             4
#define  R10D_REG_SYNC_MAN_MODE_Msk             (0x01 << R10D_REG_SYNC_MAN_MODE_Pos)

#define  R10D_REG_SYNC_BIT_MODE_Pos             5
#define  R10D_REG_SYNC_BIT_MODE_Msk             (0x01 << R10D_REG_SYNC_BIT_MODE_Pos)

#define  R10D_REG_CRC_ENDIAN_Pos                6
#define  R10D_REG_CRC_ENDIAN_Msk                (0x01 << R10D_REG_CRC_ENDIAN_Pos)

#define  R10D_REG_PAYLOAD_ENDIAN_Pos            7
#define  R10D_REG_PAYLOAD_ENDIAN_Msk            (0x01 << R10D_REG_PAYLOAD_ENDIAN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R10E_REG_CRC_POLY                      0x10e
#define  R10E_REG_CRC_POLY_L16                  0x10e
#define  R110_REG_CRC_POLY_H16                  0x110

#define   R10E_REG_CRC_POLY_L1                   0x10e
#define   R10E                                   0x10e

#define   R10F_REG_CRC_POLY_L2                   0x10f
#define   R10F                                   0x10f

#define   R110_REG_CRC_POLY_L3                   0x110
#define   R110                                   0x110

#define   R111_REG_CRC_POLY_H                    0x111
#define   R111                                   0x111

//--------------------------------------------------------------------------------------------------
#define  R112_REG_CRC_SEED                      0x112
#define  R112_REG_CRC_SEED_L16                  0x112
#define  R114_REG_CRC_SEED_H16                  0x114

#define   R112_REG_CRC_SEED_L1                   0x112
#define   R112                                   0x112

#define   R113_REG_CRC_SEED_L2                   0x113
#define   R113                                   0x113

#define   R114_REG_CRC_SEED_L3                   0x114
#define   R114                                   0x114

#define   R115_REG_CRC_SEED_H                    0x115
#define   R115                                   0x115

//--------------------------------------------------------------------------------------------------
#define   R116                                   0x116

#define  R116_REG_CRC_MODE_Pos                  0
#define  R116_REG_CRC_MODE_Msk                  (0x03 << R116_REG_CRC_MODE_Pos)

#define  R116_REG_CRC_NOT_SEL_Pos               2
#define  R116_REG_CRC_NOT_SEL_Msk               (0x01 << R116_REG_CRC_NOT_SEL_Pos)

#define  R116_REG_WHITEN_SEL_Pos                3
#define  R116_REG_WHITEN_SEL_Msk                (0x01 << R116_REG_WHITEN_SEL_Pos)

#define  R116_REG_WHITEN_OUT_SEL_Pos            4
#define  R116_REG_WHITEN_OUT_SEL_Msk            (0x0f << R116_REG_WHITEN_OUT_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R117                                   0x117

#define  R117_REG_WHITEN_XOR1_SEL_Pos           0
#define  R117_REG_WHITEN_XOR1_SEL_Msk           (0x0f << R117_REG_WHITEN_XOR1_SEL_Pos)

#define  R117_REG_WHITEN_XOR2_SEL_Pos           4
#define  R117_REG_WHITEN_XOR2_SEL_Msk           (0x0f << R117_REG_WHITEN_XOR2_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define  R118_REG_WHITEN_SEED                   0x118

#define   R118_REG_WHITEN_SEED_L                 0x118
#define   R118                                   0x118

#define   R119_REG_WHITEN_SEED_H                 0x119
#define   R119                                   0x119

//--------------------------------------------------------------------------------------------------
#define   R11A                                   0x11a

#define  R11A_REG_WHITEN_LENGTH_Pos             0
#define  R11A_REG_WHITEN_LENGTH_Msk             (0x0f << R11A_REG_WHITEN_LENGTH_Pos)

#define  R11A_REG_PL_MAN_MODE_Pos               4
#define  R11A_REG_PL_MAN_MODE_Msk               (0x01 << R11A_REG_PL_MAN_MODE_Pos)

#define  R11A_REG_PAYLOAD_SEL_Pos               5
#define  R11A_REG_PAYLOAD_SEL_Msk               (0x01 << R11A_REG_PAYLOAD_SEL_Pos)

#define  R11A_M802_PHR_MODE_Pos                 6
#define  R11A_M802_PHR_MODE_Msk                 (0x01 << R11A_M802_PHR_MODE_Pos)

#define  R11A_REG_WHITEN_PN13_SEL_Pos           7
#define  R11A_REG_WHITEN_PN13_SEL_Msk           (0x01 << R11A_REG_WHITEN_PN13_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R11B                                   0x11b

#define  R11B_REG_NODE_LENGTH_Pos               2
#define  R11B_REG_NODE_LENGTH_Msk               (0x07 << R11B_REG_NODE_LENGTH_Pos)

#define  R11B_REG_NODE_MODE_Pos                 5
#define  R11B_REG_NODE_MODE_Msk                 (0x01 << R11B_REG_NODE_MODE_Pos)

#define  R11B_REG_M802_FCS_Pos                  6
#define  R11B_REG_M802_FCS_Msk                  (0x01 << R11B_REG_M802_FCS_Pos)

#define  R11B_REG_VIA_LENGTH_LEN_Pos            7
#define  R11B_REG_VIA_LENGTH_LEN_Msk            (0x01 << R11B_REG_VIA_LENGTH_LEN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R11C_REG_NODE_ID                       0x11c
#define  R11C_REG_NODE_ID_L16                   0x11c
#define  R11E_REG_NODE_ID_H16                   0x11e

#define   R11C_REG_NODE_ID_L1                    0x11c
#define   R11C                                   0x11c

#define   R11D_REG_NODE_ID_L2                    0x11d
#define   R11D                                   0x11d

#define   R11E_REG_NODE_ID_L3                    0x11e
#define   R11E                                   0x11e

#define   R11F_REG_NODE_ID_H                     0x11f
#define   R11F                                   0x11f

//--------------------------------------------------------------------------------------------------
#define   R120                                   0x120

#define  R120_REG_POSTAMBLE_LEN_Pos             0
#define  R120_REG_POSTAMBLE_LEN_Msk             (0x7f << R120_REG_POSTAMBLE_LEN_Pos)

#define  R120_REG_VIA_CRC_MODE_Pos              7
#define  R120_REG_VIA_CRC_MODE_Msk              (0x01 << R120_REG_VIA_CRC_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define  R121_REG_POST_PAT                      0x121
#define  R121_REG_POST_PAT_L16                  0x121
#define  R123_REG_POST_PAT_H16                  0x123

#define   R121_REG_POST_PAT_L1                   0x121
#define   R121                                   0x121

#define   R122_REG_POST_PAT_L2                   0x122
#define   R122                                   0x122

#define   R123_REG_POST_PAT_L3                   0x123
#define   R123                                   0x123

#define   R124_REG_POST_PAT_H                    0x124
#define   R124                                   0x124

//--------------------------------------------------------------------------------------------------
#define   R125                                   0x125

#define  R125_REG_POST_EN_Pos                   0
#define  R125_REG_POST_EN_Msk                   (0x01 << R125_REG_POST_EN_Pos)

#define  R125_REG_POST_BIT_MODE_Pos             1
#define  R125_REG_POST_BIT_MODE_Msk             (0x01 << R125_REG_POST_BIT_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R126                                   0x126

#define  R126_REG_BUF_SIZE_Pos                  0
#define  R126_REG_BUF_SIZE_Msk                  (0x7f << R126_REG_BUF_SIZE_Pos)

#define  R126_REG_BUF_SIZE_SEL_Pos              7
#define  R126_REG_BUF_SIZE_SEL_Msk              (0x01 << R126_REG_BUF_SIZE_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R129                                   0x129

//--------------------------------------------------------------------------------------------------
#define   R12B                                   0x12b

#define  R12B_REG_WHITEN_PN9_SEL_Pos            4
#define  R12B_REG_WHITEN_PN9_SEL_Msk            (0x01 << R12B_REG_WHITEN_PN9_SEL_Pos)

#define  R12B_REG_VIA_LEN_ENDIAN_Pos            5
#define  R12B_REG_VIA_LEN_ENDIAN_Msk            (0x01 << R12B_REG_VIA_LEN_ENDIAN_Pos)

#define  R12B_CRC_BYTE_ENDIAN_Pos               6
#define  R12B_CRC_BYTE_ENDIAN_Msk               (0x01 << R12B_CRC_BYTE_ENDIAN_Pos)

#define  R12B_NRNSC_NOT_SEL_Pos                 7
#define  R12B_NRNSC_NOT_SEL_Msk                 (0x01 << R12B_NRNSC_NOT_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R12C                                   0x12c

#define  R12C_REG_LENGTH_FIELD_NUM_Pos          0
#define  R12C_REG_LENGTH_FIELD_NUM_Msk          (0x07 << R12C_REG_LENGTH_FIELD_NUM_Pos)

#define  R12C_REG_VIA_FIELD_NUM_Pos             3
#define  R12C_REG_VIA_FIELD_NUM_Msk             (0x07 << R12C_REG_VIA_FIELD_NUM_Pos)

#define  R12C_REG_DEV_MODE_Pos                  6
#define  R12C_REG_DEV_MODE_Msk                  (0x03 << R12C_REG_DEV_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R12D                                   0x12d

#define  R12D_FIELD_NUM_Pos                     0
#define  R12D_FIELD_NUM_Msk                     (0x07 << R12D_FIELD_NUM_Pos)

#define  R12D_VIA_MFIELD_EN_Pos                 3
#define  R12D_VIA_MFIELD_EN_Msk                 (0x01 << R12D_VIA_MFIELD_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R12E                                   0x12e

#define  R12E_FIELD1_WHITE_SET_Pos              0
#define  R12E_FIELD1_WHITE_SET_Msk              (0x01 << R12E_FIELD1_WHITE_SET_Pos)

#define  R12E_FIELD1_WHITE_EN_Pos               1
#define  R12E_FIELD1_WHITE_EN_Msk               (0x01 << R12E_FIELD1_WHITE_EN_Pos)

#define  R12E_FIELD1_CRC_SET_Pos                2
#define  R12E_FIELD1_CRC_SET_Msk                (0x01 << R12E_FIELD1_CRC_SET_Pos)

#define  R12E_FIELD1_CRC_EN_Pos                 3
#define  R12E_FIELD1_CRC_EN_Msk                 (0x01 << R12E_FIELD1_CRC_EN_Pos)

#define  R12E_FIELD1_CRC_IN_Pos                 4
#define  R12E_FIELD1_CRC_IN_Msk                 (0x01 << R12E_FIELD1_CRC_IN_Pos)

#define  R12E_FIELD1_MAN_EN_Pos                 5
#define  R12E_FIELD1_MAN_EN_Msk                 (0x01 << R12E_FIELD1_MAN_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R12F_FIELD2_LENGTH                     0x12f

#define   R12F_FIELD2_LENGTH_L                   0x12f
#define   R12F                                   0x12f

#define   R130_FIELD2_LENGTH_H                   0x130
#define   R130                                   0x130

//--------------------------------------------------------------------------------------------------
#define   R131                                   0x131

#define  R131_FIELD2_WHITE_SET_Pos              0
#define  R131_FIELD2_WHITE_SET_Msk              (0x01 << R131_FIELD2_WHITE_SET_Pos)

#define  R131_FIELD2_WHITE_EN_Pos               1
#define  R131_FIELD2_WHITE_EN_Msk               (0x01 << R131_FIELD2_WHITE_EN_Pos)

#define  R131_FIELD2_CRC_SET_Pos                2
#define  R131_FIELD2_CRC_SET_Msk                (0x01 << R131_FIELD2_CRC_SET_Pos)

#define  R131_FIELD2_CRC_EN_Pos                 3
#define  R131_FIELD2_CRC_EN_Msk                 (0x01 << R131_FIELD2_CRC_EN_Pos)

#define  R131_FIELD2_CRC_IN_Pos                 4
#define  R131_FIELD2_CRC_IN_Msk                 (0x01 << R131_FIELD2_CRC_IN_Pos)

#define  R131_FIELD2_MAN_EN_Pos                 5
#define  R131_FIELD2_MAN_EN_Msk                 (0x01 << R131_FIELD2_MAN_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R132_FIELD3_LENGTH                     0x132

#define   R132_FIELD3_LENGTH_L                   0x132
#define   R132                                   0x132

#define   R133_FIELD3_LENGTH_H                   0x133
#define   R133                                   0x133

//--------------------------------------------------------------------------------------------------
#define   R134                                   0x134

#define  R134_FIELD3_WHITE_SET_Pos              0
#define  R134_FIELD3_WHITE_SET_Msk              (0x01 << R134_FIELD3_WHITE_SET_Pos)

#define  R134_FIELD3_WHITE_EN_Pos               1
#define  R134_FIELD3_WHITE_EN_Msk               (0x01 << R134_FIELD3_WHITE_EN_Pos)

#define  R134_FIELD3_CRC_SET_Pos                2
#define  R134_FIELD3_CRC_SET_Msk                (0x01 << R134_FIELD3_CRC_SET_Pos)

#define  R134_FIELD3_CRC_EN_Pos                 3
#define  R134_FIELD3_CRC_EN_Msk                 (0x01 << R134_FIELD3_CRC_EN_Pos)

#define  R134_FIELD3_CRC_IN_Pos                 4
#define  R134_FIELD3_CRC_IN_Msk                 (0x01 << R134_FIELD3_CRC_IN_Pos)

#define  R134_FIELD3_MAN_EN_Pos                 5
#define  R134_FIELD3_MAN_EN_Msk                 (0x01 << R134_FIELD3_MAN_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R135_FIELD4_LENGTH                     0x135

#define   R135_FIELD4_LENGTH_L                   0x135
#define   R135                                   0x135

#define   R136_FIELD4_LENGTH_H                   0x136
#define   R136                                   0x136

//--------------------------------------------------------------------------------------------------
#define   R137                                   0x137

#define  R137_FIELD4_WHITE_SET_Pos              0
#define  R137_FIELD4_WHITE_SET_Msk              (0x01 << R137_FIELD4_WHITE_SET_Pos)

#define  R137_FIELD4_WHITE_EN_Pos               1
#define  R137_FIELD4_WHITE_EN_Msk               (0x01 << R137_FIELD4_WHITE_EN_Pos)

#define  R137_FIELD4_CRC_SET_Pos                2
#define  R137_FIELD4_CRC_SET_Msk                (0x01 << R137_FIELD4_CRC_SET_Pos)

#define  R137_FIELD4_CRC_EN_Pos                 3
#define  R137_FIELD4_CRC_EN_Msk                 (0x01 << R137_FIELD4_CRC_EN_Pos)

#define  R137_FIELD4_CRC_IN_Pos                 4
#define  R137_FIELD4_CRC_IN_Msk                 (0x01 << R137_FIELD4_CRC_IN_Pos)

#define  R137_FIELD4_MAN_EN_Pos                 5
#define  R137_FIELD4_MAN_EN_Msk                 (0x01 << R137_FIELD4_MAN_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R138_FIELD5_LENGTH_L                   0x138
#define   R138                                   0x138

//--------------------------------------------------------------------------------------------------
#define   R139                                   0x139

#define  R139_FIELD5_LENGTH_H_Pos               0
#define  R139_FIELD5_LENGTH_H_Msk               (0x3f << R139_FIELD5_LENGTH_H_Pos)

#define  R139_SET_MODE_Pos                      6
#define  R139_SET_MODE_Msk                      (0x01 << R139_SET_MODE_Pos)

#define  R139_SYNC_4FSK_MODE_Pos                7
#define  R139_SYNC_4FSK_MODE_Msk                (0x01 << R139_SYNC_4FSK_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R13A                                   0x13a

#define  R13A_FIELD5_WHITE_SET_Pos              0
#define  R13A_FIELD5_WHITE_SET_Msk              (0x01 << R13A_FIELD5_WHITE_SET_Pos)

#define  R13A_FIELD5_WHITE_EN_Pos               1
#define  R13A_FIELD5_WHITE_EN_Msk               (0x01 << R13A_FIELD5_WHITE_EN_Pos)

#define  R13A_FIELD5_CRC_SET_Pos                2
#define  R13A_FIELD5_CRC_SET_Msk                (0x01 << R13A_FIELD5_CRC_SET_Pos)

#define  R13A_FIELD5_CRC_EN_Pos                 3
#define  R13A_FIELD5_CRC_EN_Msk                 (0x01 << R13A_FIELD5_CRC_EN_Pos)

#define  R13A_FIELD5_CRC_IN_Pos                 4
#define  R13A_FIELD5_CRC_IN_Msk                 (0x01 << R13A_FIELD5_CRC_IN_Pos)

#define  R13A_FIELD5_MAN_EN_Pos                 5
#define  R13A_FIELD5_MAN_EN_Msk                 (0x01 << R13A_FIELD5_MAN_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R13B_REG_DRIFT_SPEED                   0x13b

#define   R13B_REG_DRIFT_SPEED_L                 0x13b
#define   R13B                                   0x13b

#define   R13C_REG_DRIFT_SPEED_H                 0x13c
#define   R13C                                   0x13c

//--------------------------------------------------------------------------------------------------
#define   R13D_REG_FLTR_DEV_L                    0x13d
#define   R13D                                   0x13d

//--------------------------------------------------------------------------------------------------
#define   R13E                                   0x13e

#define  R13E_REG_FLTR_DEV_H_Pos                0
#define  R13E_REG_FLTR_DEV_H_Msk                (0x01 << R13E_REG_FLTR_DEV_H_Pos)

#define  R13E_REG_SYNC_WORD2_EN_Pos             5
#define  R13E_REG_SYNC_WORD2_EN_Msk             (0x01 << R13E_REG_SYNC_WORD2_EN_Pos)

#define  R13E_ADC_CLK_INV_Pos                   7
#define  R13E_ADC_CLK_INV_Msk                   (0x01 << R13E_ADC_CLK_INV_Pos)

//--------------------------------------------------------------------------------------------------
#define  R13F_REG_MAX_AFC_FREQ                  0x13f

#define   R13F_REG_MAX_AFC_FREQ_L                0x13f
#define   R13F                                   0x13f

#define   R140_REG_MAX_AFC_FREQ_H                0x140
#define   R140                                   0x140

//--------------------------------------------------------------------------------------------------
#define   R141_REG_AFC_FLS_TH                    0x141
#define   R141                                   0x141

//--------------------------------------------------------------------------------------------------
#define   R142_REG_FSK_DEV                       0x142
#define   R142                                   0x142

//--------------------------------------------------------------------------------------------------
#define   R143_REG_FSK_DEV_INNER                 0x143
#define   R143                                   0x143

//--------------------------------------------------------------------------------------------------
#define  R144_REG_RX_4FSK_DEV_TH                0x144

#define   R144_REG_RX_4FSK_DEV_TH_L              0x144
#define   R144                                   0x144

#define   R145_REG_RX_4FSK_DEV_TH_H              0x145
#define   R145                                   0x145

//--------------------------------------------------------------------------------------------------
#define  R146_REG_RX_TR_DEV_OUTER               0x146

#define   R146_REG_RX_TR_DEV_OUTER_L             0x146
#define   R146                                   0x146

#define   R147_REG_RX_TR_DEV_OUTER_H             0x147
#define   R147                                   0x147

#define   R147_REG_RX_TR_DEV_OUTER_H_Pos         0
#define   R147_REG_RX_TR_DEV_OUTER_H_Msk         (0x0f << R147_REG_RX_TR_DEV_OUTER_H_Pos)

//--------------------------------------------------------------------------------------------------
#define  R148_REG_RX_TR_DEV_INNER               0x148

#define   R148_REG_RX_TR_DEV_INNER_L             0x148
#define   R148                                   0x148

#define   R149_REG_RX_TR_DEV_INNER_H             0x149
#define   R149                                   0x149

//--------------------------------------------------------------------------------------------------
#define   R14A_REG_FREQC_L                       0x14a
#define   R14A                                   0x14a

//--------------------------------------------------------------------------------------------------
#define   R14B                                   0x14b

#define  R14B_REG_FREQC_H_Pos                   0
#define  R14B_REG_FREQC_H_Msk                   (0x03 << R14B_REG_FREQC_H_Pos)

#define  R14B_HIGH_DEV_DECIMAT_NUM_Pos          2
#define  R14B_HIGH_DEV_DECIMAT_NUM_Msk          (0x0f << R14B_HIGH_DEV_DECIMAT_NUM_Pos)

#define  R14B_HIGH_DEV_DECIMAT_EN_Pos           6
#define  R14B_HIGH_DEV_DECIMAT_EN_Msk           (0x01 << R14B_HIGH_DEV_DECIMAT_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R14C                                   0x14c

#define  R14C_REG_PA_OSIDE_TIME_Pos             0
#define  R14C_REG_PA_OSIDE_TIME_Msk             (0x7f << R14C_REG_PA_OSIDE_TIME_Pos)

#define  R14C_REG_PA_OSIDE_EN_Pos               7
#define  R14C_REG_PA_OSIDE_EN_Msk               (0x01 << R14C_REG_PA_OSIDE_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R14D                                   0x14d

#define  R14D_PLL_VCO_TXCTK_Pos                 0
#define  R14D_PLL_VCO_TXCTK_Msk                 (0x03 << R14D_PLL_VCO_TXCTK_Pos)

#define  R14D_RX_TIA_CAPTUNE_SEL_Pos            2
#define  R14D_RX_TIA_CAPTUNE_SEL_Msk            (0x01 << R14D_RX_TIA_CAPTUNE_SEL_Pos)

#define  R14D_OCLK_500K_SEL_Pos                 3
#define  R14D_OCLK_500K_SEL_Msk                 (0x01 << R14D_OCLK_500K_SEL_Pos)

#define  R14D_RX_MIX_IQ_SEL_Pos                 4
#define  R14D_RX_MIX_IQ_SEL_Msk                 (0x01 << R14D_RX_MIX_IQ_SEL_Pos)

#define  R14D_RX_ADC_IFSEL_Pos                  5
#define  R14D_RX_ADC_IFSEL_Msk                  (0x03 << R14D_RX_ADC_IFSEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R14E                                   0x14e

#define  R14E_PA_2ND_RAMP_Pos                   0
#define  R14E_PA_2ND_RAMP_Msk                   (0x3f << R14E_PA_2ND_RAMP_Pos)

#define  R14E_RX_ADC_BWSEL_Pos                  6
#define  R14E_RX_ADC_BWSEL_Msk                  (0x03 << R14E_RX_ADC_BWSEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R14F_RX_ADC_CAPTUNE                    0x14f
#define   R14F                                   0x14f

#define  R14F_RX_ADC_CAPTUNE_Pos                0
#define  R14F_RX_ADC_CAPTUNE_Msk                (0x3f << R14F_RX_ADC_CAPTUNE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R150                                   0x150

#define  R150_OCLK_SRC_SEL_Pos                  0
#define  R150_OCLK_SRC_SEL_Msk                  (0x01 << R150_OCLK_SRC_SEL_Pos)

#define  R150_OCLK_EN_Pos                       1
#define  R150_OCLK_EN_Msk                       (0x01 << R150_OCLK_EN_Pos)

#define  R150_OCLK_DIV_SEL_Pos                  2
#define  R150_OCLK_DIV_SEL_Msk                  (0x03 << R150_OCLK_DIV_SEL_Pos)

#define  R150_REG_CHF_SEL_Pos                   4
#define  R150_REG_CHF_SEL_Msk                   (0x0f << R150_REG_CHF_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R151_IF_L0                             0x151
#define   R151                                   0x151

//--------------------------------------------------------------------------------------------------
#define   R152_IF_L1                             0x152
#define   R152                                   0x152

//--------------------------------------------------------------------------------------------------
#define   R153                                   0x153

#define  R153_IF_H_Pos                          0
#define  R153_IF_H_Msk                          (0x0f << R153_IF_H_Pos)

#define  R153_REG_RX_CFG_MODE_Pos               4
#define  R153_REG_RX_CFG_MODE_Msk               (0x03 << R153_REG_RX_CFG_MODE_Pos)

#define  R153_REG_TX_CFG_MODE_Pos               6
#define  R153_REG_TX_CFG_MODE_Msk               (0x01 << R153_REG_TX_CFG_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R154_REG_RX_TIMEOUT_L                  0x154
#define   R154                                   0x154

//--------------------------------------------------------------------------------------------------
#define   R155_REG_RX_TIMEOUT_H                  0x155
#define   R155                                   0x155

//--------------------------------------------------------------------------------------------------
#define   R156_TP_CODE_COVER_L                   0x156
#define   R156                                   0x156

//--------------------------------------------------------------------------------------------------
#define   R157                                   0x157

#define  R157_TP_CODE_COVER_H_Pos               0
#define  R157_TP_CODE_COVER_H_Msk               (0x7f << R157_TP_CODE_COVER_H_Pos)

#define  R157_IB_ONLY_Pos                       7
#define  R157_IB_ONLY_Msk                       (0x01 << R157_IB_ONLY_Pos)

//--------------------------------------------------------------------------------------------------
#define   R158_OB_SCALING_L                      0x158
#define   R158                                   0x158

//--------------------------------------------------------------------------------------------------
#define   R159                                   0x159

#define  R159_OB_SCALING_H_Pos                  0
#define  R159_OB_SCALING_H_Msk                  (0x07 << R159_OB_SCALING_H_Pos)

#define  R159_TP_CODE_GROUP_SEL_Pos             3
#define  R159_TP_CODE_GROUP_SEL_Msk             (0x03 << R159_TP_CODE_GROUP_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define  R15A_IB_SCL_CODE                       0x15a

#define   R15A_IB_SCL_CODE_L                     0x15a
#define   R15A                                   0x15a

#define   R15B_IB_SCL_CODE_H                     0x15b
#define   R15B                                   0x15b

//--------------------------------------------------------------------------------------------------
#define   R15C_VCO_CODE_AUTO_RX                  0x15c
#define   R15C                                   0x15c

//--------------------------------------------------------------------------------------------------
#define   R15D_TIE0_BIT                          0x15d
#define   R15D                                   0x15d

//--------------------------------------------------------------------------------------------------
#define   R15E                                   0x15e

#define  R15E_TWO_POINT_AUTO_CODE0_Pos          0
#define  R15E_TWO_POINT_AUTO_CODE0_Msk          (0x1f << R15E_TWO_POINT_AUTO_CODE0_Pos)

#define  R15E_VCO_CAL_DONE_Pos                  5
#define  R15E_VCO_CAL_DONE_Msk                  (0x01 << R15E_VCO_CAL_DONE_Pos)

#define  R15E_TWO_POINT_CAL_DONE_Pos            6
#define  R15E_TWO_POINT_CAL_DONE_Msk            (0x01 << R15E_TWO_POINT_CAL_DONE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R15F                                   0x15f

#define  R15F_TWO_POINT_AUTO_CODE1_Pos          0
#define  R15F_TWO_POINT_AUTO_CODE1_Msk          (0x1f << R15F_TWO_POINT_AUTO_CODE1_Pos)

#define  R15F_BUCK_IMAX_CAL_FINISH_Pos          6
#define  R15F_BUCK_IMAX_CAL_FINISH_Msk          (0x01 << R15F_BUCK_IMAX_CAL_FINISH_Pos)

#define  R15F_BUCK_ZERO_CAL_FINISH_Pos          7
#define  R15F_BUCK_ZERO_CAL_FINISH_Msk          (0x01 << R15F_BUCK_ZERO_CAL_FINISH_Pos)

//--------------------------------------------------------------------------------------------------
#define   R160                                   0x160

#define  R160_TWO_POINT_AUTO_CODE2_Pos          0
#define  R160_TWO_POINT_AUTO_CODE2_Msk          (0x1f << R160_TWO_POINT_AUTO_CODE2_Pos)

#define  R160_BUCK_CAL_FINISH_Pos               5
#define  R160_BUCK_CAL_FINISH_Msk               (0x01 << R160_BUCK_CAL_FINISH_Pos)

//--------------------------------------------------------------------------------------------------
#define   R161_TWO_POINT_AUTO_CODE3              0x161
#define   R161                                   0x161

#define  R161_TWO_POINT_AUTO_CODE3_Pos          0
#define  R161_TWO_POINT_AUTO_CODE3_Msk          (0x1f << R161_TWO_POINT_AUTO_CODE3_Pos)

//--------------------------------------------------------------------------------------------------
#define   R162_TP_CAL_CODE                       0x162
#define   R162                                   0x162

#define  R162_TP_CAL_CODE_Pos                   0
#define  R162_TP_CAL_CODE_Msk                   (0x1f << R162_TP_CAL_CODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R163_VCO_CODE_AUTO_TX                  0x163
#define   R163                                   0x163

#define  R163_VCO_CODE_AUTO_TX_Pos              0
#define  R163_VCO_CODE_AUTO_TX_Msk              (0x3f << R163_VCO_CODE_AUTO_TX_Pos)

//--------------------------------------------------------------------------------------------------
#define   R164                                   0x164

#define  R164_CODE_OFFSET_Pos                   0
#define  R164_CODE_OFFSET_Msk                   (0x07 << R164_CODE_OFFSET_Pos)

#define  R164_SPI_CAL_TRIG_Pos                  3
#define  R164_SPI_CAL_TRIG_Msk                  (0x01 << R164_SPI_CAL_TRIG_Pos)

#define  R164_TWO_POINT_SPI_TRIG_Pos            4
#define  R164_TWO_POINT_SPI_TRIG_Msk            (0x01 << R164_TWO_POINT_SPI_TRIG_Pos)

#define  R164_EN_VCO_CAL_Pos                    5
#define  R164_EN_VCO_CAL_Msk                    (0x01 << R164_EN_VCO_CAL_Pos)

#define  R164_EN_TWO_POINT_CAL_Pos              6
#define  R164_EN_TWO_POINT_CAL_Msk              (0x01 << R164_EN_TWO_POINT_CAL_Pos)

#define  R164_TWO_POINT_CLK_EN_Pos              7
#define  R164_TWO_POINT_CLK_EN_Msk              (0x01 << R164_TWO_POINT_CLK_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R165_TWO_POINT_MANUL_CODE_IN0          0x165
#define   R165                                   0x165

#define  R165_TWO_POINT_MANUL_CODE_IN0_Pos      0
#define  R165_TWO_POINT_MANUL_CODE_IN0_Msk      (0x1f << R165_TWO_POINT_MANUL_CODE_IN0_Pos)

//--------------------------------------------------------------------------------------------------
#define   R166_TWO_POINT_MANUL_CODE_IN1          0x166
#define   R166                                   0x166

#define  R166_TWO_POINT_MANUL_CODE_IN1_Pos      0
#define  R166_TWO_POINT_MANUL_CODE_IN1_Msk      (0x1f << R166_TWO_POINT_MANUL_CODE_IN1_Pos)

//--------------------------------------------------------------------------------------------------
#define   R167_TWO_POINT_MANUL_CODE_IN2          0x167
#define   R167                                   0x167

#define  R167_TWO_POINT_MANUL_CODE_IN2_Pos      0
#define  R167_TWO_POINT_MANUL_CODE_IN2_Msk      (0x1f << R167_TWO_POINT_MANUL_CODE_IN2_Pos)

//--------------------------------------------------------------------------------------------------
#define   R168                                   0x168

#define  R168_TWO_POINT_MANUL_CODE_IN3_Pos      0
#define  R168_TWO_POINT_MANUL_CODE_IN3_Msk      (0x1f << R168_TWO_POINT_MANUL_CODE_IN3_Pos)

#define  R168_AUTO_START_2P_CAL_Pos             7
#define  R168_AUTO_START_2P_CAL_Msk             (0x01 << R168_AUTO_START_2P_CAL_Pos)

//--------------------------------------------------------------------------------------------------
#define  R169_REF_DIFF                          0x169

#define   R169_REF_DIFF_L                        0x169
#define   R169                                   0x169

#define   R16A_REF_DIFF_H                        0x16a
#define   R16A                                   0x16a

//--------------------------------------------------------------------------------------------------
#define   R16B                                   0x16b

#define  R16B_FIFO_ENDIAN_Pos                   0
#define  R16B_FIFO_ENDIAN_Msk                   (0x01 << R16B_FIFO_ENDIAN_Pos)

#define  R16B_FIFO_MODE_Pos                     1
#define  R16B_FIFO_MODE_Msk                     (0x03 << R16B_FIFO_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R186                                   0x186

#define  R186_REG_SYMB_AB_SEL_Pos               0
#define  R186_REG_SYMB_AB_SEL_Msk               (0x01 << R186_REG_SYMB_AB_SEL_Pos)

#define  R186_REG_MODTYPE_Pos                   2
#define  R186_REG_MODTYPE_Msk                   (0x03 << R186_REG_MODTYPE_Pos)

#define  R186_REG_SYMBRATE_B_Pos                4
#define  R186_REG_SYMBRATE_B_Msk                (0x0f << R186_REG_SYMBRATE_B_Pos)

//--------------------------------------------------------------------------------------------------
#define   R187_REG_SYMBRATE_A_L                  0x187
#define   R187                                   0x187

//--------------------------------------------------------------------------------------------------
#define   R188                                   0x188

#define  R188_REG_SYMBRATE_A_H_Pos              0
#define  R188_REG_SYMBRATE_A_H_Msk              (0x01 << R188_REG_SYMBRATE_A_H_Pos)

#define  R188_REG_PACKET_MODE_Pos               1
#define  R188_REG_PACKET_MODE_Msk               (0x03 << R188_REG_PACKET_MODE_Pos)

#define  R188_PREAMBLE_TRIG_SEL_Pos             3
#define  R188_PREAMBLE_TRIG_SEL_Msk             (0x01 << R188_PREAMBLE_TRIG_SEL_Pos)

#define  R188_SYNCWORD2_FEC_EN_Pos              4
#define  R188_SYNCWORD2_FEC_EN_Msk              (0x01 << R188_SYNCWORD2_FEC_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R189_REG_SYNC_WORD                     0x189
#define  R189_REG_SYNC_WORD_L16                 0x189
#define  R18B_REG_SYNC_WORD_H16                 0x18b

#define   R189_REG_SYNC_WORD_L1                  0x189
#define   R189                                   0x189

#define   R18A_REG_SYNC_WORD_L2                  0x18a
#define   R18A                                   0x18a

#define   R18B_REG_SYNC_WORD_L3                  0x18b
#define   R18B                                   0x18b

#define   R18C_REG_SYNC_WORD_H                   0x18c
#define   R18C                                   0x18c

//--------------------------------------------------------------------------------------------------
#define  R18D_REG_SYNC_WORD2                    0x18d
#define  R18D_REG_SYNC_WORD2_L16                0x18d
#define  R18F_REG_SYNC_WORD2_H16                0x18f

#define   R18D_REG_SYNC_WORD2_L1                 0x18d
#define   R18D                                   0x18d

#define   R18E_REG_SYNC_WORD2_L2                 0x18e
#define   R18E                                   0x18e

#define   R18F_REG_SYNC_WORD2_L3                 0x18f
#define   R18F                                   0x18f

#define   R190_REG_SYNC_WORD2_H                  0x190
#define   R190                                   0x190

//--------------------------------------------------------------------------------------------------
#define  R191_REG_FREQ_STEP                     0x191

#define   R191_REG_FREQ_STEP_L                   0x191
#define   R191                                   0x191

#define   R192_REG_FREQ_STEP_H                   0x192
#define   R192                                   0x192

//--------------------------------------------------------------------------------------------------
#define  R193_REG_CHANNEL_NUM                   0x193

#define   R193_REG_CHANNEL_NUM_L                 0x193
#define   R193                                   0x193

#define   R194_REG_CHANNEL_NUM_H                 0x194
#define   R194                                   0x194

//--------------------------------------------------------------------------------------------------
#define  R195_REG_BASE_FREQ                     0x195
#define  R195_REG_BASE_FREQ_L16                 0x195
#define  R197_REG_BASE_FREQ_H16                 0x197

#define   R195_REG_BASE_FREQ_L1                  0x195
#define   R195                                   0x195

#define   R196_REG_BASE_FREQ_L2                  0x196
#define   R196                                   0x196

#define   R197_REG_BASE_FREQ_L3                  0x197
#define   R197                                   0x197

#define   R198_REG_BASE_FREQ_H                   0x198
#define   R198                                   0x198

//--------------------------------------------------------------------------------------------------
#define   R199_REG_RX_ADJUST_L1                  0x199
#define   R199                                   0x199

//--------------------------------------------------------------------------------------------------
#define   R19A_REG_RX_ADJUST_L2                  0x19a
#define   R19A                                   0x19a

//--------------------------------------------------------------------------------------------------
#define   R19B_REG_RX_ADJUST_H                   0x19b
#define   R19B                                   0x19b

//--------------------------------------------------------------------------------------------------
#define  R19C_FIELD1_LENGTH                     0x19c

#define   R19C_FIELD1_LENGTH_L                   0x19c
#define   R19C                                   0x19c

#define   R19D_FIELD1_LENGTH_H                   0x19d
#define   R19D                                   0x19d

//--------------------------------------------------------------------------------------------------
#define   R19E                                   0x19e

#define  R19E_REG_TX_DONE_MASK_Pos              0
#define  R19E_REG_TX_DONE_MASK_Msk              (0x01 << R19E_REG_TX_DONE_MASK_Pos)

#define  R19E_REG_RX_TIMEOUT_MASK_Pos           1
#define  R19E_REG_RX_TIMEOUT_MASK_Msk           (0x01 << R19E_REG_RX_TIMEOUT_MASK_Pos)

#define  R19E_REG_RX_PL_CRC_ERR_MASK_Pos        2
#define  R19E_REG_RX_PL_CRC_ERR_MASK_Msk        (0x01 << R19E_REG_RX_PL_CRC_ERR_MASK_Pos)

#define  R19E_REG_RX_DONE_MASK_Pos              3
#define  R19E_REG_RX_DONE_MASK_Msk              (0x01 << R19E_REG_RX_DONE_MASK_Pos)

#define  R19E_REG_RX_PRE_DONE_MASK_Pos          4
#define  R19E_REG_RX_PRE_DONE_MASK_Msk          (0x01 << R19E_REG_RX_PRE_DONE_MASK_Pos)

#define  R19E_REG_RX_SYNC_DONE_MASK_Pos         5
#define  R19E_REG_RX_SYNC_DONE_MASK_Msk         (0x01 << R19E_REG_RX_SYNC_DONE_MASK_Pos)

#define  R19E_REG_RX_PRE_TIMEOUT_MASK_Pos       6
#define  R19E_REG_RX_PRE_TIMEOUT_MASK_Msk       (0x01 << R19E_REG_RX_PRE_TIMEOUT_MASK_Pos)

#define  R19E_REG_RX_TIMEOUT_IMMED_Pos          7
#define  R19E_REG_RX_TIMEOUT_IMMED_Msk          (0x01 << R19E_REG_RX_TIMEOUT_IMMED_Pos)

//--------------------------------------------------------------------------------------------------
#define   R19F                                   0x19f

#define  R19F_REG_RX_SYNC_TIMEOUT_MASK_Pos      0
#define  R19F_REG_RX_SYNC_TIMEOUT_MASK_Msk      (0x01 << R19F_REG_RX_SYNC_TIMEOUT_MASK_Pos)

#define  R19F_REG_TRX_SWITCH_MODE_Pos           1
#define  R19F_REG_TRX_SWITCH_MODE_Msk           (0x01 << R19F_REG_TRX_SWITCH_MODE_Pos)

#define  R19F_REG_M802_WHITEN_ERR_MASK_Pos      2
#define  R19F_REG_M802_WHITEN_ERR_MASK_Msk      (0x01 << R19F_REG_M802_WHITEN_ERR_MASK_Pos)

#define  R19F_REG_RX_RSSI_VLD_MASK_Pos          3
#define  R19F_REG_RX_RSSI_VLD_MASK_Msk          (0x01 << R19F_REG_RX_RSSI_VLD_MASK_Pos)

#define  R19F_REG_F2_DONE_MASK_Pos              4
#define  R19F_REG_F2_DONE_MASK_Msk              (0x01 << R19F_REG_F2_DONE_MASK_Pos)

#define  R19F_REG_F3_DONE_MASK_Pos              5
#define  R19F_REG_F3_DONE_MASK_Msk              (0x01 << R19F_REG_F3_DONE_MASK_Pos)

#define  R19F_REG_F4_DONE_MASK_Pos              6
#define  R19F_REG_F4_DONE_MASK_Msk              (0x01 << R19F_REG_F4_DONE_MASK_Pos)

#define  R19F_REG_F5_DONE_MASK_Pos              7
#define  R19F_REG_F5_DONE_MASK_Msk              (0x01 << R19F_REG_F5_DONE_MASK_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1A0                                   0x1a0

#define  R1A0_REG_NODE_ID_VLD_MASK_Pos          0
#define  R1A0_REG_NODE_ID_VLD_MASK_Msk          (0x01 << R1A0_REG_NODE_ID_VLD_MASK_Pos)

#define  R1A0_TX_WFULL_MASK_Pos                 1
#define  R1A0_TX_WFULL_MASK_Msk                 (0x01 << R1A0_TX_WFULL_MASK_Pos)

#define  R1A0_TX_REMPTY_MASK_Pos                2
#define  R1A0_TX_REMPTY_MASK_Msk                (0x01 << R1A0_TX_REMPTY_MASK_Pos)

#define  R1A0_RX_WFULL_MASK_Pos                 3
#define  R1A0_RX_WFULL_MASK_Msk                 (0x01 << R1A0_RX_WFULL_MASK_Pos)

#define  R1A0_RX_REMPTY_MASK_Pos                4
#define  R1A0_RX_REMPTY_MASK_Msk                (0x01 << R1A0_RX_REMPTY_MASK_Pos)

#define  R1A0_REG_IRQ_PULSE_CHECK_MODE_Pos      5
#define  R1A0_REG_IRQ_PULSE_CHECK_MODE_Msk      (0x01 << R1A0_REG_IRQ_PULSE_CHECK_MODE_Pos)

#define  R1A0_REG_RSSI_TIMEOUT_MASK_Pos         6
#define  R1A0_REG_RSSI_TIMEOUT_MASK_Msk         (0x01 << R1A0_REG_RSSI_TIMEOUT_MASK_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1A1                                   0x1a1

#define  R1A1_REG_TX_DONE_IRQ_Pos               0
#define  R1A1_REG_TX_DONE_IRQ_Msk               (0x01 << R1A1_REG_TX_DONE_IRQ_Pos)

#define  R1A1_REG_RX_TIMEOUT_IRQ_Pos            1
#define  R1A1_REG_RX_TIMEOUT_IRQ_Msk            (0x01 << R1A1_REG_RX_TIMEOUT_IRQ_Pos)

#define  R1A1_REG_RX_PL_CRC_ERR_IRQ_Pos         2
#define  R1A1_REG_RX_PL_CRC_ERR_IRQ_Msk         (0x01 << R1A1_REG_RX_PL_CRC_ERR_IRQ_Pos)

#define  R1A1_REG_RX_DONE_IRQ_Pos               3
#define  R1A1_REG_RX_DONE_IRQ_Msk               (0x01 << R1A1_REG_RX_DONE_IRQ_Pos)

#define  R1A1_REG_RX_PRE_DONE_IRQ_Pos           4
#define  R1A1_REG_RX_PRE_DONE_IRQ_Msk           (0x01 << R1A1_REG_RX_PRE_DONE_IRQ_Pos)

#define  R1A1_REG_RX_SYNC_DONE_IRQ_Pos          5
#define  R1A1_REG_RX_SYNC_DONE_IRQ_Msk          (0x01 << R1A1_REG_RX_SYNC_DONE_IRQ_Pos)

#define  R1A1_REG_PRE_TIMEOUT_IRQ_Pos           6
#define  R1A1_REG_PRE_TIMEOUT_IRQ_Msk           (0x01 << R1A1_REG_PRE_TIMEOUT_IRQ_Pos)

#define  R1A1_REG_SYNC_TIMEOUT_IRQ_Pos          7
#define  R1A1_REG_SYNC_TIMEOUT_IRQ_Msk          (0x01 << R1A1_REG_SYNC_TIMEOUT_IRQ_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1A2                                   0x1a2

#define  R1A2_RX_F2_DONE_IRQ_Pos                0
#define  R1A2_RX_F2_DONE_IRQ_Msk                (0x01 << R1A2_RX_F2_DONE_IRQ_Pos)

#define  R1A2_RX_F3_DONE_IRQ_Pos                1
#define  R1A2_RX_F3_DONE_IRQ_Msk                (0x01 << R1A2_RX_F3_DONE_IRQ_Pos)

#define  R1A2_RX_F4_DONE_IRQ_Pos                2
#define  R1A2_RX_F4_DONE_IRQ_Msk                (0x01 << R1A2_RX_F4_DONE_IRQ_Pos)

#define  R1A2_RX_F5_DONE_IRQ_Pos                3
#define  R1A2_RX_F5_DONE_IRQ_Msk                (0x01 << R1A2_RX_F5_DONE_IRQ_Pos)

#define  R1A2_RX_F2_CRC_ERR_IRQ_Pos             4
#define  R1A2_RX_F2_CRC_ERR_IRQ_Msk             (0x01 << R1A2_RX_F2_CRC_ERR_IRQ_Pos)

#define  R1A2_RX_F3_CRC_ERR_IRQ_Pos             5
#define  R1A2_RX_F3_CRC_ERR_IRQ_Msk             (0x01 << R1A2_RX_F3_CRC_ERR_IRQ_Pos)

#define  R1A2_RX_F4_CRC_ERR_IRQ_Pos             6
#define  R1A2_RX_F4_CRC_ERR_IRQ_Msk             (0x01 << R1A2_RX_F4_CRC_ERR_IRQ_Pos)

#define  R1A2_RX_F5_CRC_ERR_IRQ_Pos             7
#define  R1A2_RX_F5_CRC_ERR_IRQ_Msk             (0x01 << R1A2_RX_F5_CRC_ERR_IRQ_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1A3                                   0x1a3

#define  R1A3_RX_RSSI_VLD_IRQ_Pos               0
#define  R1A3_RX_RSSI_VLD_IRQ_Msk               (0x01 << R1A3_RX_RSSI_VLD_IRQ_Pos)

#define  R1A3_NODE_ID_VLD_IRQ_Pos               1
#define  R1A3_NODE_ID_VLD_IRQ_Msk               (0x01 << R1A3_NODE_ID_VLD_IRQ_Pos)

#define  R1A3_RX_M802_WHIT_ERR_IRQ_Pos          2
#define  R1A3_RX_M802_WHIT_ERR_IRQ_Msk          (0x01 << R1A3_RX_M802_WHIT_ERR_IRQ_Pos)

#define  R1A3_TX_WFULL_IRQ_Pos                  3
#define  R1A3_TX_WFULL_IRQ_Msk                  (0x01 << R1A3_TX_WFULL_IRQ_Pos)

#define  R1A3_TX_REMPTY_IRQ_Pos                 4
#define  R1A3_TX_REMPTY_IRQ_Msk                 (0x01 << R1A3_TX_REMPTY_IRQ_Pos)

#define  R1A3_RX_WFULL_IRQ_Pos                  5
#define  R1A3_RX_WFULL_IRQ_Msk                  (0x01 << R1A3_RX_WFULL_IRQ_Pos)

#define  R1A3_RX_REMPTY_IRQ_Pos                 6
#define  R1A3_RX_REMPTY_IRQ_Msk                 (0x01 << R1A3_RX_REMPTY_IRQ_Pos)

#define  R1A3_REG_RSSI_TIMEOUT_IRQ_Pos          7
#define  R1A3_REG_RSSI_TIMEOUT_IRQ_Msk          (0x01 << R1A3_REG_RSSI_TIMEOUT_IRQ_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1A4                                   0x1a4

#define  R1A4_REG_2POINT_CAL_EN_Pos             0
#define  R1A4_REG_2POINT_CAL_EN_Msk             (0x01 << R1A4_REG_2POINT_CAL_EN_Pos)

#define  R1A4_REG_RX_CRC_ERR_RST_Pos            2
#define  R1A4_REG_RX_CRC_ERR_RST_Msk            (0x01 << R1A4_REG_RX_CRC_ERR_RST_Pos)

#define  R1A4_REG_RX_DONE_RST_TEST_Pos          3
#define  R1A4_REG_RX_DONE_RST_TEST_Msk          (0x01 << R1A4_REG_RX_DONE_RST_TEST_Pos)

#define  R1A4_REG_GPIO_TX_MODE_Pos              4
#define  R1A4_REG_GPIO_TX_MODE_Msk              (0x01 << R1A4_REG_GPIO_TX_MODE_Pos)

#define  R1A4_REG_GPIO_RX_MODE_Pos              5
#define  R1A4_REG_GPIO_RX_MODE_Msk              (0x01 << R1A4_REG_GPIO_RX_MODE_Pos)

#define  R1A4_REG_TX_FIFO_FULL_Pos              6
#define  R1A4_REG_TX_FIFO_FULL_Msk              (0x01 << R1A4_REG_TX_FIFO_FULL_Pos)

#define  R1A4_REG_TIMEOUT_EN_Pos                7
#define  R1A4_REG_TIMEOUT_EN_Msk                (0x01 << R1A4_REG_TIMEOUT_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R1A5_PREAMBLE_TIMEOUT_TH               0x1a5

#define   R1A5_PREAMBLE_TIMEOUT_TH_L             0x1a5
#define   R1A5                                   0x1a5

#define   R1A6_PREAMBLE_TIMEOUT_TH_H             0x1a6
#define   R1A6                                   0x1a6

//--------------------------------------------------------------------------------------------------
#define  R1A7_SYNCWORD_TIMEOUT_TH               0x1a7

#define   R1A7_SYNCWORD_TIMEOUT_TH_L             0x1a7
#define   R1A7                                   0x1a7

#define   R1A8_SYNCWORD_TIMEOUT_TH_H             0x1a8
#define   R1A8                                   0x1a8

//--------------------------------------------------------------------------------------------------
#define  R1A9_RSSI_TIMEOUT_TH                   0x1a9

#define   R1A9_RSSI_TIMEOUT_TH_L                 0x1a9
#define   R1A9                                   0x1a9

#define   R1AA_RSSI_TIMEOUT_TH_H                 0x1aa
#define   R1AA                                   0x1aa

//--------------------------------------------------------------------------------------------------
#define   R1AB_RSSI_WIDTH_TH                     0x1ab
#define   R1AB                                   0x1ab

//--------------------------------------------------------------------------------------------------
#define   R1AC_RSSI_BUSY_THRE                    0x1ac
#define   R1AC                                   0x1ac

//--------------------------------------------------------------------------------------------------
#define  R1AD_RX_PL_LENGTH                      0x1ad

#define   R1AD_RX_PL_LENGTH_L                    0x1ad
#define   R1AD                                   0x1ad

#define   R1AE_RX_PL_LENGTH_H                    0x1ae
#define   R1AE                                   0x1ae

//--------------------------------------------------------------------------------------------------
#define   R1AF                                   0x1af

#define  R1AF_GPIO0_PUEN_Pos                    0
#define  R1AF_GPIO0_PUEN_Msk                    (0x01 << R1AF_GPIO0_PUEN_Pos)

#define  R1AF_GPIO1_PUEN_Pos                    1
#define  R1AF_GPIO1_PUEN_Msk                    (0x01 << R1AF_GPIO1_PUEN_Pos)

#define  R1AF_GPIO2_PUEN_Pos                    2
#define  R1AF_GPIO2_PUEN_Msk                    (0x01 << R1AF_GPIO2_PUEN_Pos)

#define  R1AF_GPIO0_PDEN_Pos                    3
#define  R1AF_GPIO0_PDEN_Msk                    (0x01 << R1AF_GPIO0_PDEN_Pos)

#define  R1AF_GPIO1_PDEN_Pos                    4
#define  R1AF_GPIO1_PDEN_Msk                    (0x01 << R1AF_GPIO1_PDEN_Pos)

#define  R1AF_GPIO2_PDEN_Pos                    5
#define  R1AF_GPIO2_PDEN_Msk                    (0x01 << R1AF_GPIO2_PDEN_Pos)

#define  R1AF_VPP_MUX_Pos                       6
#define  R1AF_VPP_MUX_Msk                       (0x01 << R1AF_VPP_MUX_Pos)

#define  R1AF_GPIO11_MUX_Pos                    R1AF_VPP_MUX_Pos
#define  R1AF_GPIO11_MUX_Msk                    R1AF_VPP_MUX_Msk

//--------------------------------------------------------------------------------------------------
#define   R1B0                                   0x1b0

#define  R1B0_GPIO0_DIEN_Pos                    0
#define  R1B0_GPIO0_DIEN_Msk                    (0x01 << R1B0_GPIO0_DIEN_Pos)

#define  R1B0_GPIO1_DIEN_Pos                    1
#define  R1B0_GPIO1_DIEN_Msk                    (0x01 << R1B0_GPIO1_DIEN_Pos)

#define  R1B0_GPIO2_DIEN_Pos                    2
#define  R1B0_GPIO2_DIEN_Msk                    (0x01 << R1B0_GPIO2_DIEN_Pos)

#define  R1B0_VPP_DIEN_Pos                      3
#define  R1B0_VPP_DIEN_Msk                      (0x01 << R1B0_VPP_DIEN_Pos)

#define  R1B0_GPIO11_DIEN_Pos                   R1B0_VPP_DIEN_Pos
#define  R1B0_GPIO11_DIEN_Msk                   R1B0_VPP_DIEN_Msk

#define  R1B0_GPIO0_OE_Pos                      4
#define  R1B0_GPIO0_OE_Msk                      (0x01 << R1B0_GPIO0_OE_Pos)

#define  R1B0_GPIO1_OE_Pos                      5
#define  R1B0_GPIO1_OE_Msk                      (0x01 << R1B0_GPIO1_OE_Pos)

#define  R1B0_GPIO2_OE_Pos                      6
#define  R1B0_GPIO2_OE_Msk                      (0x01 << R1B0_GPIO2_OE_Pos)

#define  R1B0_VPP_OE_Pos                        7
#define  R1B0_VPP_OE_Msk                        (0x01 << R1B0_VPP_OE_Pos)

#define  R1B0_GPIO11_OE_Pos                     R1B0_VPP_OE_Pos
#define  R1B0_GPIO11_OE_Msk                     R1B0_VPP_OE_Msk

//--------------------------------------------------------------------------------------------------
#define   R1B1                                   0x1b1

#define  R1B1_GPIO1_MUX_Pos                     0
#define  R1B1_GPIO1_MUX_Msk                     (0x0f << R1B1_GPIO1_MUX_Pos)

#define  R1B1_GPIO2_MUX_Pos                     4
#define  R1B1_GPIO2_MUX_Msk                     (0x0f << R1B1_GPIO2_MUX_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1B2                                   0x1b2

#define  R1B2_GPIO0_REG_Pos                     0
#define  R1B2_GPIO0_REG_Msk                     (0x01 << R1B2_GPIO0_REG_Pos)

#define  R1B2_GPIO1_REG_Pos                     1
#define  R1B2_GPIO1_REG_Msk                     (0x01 << R1B2_GPIO1_REG_Pos)

#define  R1B2_GPIO2_REG_Pos                     2
#define  R1B2_GPIO2_REG_Msk                     (0x01 << R1B2_GPIO2_REG_Pos)

#define  R1B2_GPIO11_REG_Pos                    3
#define  R1B2_GPIO11_REG_Msk                    (0x01 << R1B2_GPIO11_REG_Pos)

#define  R1B2_GPIO0_MUX_Pos                     4
#define  R1B2_GPIO0_MUX_Msk                     (0x0f << R1B2_GPIO0_MUX_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1B3                                   0x1b3

#define  R1B3_LO_MUX_SEL_Pos                    0
#define  R1B3_LO_MUX_SEL_Msk                    (0x07 << R1B3_LO_MUX_SEL_Pos)

#define  R1B3_REG_RSSI_PRE_RD_Pos               3
#define  R1B3_REG_RSSI_PRE_RD_Msk               (0x01 << R1B3_REG_RSSI_PRE_RD_Pos)

//--------------------------------------------------------------------------------------------------
#define  R1B4_SIG_PWR                           0x1b4

#define   R1B4_SIG_PWR_L                         0x1b4
#define   R1B4                                   0x1b4

#define   R1B5_SIG_PWR_H                         0x1b5
#define   R1B5                                   0x1b5

//--------------------------------------------------------------------------------------------------
#define  R1B6_NOISE_PWR                         0x1b6

#define   R1B6_NOISE_PWR_L                       0x1b6
#define   R1B6                                   0x1b6

#define   R1B7_NOISE_PWR_H                       0x1b7
#define   R1B7                                   0x1b7

//--------------------------------------------------------------------------------------------------
#define  R1B8_NODE_ID_DEC                       0x1b8
#define  R1B8_NODE_ID_DEC_L16                   0x1b8
#define  R1BA_NODE_ID_DEC_H16                   0x1ba

#define   R1B8_NODE_ID_DEC_L1                    0x1b8
#define   R1B8                                   0x1b8

#define   R1B9_NODE_ID_DEC_L2                    0x1b9
#define   R1B9                                   0x1b9

#define   R1BA_NODE_ID_DEC_L3                    0x1ba
#define   R1BA                                   0x1ba

#define   R1BB_NODE_ID_DEC_H                     0x1bb
#define   R1BB                                   0x1bb

//--------------------------------------------------------------------------------------------------
#define   R1BC_RSSI_R32_HOLD                     0x1bc
#define   R1BC                                   0x1bc

//--------------------------------------------------------------------------------------------------
#define   R1BD_RSSI_RBW_HOLD                     0x1bd
#define   R1BD                                   0x1bd

//--------------------------------------------------------------------------------------------------
#define   R1BE_RSSI_R32_CHG                      0x1be
#define   R1BE                                   0x1be

//--------------------------------------------------------------------------------------------------
#define   R1BF_RSSI_RBW_CHG                      0x1bf
#define   R1BF                                   0x1bf

//--------------------------------------------------------------------------------------------------
#define   R1C0                                   0x1c0

#define  R1C0_FIFO0_WADDR_CLR_Pos               0
#define  R1C0_FIFO0_WADDR_CLR_Msk               (0x01 << R1C0_FIFO0_WADDR_CLR_Pos)

#define  R1C0_FIFO0_WADDR_SET_Pos               1
#define  R1C0_FIFO0_WADDR_SET_Msk               (0x01 << R1C0_FIFO0_WADDR_SET_Pos)

#define  R1C0_FIFO0_RADDR_CLR_Pos               2
#define  R1C0_FIFO0_RADDR_CLR_Msk               (0x01 << R1C0_FIFO0_RADDR_CLR_Pos)

#define  R1C0_FIFO0_RADDR_SET_Pos               3
#define  R1C0_FIFO0_RADDR_SET_Msk               (0x01 << R1C0_FIFO0_RADDR_SET_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1C1                                   0x1c1

#define  R1C1_FIFO1_WADDR_CLR_Pos               0
#define  R1C1_FIFO1_WADDR_CLR_Msk               (0x01 << R1C1_FIFO1_WADDR_CLR_Pos)

#define  R1C1_FIFO1_WADDR_SET_Pos               1
#define  R1C1_FIFO1_WADDR_SET_Msk               (0x01 << R1C1_FIFO1_WADDR_SET_Pos)

#define  R1C1_FIFO1_RADDR_CLR_Pos               2
#define  R1C1_FIFO1_RADDR_CLR_Msk               (0x01 << R1C1_FIFO1_RADDR_CLR_Pos)

#define  R1C1_FIFO1_RADDR_SET_Pos               3
#define  R1C1_FIFO1_RADDR_SET_Msk               (0x01 << R1C1_FIFO1_RADDR_SET_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1C2_FIFO0_ADDR_INI                    0x1c2
#define   R1C2                                   0x1c2

//--------------------------------------------------------------------------------------------------
#define   R1C3_FIFO1_ADDR_INI                    0x1c3
#define   R1C3                                   0x1c3

//--------------------------------------------------------------------------------------------------
#define   R1C4_FIFO0_WFULL_TH                    0x1c4
#define   R1C4                                   0x1c4

//--------------------------------------------------------------------------------------------------
#define   R1C5_FIFO0_REMPTY_TH                   0x1c5
#define   R1C5                                   0x1c5

//--------------------------------------------------------------------------------------------------
#define   R1C6_FIFO1_WFULL_TH                    0x1c6
#define   R1C6                                   0x1c6

//--------------------------------------------------------------------------------------------------
#define   R1C7_FIFO1_REMPTY_TH                   0x1c7
#define   R1C7                                   0x1c7

//--------------------------------------------------------------------------------------------------
#define   R1C8_FIFO0_NUM                         0x1c8
#define   R1C8                                   0x1c8

//--------------------------------------------------------------------------------------------------
#define   R1C9_FIFO1_NUM                         0x1c9
#define   R1C9                                   0x1c9

//--------------------------------------------------------------------------------------------------
#define   R1CA                                   0x1ca

#define  R1CA_RX_REMPTY_Pos                     4
#define  R1CA_RX_REMPTY_Msk                     (0x01 << R1CA_RX_REMPTY_Pos)

#define  R1CA_RX_WFULL_Pos                      5
#define  R1CA_RX_WFULL_Msk                      (0x01 << R1CA_RX_WFULL_Pos)

#define  R1CA_TX_REMPTY_Pos                     6
#define  R1CA_TX_REMPTY_Msk                     (0x01 << R1CA_TX_REMPTY_Pos)

#define  R1CA_TX_WFULL_Pos                      7
#define  R1CA_TX_WFULL_Msk                      (0x01 << R1CA_TX_WFULL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1CB                                   0x1cb

#define  R1CB_REG_MDM_TRIG_SEL1_Pos             0
#define  R1CB_REG_MDM_TRIG_SEL1_Msk             (0x03 << R1CB_REG_MDM_TRIG_SEL1_Pos)

#define  R1CB_REG_MDM_TRIG_SEL2_Pos             2
#define  R1CB_REG_MDM_TRIG_SEL2_Msk             (0x03 << R1CB_REG_MDM_TRIG_SEL2_Pos)

#define  R1CB_PRE_BUSY_MASK_Pos                 4
#define  R1CB_PRE_BUSY_MASK_Msk                 (0x01 << R1CB_PRE_BUSY_MASK_Pos)

#define  R1CB_SW_BUSY_MASK_Pos                  5
#define  R1CB_SW_BUSY_MASK_Msk                  (0x01 << R1CB_SW_BUSY_MASK_Pos)

#define  R1CB_RSSI_BUSY_MASK_Pos                6
#define  R1CB_RSSI_BUSY_MASK_Msk                (0x01 << R1CB_RSSI_BUSY_MASK_Pos)

#define  R1CB_PSDOR_SEQ_VLD_Pos                 7
#define  R1CB_PSDOR_SEQ_VLD_Msk                 (0x01 << R1CB_PSDOR_SEQ_VLD_Pos)

//--------------------------------------------------------------------------------------------------
#define  R1CC_REG_MAX_PL_LEN                    0x1cc

#define   R1CC_REG_MAX_PL_LEN_L                  0x1cc
#define   R1CC                                   0x1cc

#define   R1CD_REG_MAX_PL_LEN_H                  0x1cd
#define   R1CD                                   0x1cd

//--------------------------------------------------------------------------------------------------
#define   R1CE_PSDOR_SEQ_L0                      0x1ce
#define   R1CE                                   0x1ce

//--------------------------------------------------------------------------------------------------
#define   R1CF_PSDOR_SEQ_L1                      0x1cf
#define   R1CF                                   0x1cf

//--------------------------------------------------------------------------------------------------
#define   R1D0_PSDOR_SEQ_L2                      0x1d0
#define   R1D0                                   0x1d0

//--------------------------------------------------------------------------------------------------
#define   R1D1_PSDOR_SEQ_H                       0x1d1
#define   R1D1                                   0x1d1

//--------------------------------------------------------------------------------------------------
#define  R1D2_PIC_RESTART_FLAG                  0x1d2

#define   R1D2_PIC_RESTART_FLAG_L                0x1d2
#define   R1D2                                   0x1d2

#define   R1D3_PIC_RESTART_FLAG_H                0x1d3
#define   R1D3                                   0x1d3

//--------------------------------------------------------------------------------------------------
#define   R1D4                                   0x1d4

#define  R1D4_TEMP_EN_Pos                       0
#define  R1D4_TEMP_EN_Msk                       (0x01 << R1D4_TEMP_EN_Pos)

#define  R1D4_GPIO_DRV_SEL_Pos                  1
#define  R1D4_GPIO_DRV_SEL_Msk                  (0x03 << R1D4_GPIO_DRV_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R1D5_SYNCWORD_LAST_BYTE_MASK           0x1d5
#define   R1D5                                   0x1d5

//--------------------------------------------------------------------------------------------------
#define   R1D6_PREAMBLE_LAST_BYTE_MASK           0x1d6
#define   R1D6                                   0x1d6

//--------------------------------------------------------------------------------------------------
#define   R1D7_SYNCWORD_LAST_BYTE                0x1d7
#define   R1D7                                   0x1d7

//--------------------------------------------------------------------------------------------------
#define   R1D8_PREAMBLE_LAST_BYTE                0x1d8
#define   R1D8                                   0x1d8

//--------------------------------------------------------------------------------------------------
#define   R206                                   0x206

#define  R206_REG_AGC_MANU_EN_Pos               0
#define  R206_REG_AGC_MANU_EN_Msk               (0x01 << R206_REG_AGC_MANU_EN_Pos)

#define  R206_REG_AGC_SEL_Pos                   1
#define  R206_REG_AGC_SEL_Msk                   (0x01 << R206_REG_AGC_SEL_Pos)

#define  R206_REG_AGC_MODE_Pos                  2
#define  R206_REG_AGC_MODE_Msk                  (0x01 << R206_REG_AGC_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define  R207_REG_AGC_MANU                      0x207

#define   R207_REG_AGC_MANU_L                    0x207
#define   R207                                   0x207

#define   R208_REG_AGC_MANU_H                    0x208
#define   R208                                   0x208

//--------------------------------------------------------------------------------------------------
#define   R209_REG_AGC_GAIN_MANU                 0x209
#define   R209                                   0x209

//--------------------------------------------------------------------------------------------------
#define   R20A                                   0x20a

#define  R20A_REG_CMP_SEL2_Pos                  0
#define  R20A_REG_CMP_SEL2_Msk                  (0x07 << R20A_REG_CMP_SEL2_Pos)

#define  R20A_REG_CMP_SEL_Pos                   4
#define  R20A_REG_CMP_SEL_Msk                   (0x07 << R20A_REG_CMP_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define  R20B_REG_AGC_SET01                     0x20b

#define   R20B_REG_AGC_SET01_L                   0x20b
#define   R20B                                   0x20b

#define   R20C_REG_AGC_SET01_H                   0x20c
#define   R20C                                   0x20c

//--------------------------------------------------------------------------------------------------
#define   R20D_REG_AGC_GAIN01                    0x20d
#define   R20D                                   0x20d

//--------------------------------------------------------------------------------------------------
#define   R20E_REG_AGC_TH02                      0x20e
#define   R20E                                   0x20e

//--------------------------------------------------------------------------------------------------
#define  R20F_REG_AGC_SET02                     0x20f

#define   R20F_REG_AGC_SET02_L                   0x20f
#define   R20F                                   0x20f

#define   R210_REG_AGC_SET02_H                   0x210
#define   R210                                   0x210

//--------------------------------------------------------------------------------------------------
#define   R211_REG_AGC_GAIN02                    0x211
#define   R211                                   0x211

//--------------------------------------------------------------------------------------------------
#define   R212_REG_AGC_TH03                      0x212
#define   R212                                   0x212

//--------------------------------------------------------------------------------------------------
#define  R213_REG_AGC_SET03                     0x213

#define   R213_REG_AGC_SET03_L                   0x213
#define   R213                                   0x213

#define   R214_REG_AGC_SET03_H                   0x214
#define   R214                                   0x214

//--------------------------------------------------------------------------------------------------
#define   R215_REG_AGC_GAIN03                    0x215
#define   R215                                   0x215

//--------------------------------------------------------------------------------------------------
#define   R216_REG_AGC_TH04                      0x216
#define   R216                                   0x216

//--------------------------------------------------------------------------------------------------
#define  R217_REG_AGC_SET04                     0x217

#define   R217_REG_AGC_SET04_L                   0x217
#define   R217                                   0x217

#define   R218_REG_AGC_SET04_H                   0x218
#define   R218                                   0x218

//--------------------------------------------------------------------------------------------------
#define   R219_REG_AGC_GAIN04                    0x219
#define   R219                                   0x219

//--------------------------------------------------------------------------------------------------
#define   R21A_REG_AGC_TH05                      0x21a
#define   R21A                                   0x21a

//--------------------------------------------------------------------------------------------------
#define  R21B_REG_AGC_SET05                     0x21b

#define   R21B_REG_AGC_SET05_L                   0x21b
#define   R21B                                   0x21b

#define   R21C_REG_AGC_SET05_H                   0x21c
#define   R21C                                   0x21c

//--------------------------------------------------------------------------------------------------
#define   R21D_REG_AGC_GAIN05                    0x21d
#define   R21D                                   0x21d

//--------------------------------------------------------------------------------------------------
#define   R21E_REG_AGC_TH06                      0x21e
#define   R21E                                   0x21e

//--------------------------------------------------------------------------------------------------
#define  R21F_REG_AGC_SET06                     0x21f

#define   R21F_REG_AGC_SET06_L                   0x21f
#define   R21F                                   0x21f

#define   R220_REG_AGC_SET06_H                   0x220
#define   R220                                   0x220

//--------------------------------------------------------------------------------------------------
#define   R221_REG_AGC_GAIN06                    0x221
#define   R221                                   0x221

//--------------------------------------------------------------------------------------------------
#define   R222_REG_AGC_TH07                      0x222
#define   R222                                   0x222

//--------------------------------------------------------------------------------------------------
#define  R223_REG_AGC_SET07                     0x223

#define   R223_REG_AGC_SET07_L                   0x223
#define   R223                                   0x223

#define   R224_REG_AGC_SET07_H                   0x224
#define   R224                                   0x224

//--------------------------------------------------------------------------------------------------
#define   R225_REG_AGC_GAIN07                    0x225
#define   R225                                   0x225

//--------------------------------------------------------------------------------------------------
#define   R226_REG_AGC_TH08                      0x226
#define   R226                                   0x226

//--------------------------------------------------------------------------------------------------
#define  R227_REG_AGC_SET08                     0x227

#define   R227_REG_AGC_SET08_L                   0x227
#define   R227                                   0x227

#define   R228_REG_AGC_SET08_H                   0x228
#define   R228                                   0x228

//--------------------------------------------------------------------------------------------------
#define   R229_REG_AGC_GAIN08                    0x229
#define   R229                                   0x229

//--------------------------------------------------------------------------------------------------
#define   R22A_REG_BAS_GAIN_STEP                 0x22a
#define   R22A                                   0x22a

//--------------------------------------------------------------------------------------------------
#define   R22B                                   0x22b

#define  R22B_REG_DOWN_CNT_TH_Pos               0
#define  R22B_REG_DOWN_CNT_TH_Msk               (0x0f << R22B_REG_DOWN_CNT_TH_Pos)

#define  R22B_REG_UP_CNT_TH_Pos                 4
#define  R22B_REG_UP_CNT_TH_Msk                 (0x0f << R22B_REG_UP_CNT_TH_Pos)

//--------------------------------------------------------------------------------------------------
#define   R22C_REG_GAIN_GAP                      0x22c
#define   R22C                                   0x22c

//--------------------------------------------------------------------------------------------------
#define   R22D                                   0x22d

#define  R22D_AGC_GAIN_CHG_LEN_Pos              0
#define  R22D_AGC_GAIN_CHG_LEN_Msk              (0x3f << R22D_AGC_GAIN_CHG_LEN_Pos)

#define  R22D_AGC_GAIN_CHG_VLD_Pos              6
#define  R22D_AGC_GAIN_CHG_VLD_Msk              (0x01 << R22D_AGC_GAIN_CHG_VLD_Pos)

#define  R22D_REG_AFC_END_LOCK_AGC_VLD_Pos      7
#define  R22D_REG_AFC_END_LOCK_AGC_VLD_Msk      (0x01 << R22D_REG_AFC_END_LOCK_AGC_VLD_Pos)

//--------------------------------------------------------------------------------------------------
#define   R22E_ALPH_RBW                          0x22e
#define   R22E                                   0x22e

#define  R22E_ALPH_RBW_Pos                      0
#define  R22E_ALPH_RBW_Msk                      (0x0f << R22E_ALPH_RBW_Pos)

//--------------------------------------------------------------------------------------------------
#define   R22F                                   0x22f

#define  R22F_ALPH_PARA2_Pos                    0
#define  R22F_ALPH_PARA2_Msk                    (0x0f << R22F_ALPH_PARA2_Pos)

#define  R22F_ALPH_PARA1_Pos                    4
#define  R22F_ALPH_PARA1_Msk                    (0x0f << R22F_ALPH_PARA1_Pos)

//--------------------------------------------------------------------------------------------------
#define   R230_IIR_VLD_TIME_REG                  0x230
#define   R230                                   0x230

//--------------------------------------------------------------------------------------------------
#define   R231_REG_PE_0DB                        0x231
#define   R231                                   0x231

//--------------------------------------------------------------------------------------------------
#define  R232_REG_GAIN_VLD_TIME                 0x232
#define  R232_REG_GAIN_VLD_TIME_L16             0x232
#define  R234_REG_GAIN_VLD_TIME_H16             0x234

#define   R232_REG_GAIN_VLD_TIME_L1              0x232
#define   R232                                   0x232

#define   R233_REG_GAIN_VLD_TIME_L2              0x233
#define   R233                                   0x233

#define   R234_REG_GAIN_VLD_TIME_L3              0x234
#define   R234                                   0x234

#define   R235_REG_GAIN_VLD_TIME_H               0x235
#define   R235                                   0x235

//--------------------------------------------------------------------------------------------------
#define   R236                                   0x236

#define  R236_DAC_MODE_Pos                      0
#define  R236_DAC_MODE_Msk                      (0x01 << R236_DAC_MODE_Pos)

#define  R236_LOCK_REG_EN_Pos                   1
#define  R236_LOCK_REG_EN_Msk                   (0x01 << R236_LOCK_REG_EN_Pos)

#define  R236_DLY_GATE_BYPASS_Pos               2
#define  R236_DLY_GATE_BYPASS_Msk               (0x01 << R236_DLY_GATE_BYPASS_Pos)

#define  R236_HI_LO_SET_Pos                     3
#define  R236_HI_LO_SET_Msk                     (0x01 << R236_HI_LO_SET_Pos)

#define  R236_CLK32M_GATE_BYPASS_Pos            4
#define  R236_CLK32M_GATE_BYPASS_Msk            (0x01 << R236_CLK32M_GATE_BYPASS_Pos)

#define  R236_PLL_DIG_EN_Pos                    5
#define  R236_PLL_DIG_EN_Msk                    (0x01 << R236_PLL_DIG_EN_Pos)

#define  R236_DAC_CLK_INV_SEL_Pos               6
#define  R236_DAC_CLK_INV_SEL_Msk               (0x01 << R236_DAC_CLK_INV_SEL_Pos)

#define  R236_DSM_FIFO_BYPASS_Pos               7
#define  R236_DSM_FIFO_BYPASS_Msk               (0x01 << R236_DSM_FIFO_BYPASS_Pos)

//--------------------------------------------------------------------------------------------------
#define   R237                                   0x237

#define  R237_DAC_BASL_Pos                      0
#define  R237_DAC_BASL_Msk                      (0x3f << R237_DAC_BASL_Pos)

#define  R237_FBDIV_RSTN_DLY_SEL_Pos            6
#define  R237_FBDIV_RSTN_DLY_SEL_Msk            (0x03 << R237_FBDIV_RSTN_DLY_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R238                                   0x238

#define  R238_VCO_MAXCNT_SEL_Pos                0
#define  R238_VCO_MAXCNT_SEL_Msk                (0x03 << R238_VCO_MAXCNT_SEL_Pos)

#define  R238_CAL_DIV_OVRD_Pos                  2
#define  R238_CAL_DIV_OVRD_Msk                  (0x01 << R238_CAL_DIV_OVRD_Pos)

#define  R238_CALDIV_OVRD_SEL_Pos               3
#define  R238_CALDIV_OVRD_SEL_Msk               (0x01 << R238_CALDIV_OVRD_SEL_Pos)

#define  R238_FBDIV_RSTN_OVRD_Pos               4
#define  R238_FBDIV_RSTN_OVRD_Msk               (0x01 << R238_FBDIV_RSTN_OVRD_Pos)

#define  R238_FBDIV_RSTN_OVRD_SEL_Pos           5
#define  R238_FBDIV_RSTN_OVRD_SEL_Msk           (0x01 << R238_FBDIV_RSTN_OVRD_SEL_Pos)

#define  R238_FBDIV_EN_OVRD_Pos                 6
#define  R238_FBDIV_EN_OVRD_Msk                 (0x01 << R238_FBDIV_EN_OVRD_Pos)

#define  R238_FBDIV_EN_OVRD_SEL_Pos             7
#define  R238_FBDIV_EN_OVRD_SEL_Msk             (0x01 << R238_FBDIV_EN_OVRD_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R239                                   0x239

#define  R239_CTL_DITHER_SHAPE_Pos              1
#define  R239_CTL_DITHER_SHAPE_Msk              (0x01 << R239_CTL_DITHER_SHAPE_Pos)

#define  R239_CTL_DITHER_LSB_Pos                2
#define  R239_CTL_DITHER_LSB_Msk                (0x07 << R239_CTL_DITHER_LSB_Pos)

//--------------------------------------------------------------------------------------------------
#define   R23A_INT_MODE_EN                       0x23a
#define   R23A                                   0x23a

#define  R23A_INT_MODE_EN_Pos                   0
#define  R23A_INT_MODE_EN_Msk                   (0x01 << R23A_INT_MODE_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R23B                                   0x23b

#define  R23B_SHIFT_OFFSET_Pos                  1
#define  R23B_SHIFT_OFFSET_Msk                  (0x01 << R23B_SHIFT_OFFSET_Pos)

#define  R23B_MASH2_MODE_Pos                    2
#define  R23B_MASH2_MODE_Msk                    (0x01 << R23B_MASH2_MODE_Pos)

#define  R23B_INV_CLK_EN_Pos                    3
#define  R23B_INV_CLK_EN_Msk                    (0x01 << R23B_INV_CLK_EN_Pos)

#define  R23B_DS_SHIFT_Pos                      4
#define  R23B_DS_SHIFT_Msk                      (0x01 << R23B_DS_SHIFT_Pos)

#define  R23B_DIV2_EN_Pos                       5
#define  R23B_DIV2_EN_Msk                       (0x01 << R23B_DIV2_EN_Pos)

#define  R23B_CLK_EN_Pos                        6
#define  R23B_CLK_EN_Msk                        (0x01 << R23B_CLK_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R23C                                   0x23c

#define  R23C_IB_OB_DELAY_SEL_Pos               0
#define  R23C_IB_OB_DELAY_SEL_Msk               (0x01 << R23C_IB_OB_DELAY_SEL_Pos)

#define  R23C_PHASE_ADJ_Pos                     1
#define  R23C_PHASE_ADJ_Msk                     (0x01 << R23C_PHASE_ADJ_Pos)

//--------------------------------------------------------------------------------------------------
#define   R23D_DELAY_LEN                         0x23d
#define   R23D                                   0x23d

#define  R23D_DELAY_LEN_Pos                     0
#define  R23D_DELAY_LEN_Msk                     (0x1f << R23D_DELAY_LEN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R23E                                   0x23e

#define  R23E_NDIV_OVRD_Pos                     0
#define  R23E_NDIV_OVRD_Msk                     (0x3f << R23E_NDIV_OVRD_Pos)

#define  R23E_NDIV_OVRD_SEL_Pos                 7
#define  R23E_NDIV_OVRD_SEL_Msk                 (0x01 << R23E_NDIV_OVRD_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R23F                                   0x23f

#define  R23F_VCO_CODE_MANUL_TX_Pos             0
#define  R23F_VCO_CODE_MANUL_TX_Msk             (0x3f << R23F_VCO_CODE_MANUL_TX_Pos)

#define  R23F_VCO_CODE_MANUL_RX_H_Pos           6
#define  R23F_VCO_CODE_MANUL_RX_H_Msk           (0x03 << R23F_VCO_CODE_MANUL_RX_H_Pos)

//--------------------------------------------------------------------------------------------------
#define   R240                                   0x240

#define  R240_VCO_NO_DLY_Pos                    0
#define  R240_VCO_NO_DLY_Msk                    (0x01 << R240_VCO_NO_DLY_Pos)

#define  R240_VCO_DLY_SEL_Pos                   1
#define  R240_VCO_DLY_SEL_Msk                   (0x03 << R240_VCO_DLY_SEL_Pos)

#define  R240_VCO_CODE_MANUL_SEL_Pos            3
#define  R240_VCO_CODE_MANUL_SEL_Msk            (0x01 << R240_VCO_CODE_MANUL_SEL_Pos)

#define  R240_VCO_CODE_MANUL_RX_Pos             4
#define  R240_VCO_CODE_MANUL_RX_Msk             (0x0f << R240_VCO_CODE_MANUL_RX_Pos)

//--------------------------------------------------------------------------------------------------
#define   R241                                   0x241

#define  R241_CAL_DONE_SEL_Pos                  0
#define  R241_CAL_DONE_SEL_Msk                  (0x01 << R241_CAL_DONE_SEL_Pos)

#define  R241_PLL_RSTN_SEL_Pos                  1
#define  R241_PLL_RSTN_SEL_Msk                  (0x01 << R241_PLL_RSTN_SEL_Pos)

#define  R241_CHIRP_DATA_SEL_Pos                2
#define  R241_CHIRP_DATA_SEL_Msk                (0x01 << R241_CHIRP_DATA_SEL_Pos)

#define  R241_PCLK_TEST_SEL_Pos                 3
#define  R241_PCLK_TEST_SEL_Msk                 (0x01 << R241_PCLK_TEST_SEL_Pos)

#define  R241_DA_IN_SEL_Pos                     4
#define  R241_DA_IN_SEL_Msk                     (0x01 << R241_DA_IN_SEL_Pos)

#define  R241_FRACN_OUT_SEL_Pos                 5
#define  R241_FRACN_OUT_SEL_Msk                 (0x01 << R241_FRACN_OUT_SEL_Pos)

#define  R241_PLL_RSTN_FPGA_Pos                 6
#define  R241_PLL_RSTN_FPGA_Msk                 (0x01 << R241_PLL_RSTN_FPGA_Pos)

#define  R241_CAL_DONE_FPGA_Pos                 7
#define  R241_CAL_DONE_FPGA_Msk                 (0x01 << R241_CAL_DONE_FPGA_Pos)

//--------------------------------------------------------------------------------------------------
#define  R242_CH_INT_NUM_SPI                    0x242

#define   R242_CH_INT_NUM_SPI_L                  0x242
#define   R242                                   0x242

#define   R243_CH_INT_NUM_SPI_H                  0x243
#define   R243                                   0x243

//--------------------------------------------------------------------------------------------------
#define   R244_CH_FRA_NUM_SPI_L1                 0x244
#define   R244                                   0x244

//--------------------------------------------------------------------------------------------------
#define   R245_CH_FRA_NUM_SPI_L2                 0x245
#define   R245                                   0x245

//--------------------------------------------------------------------------------------------------
#define   R246                                   0x246

#define  R246_CH_FRA_NUM_SPI_H_Pos              0
#define  R246_CH_FRA_NUM_SPI_H_Msk              (0x7f << R246_CH_FRA_NUM_SPI_H_Pos)

#define  R246_CHAN_DEC_MUX_Pos                  7
#define  R246_CHAN_DEC_MUX_Msk                  (0x01 << R246_CHAN_DEC_MUX_Pos)

//--------------------------------------------------------------------------------------------------
#define   R247                                   0x247

#define  R247_DCDC_EN_Pos                       2
#define  R247_DCDC_EN_Msk                       (0x01 << R247_DCDC_EN_Pos)

#define  R247_BUCK_CAL_LOOP_DELAY_Pos           3
#define  R247_BUCK_CAL_LOOP_DELAY_Msk           (0x03 << R247_BUCK_CAL_LOOP_DELAY_Pos)

#define  R247_BUCK_CAL_START_DELAY_Pos          5
#define  R247_BUCK_CAL_START_DELAY_Msk          (0x03 << R247_BUCK_CAL_START_DELAY_Pos)

#define  R247_DCDC_SOFT_EN_Pos                  7
#define  R247_DCDC_SOFT_EN_Msk                  (0x01 << R247_DCDC_SOFT_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R248_REG_DIG2_TX_DLY                   0x248
#define   R248                                   0x248

//--------------------------------------------------------------------------------------------------
#define   R249_AGC_GAIN_GRID                     0x249
#define   R249                                   0x249

//--------------------------------------------------------------------------------------------------
#define  R24A_AGC_SET                           0x24a

#define   R24A_AGC_SET_L                         0x24a
#define   R24A                                   0x24a

#define   R24B_AGC_SET_H                         0x24b
#define   R24B                                   0x24b

//--------------------------------------------------------------------------------------------------
#define   R24C_REG_PR_MATCH_LOCK_AGC_TH          0x24c
#define   R24C                                   0x24c

//--------------------------------------------------------------------------------------------------
#define   R24D_REG_TH_OFST                       0x24d
#define   R24D                                   0x24d

//--------------------------------------------------------------------------------------------------
#define   R24E_DECIMAT_1ST_MANU_NUM_L1           0x24e
#define   R24E                                   0x24e

//--------------------------------------------------------------------------------------------------
#define   R24F_DECIMAT_1ST_MANU_NUM_L2           0x24f
#define   R24F                                   0x24f

//--------------------------------------------------------------------------------------------------
#define   R250_DECIMAT_LAST_MANU_NUM_L1          0x250
#define   R250                                   0x250

//--------------------------------------------------------------------------------------------------
#define   R251_DECIMAT_LAST_MANU_NUM_L2          0x251
#define   R251                                   0x251

//--------------------------------------------------------------------------------------------------
#define   R252                                   0x252

#define  R252_DECIMAT_LAST_MANU_NUM_H_Pos       0
#define  R252_DECIMAT_LAST_MANU_NUM_H_Msk       (0x07 << R252_DECIMAT_LAST_MANU_NUM_H_Pos)

#define  R252_DECIMAT_1ST_MANU_NUM_H_Pos        3
#define  R252_DECIMAT_1ST_MANU_NUM_H_Msk        (0x07 << R252_DECIMAT_1ST_MANU_NUM_H_Pos)

#define  R252_DECIMAT_LAST_MANU_EN_Pos          6
#define  R252_DECIMAT_LAST_MANU_EN_Msk          (0x01 << R252_DECIMAT_LAST_MANU_EN_Pos)

#define  R252_DECIMAT_1ST_MANU_EN_Pos           7
#define  R252_DECIMAT_1ST_MANU_EN_Msk           (0x01 << R252_DECIMAT_1ST_MANU_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R253_DCDC_IMAX_CAL_CODE                0x253
#define   R253                                   0x253

#define  R253_DCDC_IMAX_CAL_CODE_Pos            0
#define  R253_DCDC_IMAX_CAL_CODE_Msk            (0x1f << R253_DCDC_IMAX_CAL_CODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R254_DCDC_ZERO_CAL_CODE                0x254
#define   R254                                   0x254

#define  R254_DCDC_ZERO_CAL_CODE_Pos            0
#define  R254_DCDC_ZERO_CAL_CODE_Msk            (0x1f << R254_DCDC_ZERO_CAL_CODE_Pos)

//--------------------------------------------------------------------------------------------------
#define  R286_REG_FLTR_5TH_COEF0                0x286

#define   R286_REG_FLTR_5TH_COEF0_L              0x286
#define   R286                                   0x286

#define   R287_REG_FLTR_5TH_COEF0_H              0x287
#define   R287                                   0x287

//--------------------------------------------------------------------------------------------------
#define  R288_REG_FLTR_5TH_COEF1                0x288

#define   R288_REG_FLTR_5TH_COEF1_L              0x288
#define   R288                                   0x288

#define   R289_REG_FLTR_5TH_COEF1_H              0x289
#define   R289                                   0x289

//--------------------------------------------------------------------------------------------------
#define  R28A_REG_FLTR_5TH_COEF2                0x28a

#define   R28A_REG_FLTR_5TH_COEF2_L              0x28a
#define   R28A                                   0x28a

#define   R28B_REG_FLTR_5TH_COEF2_H              0x28b
#define   R28B                                   0x28b

//--------------------------------------------------------------------------------------------------
#define  R28C_REG_FLTR_5TH_COEF3                0x28c

#define   R28C_REG_FLTR_5TH_COEF3_L              0x28c
#define   R28C                                   0x28c

#define   R28D_REG_FLTR_5TH_COEF3_H              0x28d
#define   R28D                                   0x28d

//--------------------------------------------------------------------------------------------------
#define  R28E_REG_FLTR_5TH_COEF4                0x28e

#define   R28E_REG_FLTR_5TH_COEF4_L              0x28e
#define   R28E                                   0x28e

#define   R28F_REG_FLTR_5TH_COEF4_H              0x28f
#define   R28F                                   0x28f

//--------------------------------------------------------------------------------------------------
#define  R290_REG_FLTR_5TH_COEF5                0x290

#define   R290_REG_FLTR_5TH_COEF5_L              0x290
#define   R290                                   0x290

#define   R291_REG_FLTR_5TH_COEF5_H              0x291
#define   R291                                   0x291

//--------------------------------------------------------------------------------------------------
#define  R292_REG_FLTR_5TH_COEF6                0x292

#define   R292_REG_FLTR_5TH_COEF6_L              0x292
#define   R292                                   0x292

#define   R293_REG_FLTR_5TH_COEF6_H              0x293
#define   R293                                   0x293

//--------------------------------------------------------------------------------------------------
#define  R294_REG_FLTR_5TH_COEF7                0x294

#define   R294_REG_FLTR_5TH_COEF7_L              0x294
#define   R294                                   0x294

#define   R295_REG_FLTR_5TH_COEF7_H              0x295
#define   R295                                   0x295

//--------------------------------------------------------------------------------------------------
#define  R296_REG_FLTR_5TH_COEF8                0x296

#define   R296_REG_FLTR_5TH_COEF8_L              0x296
#define   R296                                   0x296

#define   R297_REG_FLTR_5TH_COEF8_H              0x297
#define   R297                                   0x297

//--------------------------------------------------------------------------------------------------
#define  R298_REG_FLTR_5TH_COEF9                0x298

#define   R298_REG_FLTR_5TH_COEF9_L              0x298
#define   R298                                   0x298

#define   R299_REG_FLTR_5TH_COEF9_H              0x299
#define   R299                                   0x299

//--------------------------------------------------------------------------------------------------
#define  R29A_REG_FLTR_5TH_COEF10               0x29a

#define   R29A_REG_FLTR_5TH_COEF10_L             0x29a
#define   R29A                                   0x29a

#define   R29B_REG_FLTR_5TH_COEF10_H             0x29b
#define   R29B                                   0x29b

//--------------------------------------------------------------------------------------------------
#define  R29C_REG_FLTR_5TH_COEF11               0x29c

#define   R29C_REG_FLTR_5TH_COEF11_L             0x29c
#define   R29C                                   0x29c

#define   R29D_REG_FLTR_5TH_COEF11_H             0x29d
#define   R29D                                   0x29d

//--------------------------------------------------------------------------------------------------
#define  R29E_REG_FLTR_5TH_COEF12               0x29e

#define   R29E_REG_FLTR_5TH_COEF12_L             0x29e
#define   R29E                                   0x29e

#define   R29F_REG_FLTR_5TH_COEF12_H             0x29f
#define   R29F                                   0x29f

//--------------------------------------------------------------------------------------------------
#define  R2A0_REG_FLTR_5TH_COEF13               0x2a0

#define   R2A0_REG_FLTR_5TH_COEF13_L             0x2a0
#define   R2A0                                   0x2a0

#define   R2A1_REG_FLTR_5TH_COEF13_H             0x2a1
#define   R2A1                                   0x2a1

//--------------------------------------------------------------------------------------------------
#define  R2A2_REG_FLTR_5TH_COEF14               0x2a2

#define   R2A2_REG_FLTR_5TH_COEF14_L             0x2a2
#define   R2A2                                   0x2a2

#define   R2A3_REG_FLTR_5TH_COEF14_H             0x2a3
#define   R2A3                                   0x2a3

//--------------------------------------------------------------------------------------------------
#define  R2A4_REG_FLTR_5TH_COEF15               0x2a4

#define   R2A4_REG_FLTR_5TH_COEF15_L             0x2a4
#define   R2A4                                   0x2a4

#define   R2A5_REG_FLTR_5TH_COEF15_H             0x2a5
#define   R2A5                                   0x2a5

//--------------------------------------------------------------------------------------------------
#define  R2A6_REG_FLTR_5TH_COEF16               0x2a6

#define   R2A6_REG_FLTR_5TH_COEF16_L             0x2a6
#define   R2A6                                   0x2a6

#define   R2A7_REG_FLTR_5TH_COEF16_H             0x2a7
#define   R2A7                                   0x2a7

//--------------------------------------------------------------------------------------------------
#define  R2A8_REG_FLTR_5TH_COEF17               0x2a8

#define   R2A8_REG_FLTR_5TH_COEF17_L             0x2a8
#define   R2A8                                   0x2a8

#define   R2A9_REG_FLTR_5TH_COEF17_H             0x2a9
#define   R2A9                                   0x2a9

//--------------------------------------------------------------------------------------------------
#define  R2AA_REG_FLTR_5TH_COEF18               0x2aa

#define   R2AA_REG_FLTR_5TH_COEF18_L             0x2aa
#define   R2AA                                   0x2aa

#define   R2AB_REG_FLTR_5TH_COEF18_H             0x2ab
#define   R2AB                                   0x2ab

//--------------------------------------------------------------------------------------------------
#define  R2AC_REG_FLTR_5TH_COEF19               0x2ac

#define   R2AC_REG_FLTR_5TH_COEF19_L             0x2ac
#define   R2AC                                   0x2ac

#define   R2AD_REG_FLTR_5TH_COEF19_H             0x2ad
#define   R2AD                                   0x2ad

//--------------------------------------------------------------------------------------------------
#define  R2AE_REG_FLTR_5TH_COEF20               0x2ae

#define   R2AE_REG_FLTR_5TH_COEF20_L             0x2ae
#define   R2AE                                   0x2ae

#define   R2AF_REG_FLTR_5TH_COEF20_H             0x2af
#define   R2AF                                   0x2af

//--------------------------------------------------------------------------------------------------
#define  R2B0_REG_FLTR_5TH_COEF21               0x2b0

#define   R2B0_REG_FLTR_5TH_COEF21_L             0x2b0
#define   R2B0                                   0x2b0

#define   R2B1_REG_FLTR_5TH_COEF21_H             0x2b1
#define   R2B1                                   0x2b1

//--------------------------------------------------------------------------------------------------
#define   R2B2                                   0x2b2

#define  R2B2_PMU_IPOLY_TRIM_Pos                0
#define  R2B2_PMU_IPOLY_TRIM_Msk                (0x07 << R2B2_PMU_IPOLY_TRIM_Pos)

#define  R2B2_VDD_PA_TRIM_Pos                   3
#define  R2B2_VDD_PA_TRIM_Msk                   (0x1f << R2B2_VDD_PA_TRIM_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2B3_DCDC_IMAX_CAL                     0x2b3
#define   R2B3                                   0x2b3

#define  R2B3_DCDC_IMAX_CAL_Pos                 0
#define  R2B3_DCDC_IMAX_CAL_Msk                 (0x1f << R2B3_DCDC_IMAX_CAL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2B4_DCDC_VOUT_TRIM                    0x2b4
#define   R2B4                                   0x2b4

#define  R2B4_DCDC_VOUT_TRIM_Pos                0
#define  R2B4_DCDC_VOUT_TRIM_Msk                (0x1f << R2B4_DCDC_VOUT_TRIM_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2B5                                   0x2b5

#define  R2B5_DCDC_ZERO_CAL_Pos                 0
#define  R2B5_DCDC_ZERO_CAL_Msk                 (0x1f << R2B5_DCDC_ZERO_CAL_Pos)

#define  R2B5_PMU_PTAT_VTRIM_Pos                5
#define  R2B5_PMU_PTAT_VTRIM_Msk                (0x07 << R2B5_PMU_PTAT_VTRIM_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2B6                                   0x2b6

#define  R2B6_VDD_RFE_TRIM_Pos                  0
#define  R2B6_VDD_RFE_TRIM_Msk                  (0x0f << R2B6_VDD_RFE_TRIM_Pos)

#define  R2B6_VDD_RFE_TRIM_TX_Pos               4
#define  R2B6_VDD_RFE_TRIM_TX_Msk               (0x0f << R2B6_VDD_RFE_TRIM_TX_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2B7                                   0x2b7

#define  R2B7_VDD_IF_TRIM_Pos                   0
#define  R2B7_VDD_IF_TRIM_Msk                   (0x0f << R2B7_VDD_IF_TRIM_Pos)

#define  R2B7_VDD_FSYN_TRIM_Pos                 4
#define  R2B7_VDD_FSYN_TRIM_Msk                 (0x0f << R2B7_VDD_FSYN_TRIM_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2B8                                   0x2b8

#define  R2B8_VDD_VCO_TRIM_Pos                  0
#define  R2B8_VDD_VCO_TRIM_Msk                  (0x0f << R2B8_VDD_VCO_TRIM_Pos)

#define  R2B8_VDD_ADC_TRIM_Pos                  4
#define  R2B8_VDD_ADC_TRIM_Msk                  (0x0f << R2B8_VDD_ADC_TRIM_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2B9                                   0x2b9

#define  R2B9_LDO_HP_TRIM_Pos                   0
#define  R2B9_LDO_HP_TRIM_Msk                   (0x0f << R2B9_LDO_HP_TRIM_Pos)

#define  R2B9_VDD_LO_TRIM_Pos                   4
#define  R2B9_VDD_LO_TRIM_Msk                   (0x0f << R2B9_VDD_LO_TRIM_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2BA_RCH_FREQ_FINE                     0x2ba
#define   R2BA                                   0x2ba

//--------------------------------------------------------------------------------------------------
#define   R2BB                                   0x2bb

#define  R2BB_PLL_LPF_VSEL_Pos                  0
#define  R2BB_PLL_LPF_VSEL_Msk                  (0x03 << R2BB_PLL_LPF_VSEL_Pos)

#define  R2BB_EN_RX_TIA_Pos                     2
#define  R2BB_EN_RX_TIA_Msk                     (0x01 << R2BB_EN_RX_TIA_Pos)

#define  R2BB_EN_RX_ADC_TIA_Pos                 3
#define  R2BB_EN_RX_ADC_TIA_Msk                 (0x01 << R2BB_EN_RX_ADC_TIA_Pos)

#define  R2BB_RX_ADC_DAC_RSTSEL_Pos             4
#define  R2BB_RX_ADC_DAC_RSTSEL_Msk             (0x01 << R2BB_RX_ADC_DAC_RSTSEL_Pos)

#define  R2BB_RX_ADC_OUTSEL_Pos                 7
#define  R2BB_RX_ADC_OUTSEL_Msk                 (0x01 << R2BB_RX_ADC_OUTSEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2BC                                   0x2bc

#define  R2BC_PLL_LPF_C1_Pos                    0
#define  R2BC_PLL_LPF_C1_Msk                    (0x07 << R2BC_PLL_LPF_C1_Pos)

#define  R2BC_EN_PLL_VCO_BUF_Pos                3
#define  R2BC_EN_PLL_VCO_BUF_Msk                (0x01 << R2BC_EN_PLL_VCO_BUF_Pos)

#define  R2BC_EN_PLL_CP_FV_Pos                  5
#define  R2BC_EN_PLL_CP_FV_Msk                  (0x01 << R2BC_EN_PLL_CP_FV_Pos)

#define  R2BC_PLL_PFD_DELAY_Pos                 6
#define  R2BC_PLL_PFD_DELAY_Msk                 (0x03 << R2BC_PLL_PFD_DELAY_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2BD                                   0x2bd

#define  R2BD_PLL_BYP_FT_Pos                    0
#define  R2BD_PLL_BYP_FT_Msk                    (0x01 << R2BD_PLL_BYP_FT_Pos)

#define  R2BD_PLL_LPF_R1_Pos                    1
#define  R2BD_PLL_LPF_R1_Msk                    (0x03 << R2BD_PLL_LPF_R1_Pos)

#define  R2BD_PLL_LPF_C3_Pos                    3
#define  R2BD_PLL_LPF_C3_Msk                    (0x03 << R2BD_PLL_LPF_C3_Pos)

#define  R2BD_PLL_LPF_C2_Pos                    5
#define  R2BD_PLL_LPF_C2_Msk                    (0x07 << R2BD_PLL_LPF_C2_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2BE                                   0x2be

#define  R2BE_PLL_VCO_ISEL_Pos                  0
#define  R2BE_PLL_VCO_ISEL_Msk                  (0x0f << R2BE_PLL_VCO_ISEL_Pos)

#define  R2BE_PLL_LPF_R3_Pos                    4
#define  R2BE_PLL_LPF_R3_Msk                    (0x03 << R2BE_PLL_LPF_R3_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2C1                                   0x2c1

#define  R2C1_PLL_CALDIV_Pos                    0
#define  R2C1_PLL_CALDIV_Msk                    (0x03 << R2C1_PLL_CALDIV_Pos)

#define  R2C1_PLL_FBDIV_TSTEN_Pos               3
#define  R2C1_PLL_FBDIV_TSTEN_Msk               (0x01 << R2C1_PLL_FBDIV_TSTEN_Pos)

#define  R2C1_XTH_HYS_EN_Pos                    5
#define  R2C1_XTH_HYS_EN_Msk                    (0x03 << R2C1_XTH_HYS_EN_Pos)

#define  R2C1_PLL_TWO_POINT_VCTX_ENN_Pos        7
#define  R2C1_PLL_TWO_POINT_VCTX_ENN_Msk        (0x01 << R2C1_PLL_TWO_POINT_VCTX_ENN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2C2                                   0x2c2

#define  R2C2_DAC_CLKINV_Pos                    0
#define  R2C2_DAC_CLKINV_Msk                    (0x01 << R2C2_DAC_CLKINV_Pos)

#define  R2C2_DAC_SG_SEL_Pos                    1
#define  R2C2_DAC_SG_SEL_Msk                    (0x01 << R2C2_DAC_SG_SEL_Pos)

#define  R2C2_DAC_SEL_SW_Pos                    2
#define  R2C2_DAC_SEL_SW_Msk                    (0x03 << R2C2_DAC_SEL_SW_Pos)

#define  R2C2_DAC_TST_SEL_Pos                   4
#define  R2C2_DAC_TST_SEL_Msk                   (0x01 << R2C2_DAC_TST_SEL_Pos)

#define  R2C2_TST_BUF_BYP_Pos                   6
#define  R2C2_TST_BUF_BYP_Msk                   (0x01 << R2C2_TST_BUF_BYP_Pos)

#define  R2C2_PLL_CALTST_EN_Pos                 7
#define  R2C2_PLL_CALTST_EN_Msk                 (0x01 << R2C2_PLL_CALTST_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2C3                                   0x2c3

#define  R2C3_RCH_XTH_TST_SEL_Pos               0
#define  R2C3_RCH_XTH_TST_SEL_Msk               (0x01 << R2C3_RCH_XTH_TST_SEL_Pos)

#define  R2C3_RX_TIA_DCOC_FAST_Pos              1
#define  R2C3_RX_TIA_DCOC_FAST_Msk              (0x01 << R2C3_RX_TIA_DCOC_FAST_Pos)

#define  R2C3_RX_TIA_DCOC_BWSEL_Pos             2
#define  R2C3_RX_TIA_DCOC_BWSEL_Msk             (0x01 << R2C3_RX_TIA_DCOC_BWSEL_Pos)

#define  R2C3_RX_TIA_DCOC_ENABLE_Pos            3
#define  R2C3_RX_TIA_DCOC_ENABLE_Msk            (0x01 << R2C3_RX_TIA_DCOC_ENABLE_Pos)

#define  R2C3_EN_LO_MUX_Pos                     7
#define  R2C3_EN_LO_MUX_Msk                     (0x01 << R2C3_EN_LO_MUX_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2C4                                   0x2c4

#define  R2C4_TXPA_900M_BUF_Pos                 0
#define  R2C4_TXPA_900M_BUF_Msk                 (0x01 << R2C4_TXPA_900M_BUF_Pos)

#define  R2C4_TRX_COMATCH_EN_Pos                1
#define  R2C4_TRX_COMATCH_EN_Msk                (0x01 << R2C4_TRX_COMATCH_EN_Pos)

#define  R2C4_DCDC_RESSEL_Pos                   2
#define  R2C4_DCDC_RESSEL_Msk                   (0x07 << R2C4_DCDC_RESSEL_Pos)

#define  R2C4_DCDC_BUFSEL_Pos                   5
#define  R2C4_DCDC_BUFSEL_Msk                   (0x07 << R2C4_DCDC_BUFSEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2C5                                   0x2c5

#define  R2C5_DCDC_LIMIT_EN_Pos                 0
#define  R2C5_DCDC_LIMIT_EN_Msk                 (0x01 << R2C5_DCDC_LIMIT_EN_Pos)

#define  R2C5_DCDC_MODE_SEL_Pos                 1
#define  R2C5_DCDC_MODE_SEL_Msk                 (0x01 << R2C5_DCDC_MODE_SEL_Pos)

#define  R2C5_DCDC_SSEN_Pos                     2
#define  R2C5_DCDC_SSEN_Msk                     (0x01 << R2C5_DCDC_SSEN_Pos)

#define  R2C5_DCDC_IMAX_Pos                     3
#define  R2C5_DCDC_IMAX_Msk                     (0x07 << R2C5_DCDC_IMAX_Pos)

#define  R2C5_DCDC_CAL_EN_Pos                   6
#define  R2C5_DCDC_CAL_EN_Msk                   (0x03 << R2C5_DCDC_CAL_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2C6                                   0x2c6

#define  R2C6_XTH_DEGLITCH_EN_Pos               0
#define  R2C6_XTH_DEGLITCH_EN_Msk               (0x01 << R2C6_XTH_DEGLITCH_EN_Pos)

#define  R2C6_XTH_TST_EN_Pos                    2
#define  R2C6_XTH_TST_EN_Msk                    (0x01 << R2C6_XTH_TST_EN_Pos)

#define  R2C6_VDD_PA_BYP_Pos                    3
#define  R2C6_VDD_PA_BYP_Msk                    (0x01 << R2C6_VDD_PA_BYP_Pos)

#define  R2C6_RX_TIA_BWSEL_Pos                  4
#define  R2C6_RX_TIA_BWSEL_Msk                  (0x03 << R2C6_RX_TIA_BWSEL_Pos)

#define  R2C6_LDO_HP_SEL_Pos                    6
#define  R2C6_LDO_HP_SEL_Msk                    (0x01 << R2C6_LDO_HP_SEL_Pos)

#define  R2C6_PA_LP_SEL_Pos                     7
#define  R2C6_PA_LP_SEL_Msk                     (0x01 << R2C6_PA_LP_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2C7                                   0x2c7

#define  R2C7_XTH_STARTUP_FAST_Pos              0
#define  R2C7_XTH_STARTUP_FAST_Msk              (0x01 << R2C7_XTH_STARTUP_FAST_Pos)

#define  R2C7_XTH_RDY_SEL_Pos                   1
#define  R2C7_XTH_RDY_SEL_Msk                   (0x01 << R2C7_XTH_RDY_SEL_Pos)

#define  R2C7_XTH_CAP_TRIM_Pos                  2
#define  R2C7_XTH_CAP_TRIM_Msk                  (0x3f << R2C7_XTH_CAP_TRIM_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2C8                                   0x2c8

#define  R2C8_TST_DCDC_Pos                      0
#define  R2C8_TST_DCDC_Msk                      (0x01 << R2C8_TST_DCDC_Pos)

#define  R2C8_TST_LPF_Pos                       1
#define  R2C8_TST_LPF_Msk                       (0x01 << R2C8_TST_LPF_Pos)

#define  R2C8_TST_RX_EN_Pos                     2
#define  R2C8_TST_RX_EN_Msk                     (0x01 << R2C8_TST_RX_EN_Pos)

#define  R2C8_TST_LDO_Pos                       3
#define  R2C8_TST_LDO_Msk                       (0x01 << R2C8_TST_LDO_Pos)

#define  R2C8_XTH_RES_Pos                       4
#define  R2C8_XTH_RES_Msk                       (0x01 << R2C8_XTH_RES_Pos)

#define  R2C8_XTH_FAST_DLY_Pos                  5
#define  R2C8_XTH_FAST_DLY_Msk                  (0x01 << R2C8_XTH_FAST_DLY_Pos)

#define  R2C8_XTH_FB_EN_Pos                     6
#define  R2C8_XTH_FB_EN_Msk                     (0x01 << R2C8_XTH_FB_EN_Pos)

#define  R2C8_XTH_AMP_SEL_Pos                   7
#define  R2C8_XTH_AMP_SEL_Msk                   (0x01 << R2C8_XTH_AMP_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2C9                                   0x2c9

#define  R2C9_TST_EN_DFT_V_Pos                  0
#define  R2C9_TST_EN_DFT_V_Msk                  (0x01 << R2C9_TST_EN_DFT_V_Pos)

#define  R2C9_TST_EN_DFT_I_Pos                  1
#define  R2C9_TST_EN_DFT_I_Msk                  (0x01 << R2C9_TST_EN_DFT_I_Pos)

#define  R2C9_TST_V_REG_Pos                     2
#define  R2C9_TST_V_REG_Msk                     (0x0f << R2C9_TST_V_REG_Pos)

#define  R2C9_TST_I_REG_Pos                     6
#define  R2C9_TST_I_REG_Msk                     (0x01 << R2C9_TST_I_REG_Pos)

#define  R2C9_TST_DAC_Pos                       7
#define  R2C9_TST_DAC_Msk                       (0x01 << R2C9_TST_DAC_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2CA                                   0x2ca

#define  R2CA_EN_RX_MIX_Pos                     0
#define  R2CA_EN_RX_MIX_Msk                     (0x01 << R2CA_EN_RX_MIX_Pos)

#define  R2CA_EN_RX_LNA_Pos                     1
#define  R2CA_EN_RX_LNA_Msk                     (0x01 << R2CA_EN_RX_LNA_Pos)

#define  R2CA_EN_LDO_PA_Pos                     2
#define  R2CA_EN_LDO_PA_Msk                     (0x01 << R2CA_EN_LDO_PA_Pos)

#define  R2CA_TST_CLK_REG_Pos                   3
#define  R2CA_TST_CLK_REG_Msk                   (0x07 << R2CA_TST_CLK_REG_Pos)

#define  R2CA_TST_EN_DFT_CLK_Pos                6
#define  R2CA_TST_EN_DFT_CLK_Msk                (0x01 << R2CA_TST_EN_DFT_CLK_Pos)

#define  R2CA_TST_EN_BUF_Pos                    7
#define  R2CA_TST_EN_BUF_Msk                    (0x01 << R2CA_TST_EN_BUF_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2CB                                   0x2cb

#define  R2CB_EN_TX_DAC_Pos                     0
#define  R2CB_EN_TX_DAC_Msk                     (0x01 << R2CB_EN_TX_DAC_Pos)

#define  R2CB_EN_PLL_VCO_Pos                    1
#define  R2CB_EN_PLL_VCO_Msk                    (0x01 << R2CB_EN_PLL_VCO_Pos)

#define  R2CB_EN_PLL_LPF_VCDN_Pos               2
#define  R2CB_EN_PLL_LPF_VCDN_Msk               (0x01 << R2CB_EN_PLL_LPF_VCDN_Pos)

#define  R2CB_EN_PLL_LPF_Pos                    3
#define  R2CB_EN_PLL_LPF_Msk                    (0x01 << R2CB_EN_PLL_LPF_Pos)

#define  R2CB_EN_PLL_CPSHIFT_Pos                4
#define  R2CB_EN_PLL_CPSHIFT_Msk                (0x01 << R2CB_EN_PLL_CPSHIFT_Pos)

#define  R2CB_EN_PLL_CP_Pos                     5
#define  R2CB_EN_PLL_CP_Msk                     (0x01 << R2CB_EN_PLL_CP_Pos)

#define  R2CB_EN_PLL_PFD_Pos                    6
#define  R2CB_EN_PLL_PFD_Msk                    (0x01 << R2CB_EN_PLL_PFD_Pos)

#define  R2CB_EN_RX_ADC_Pos                     7
#define  R2CB_EN_RX_ADC_Msk                     (0x01 << R2CB_EN_RX_ADC_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2CC                                   0x2cc

#define  R2CC_RCH_RDY_TRIM_Pos                  0
#define  R2CC_RCH_RDY_TRIM_Msk                  (0x03 << R2CC_RCH_RDY_TRIM_Pos)

#define  R2CC_EN_RCH_TST_Pos                    2
#define  R2CC_EN_RCH_TST_Msk                    (0x01 << R2CC_EN_RCH_TST_Pos)

#define  R2CC_EN_RCL_TST_Pos                    3
#define  R2CC_EN_RCL_TST_Msk                    (0x01 << R2CC_EN_RCL_TST_Pos)

#define  R2CC_EN_LVR_TST_Pos                    4
#define  R2CC_EN_LVR_TST_Msk                    (0x01 << R2CC_EN_LVR_TST_Pos)

#define  R2CC_EN_BOD_TST_Pos                    5
#define  R2CC_EN_BOD_TST_Msk                    (0x01 << R2CC_EN_BOD_TST_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2CD                                   0x2cd

#define  R2CD_EN_XTL_TST_Pos                    7
#define  R2CD_EN_XTL_TST_Msk                    (0x01 << R2CD_EN_XTL_TST_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2CE                                   0x2ce

#define  R2CE_XTH_CLKRDY_OUT_Pos                4
#define  R2CE_XTH_CLKRDY_OUT_Msk                (0x01 << R2CE_XTH_CLKRDY_OUT_Pos)

#define  R2CE_RCH_RDY_Pos                       5
#define  R2CE_RCH_RDY_Msk                       (0x01 << R2CE_RCH_RDY_Pos)

#define  R2CE_DCDC_CMP_OUT_Pos                  6
#define  R2CE_DCDC_CMP_OUT_Msk                  (0x01 << R2CE_DCDC_CMP_OUT_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2CF                                   0x2cf

#define  R2CF_RCCAL_CAPTUNE_Pos                 0
#define  R2CF_RCCAL_CAPTUNE_Msk                 (0x3f << R2CF_RCCAL_CAPTUNE_Pos)

#define  R2CF_RCCAL_DONE_Pos                    6
#define  R2CF_RCCAL_DONE_Msk                    (0x01 << R2CF_RCCAL_DONE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2D0                                   0x2d0

#define  R2D0_RX_TIA_CAPTUNE_Pos                1
#define  R2D0_RX_TIA_CAPTUNE_Msk                (0x7f << R2D0_RX_TIA_CAPTUNE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2D1                                   0x2d1

#define  R2D1_RX_ADC_QUAN_VTRIM_Pos             0
#define  R2D1_RX_ADC_QUAN_VTRIM_Msk             (0x07 << R2D1_RX_ADC_QUAN_VTRIM_Pos)

#define  R2D1_RX_TIA_IBIAS_Pos                  3
#define  R2D1_RX_TIA_IBIAS_Msk                  (0x07 << R2D1_RX_TIA_IBIAS_Pos)

#define  R2D1_RX_MIX_VCM_Pos                    6
#define  R2D1_RX_MIX_VCM_Msk                    (0x03 << R2D1_RX_MIX_VCM_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2D2                                   0x2d2

#define  R2D2_PLL_CP_NSHIFT_Pos                 0
#define  R2D2_PLL_CP_NSHIFT_Msk                 (0x07 << R2D2_PLL_CP_NSHIFT_Pos)

#define  R2D2_PLL_VCO_FCSEL_Pos                 3
#define  R2D2_PLL_VCO_FCSEL_Msk                 (0x07 << R2D2_PLL_VCO_FCSEL_Pos)

#define  R2D2_RX_ADC_IBSEL_Pos                  6
#define  R2D2_RX_ADC_IBSEL_Msk                  (0x03 << R2D2_RX_ADC_IBSEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2D3                                   0x2d3

#define  R2D3_PLL_CP_PSHIFT_Pos                 0
#define  R2D3_PLL_CP_PSHIFT_Msk                 (0x07 << R2D3_PLL_CP_PSHIFT_Pos)

#define  R2D3_PLL_CP_ISEL_Pos                   3
#define  R2D3_PLL_CP_ISEL_Msk                   (0x0f << R2D3_PLL_CP_ISEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2D4                                   0x2d4

#define  R2D4_PLL_VCO_VD_SW_Pos                 0
#define  R2D4_PLL_VCO_VD_SW_Msk                 (0x03 << R2D4_PLL_VCO_VD_SW_Pos)

#define  R2D4_PLL_VCO_IPTATSEL_Pos              2
#define  R2D4_PLL_VCO_IPTATSEL_Msk              (0x03 << R2D4_PLL_VCO_IPTATSEL_Pos)

#define  R2D4_PLL_VCO_IBGSEL_Pos                4
#define  R2D4_PLL_VCO_IBGSEL_Msk                (0x03 << R2D4_PLL_VCO_IBGSEL_Pos)

#define  R2D4_PMU_PTAT_TEMPTRIM_Pos             6
#define  R2D4_PMU_PTAT_TEMPTRIM_Msk             (0x03 << R2D4_PMU_PTAT_TEMPTRIM_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2D5                                   0x2d5

#define  R2D5_PLL_VCO_BUF_BIASP_Pos             0
#define  R2D5_PLL_VCO_BUF_BIASP_Msk             (0x07 << R2D5_PLL_VCO_BUF_BIASP_Pos)

#define  R2D5_PLL_VCO_BUF_BIASN_Pos             3
#define  R2D5_PLL_VCO_BUF_BIASN_Msk             (0x07 << R2D5_PLL_VCO_BUF_BIASN_Pos)

#define  R2D5_XTH_ICORE_SEL_Pos                 6
#define  R2D5_XTH_ICORE_SEL_Msk                 (0x03 << R2D5_XTH_ICORE_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2D6                                   0x2d6

#define  R2D6_DAC_VREF_SEL_Pos                  0
#define  R2D6_DAC_VREF_SEL_Msk                  (0x07 << R2D6_DAC_VREF_SEL_Pos)

#define  R2D6_PA_DCC_SEL_Pos                    6
#define  R2D6_PA_DCC_SEL_Msk                    (0x03 << R2D6_PA_DCC_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2D7                                   0x2d7

#define  R2D7_PA_RAMP_RC_TRIM_Pos               1
#define  R2D7_PA_RAMP_RC_TRIM_Msk               (0x07 << R2D7_PA_RAMP_RC_TRIM_Pos)

#define  R2D7_PA_BIAS_TRIM_Pos                  4
#define  R2D7_PA_BIAS_TRIM_Msk                  (0x0f << R2D7_PA_BIAS_TRIM_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2D8                                   0x2d8

#define  R2D8_RCH_FREQ_COARSE_Pos               0
#define  R2D8_RCH_FREQ_COARSE_Msk               (0x03 << R2D8_RCH_FREQ_COARSE_Pos)

#define  R2D8_DAC_ISEL_Pos                      4
#define  R2D8_DAC_ISEL_Msk                      (0x07 << R2D8_DAC_ISEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2D9                                   0x2d9

#define  R2D9_RX_TIA_OUTCURRENT_SEL_Pos         0
#define  R2D9_RX_TIA_OUTCURRENT_SEL_Msk         (0x01 << R2D9_RX_TIA_OUTCURRENT_SEL_Pos)

#define  R2D9_RX_RCCAL_RST_Pos                  1
#define  R2D9_RX_RCCAL_RST_Msk                  (0x01 << R2D9_RX_RCCAL_RST_Pos)

#define  R2D9_RX_RCCAL_INV_Pos                  2
#define  R2D9_RX_RCCAL_INV_Msk                  (0x01 << R2D9_RX_RCCAL_INV_Pos)

#define  R2D9_EN_RX_RCCAL_Pos                   3
#define  R2D9_EN_RX_RCCAL_Msk                   (0x01 << R2D9_EN_RX_RCCAL_Pos)

#define  R2D9_RX_LNA2_ICORE_Pos                 4
#define  R2D9_RX_LNA2_ICORE_Msk                 (0x0f << R2D9_RX_LNA2_ICORE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R2DA_GPIO_CHEN                         0x2da
#define   R2DA                                   0x2da

#define  R2DA_GPIO_CHEN_Pos                     0
#define  R2DA_GPIO_CHEN_Msk                     (0x07 << R2DA_GPIO_CHEN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R2DB_RESERVED                          0x2db

#define   R2DB_RESERVED_L                        0x2db
#define   R2DB                                   0x2db

#define   R2DC_RESERVED_H                        0x2dc
#define   R2DC                                   0x2dc

//--------------------------------------------------------------------------------------------------
#define   R306_XCORR_SUM_TH                      0x306
#define   R306                                   0x306

//--------------------------------------------------------------------------------------------------
#define   R307                                   0x307

#define  R307_XCORR_SUM_DEL_TH_Pos              0
#define  R307_XCORR_SUM_DEL_TH_Msk              (0x0f << R307_XCORR_SUM_DEL_TH_Pos)

#define  R307_XCORR_SUM_FAKE_TH_Pos             4
#define  R307_XCORR_SUM_FAKE_TH_Msk             (0x0f << R307_XCORR_SUM_FAKE_TH_Pos)

//--------------------------------------------------------------------------------------------------
#define   R308                                   0x308

#define  R308_SYNC_TIMEOUT_RST_VLD_Pos          0
#define  R308_SYNC_TIMEOUT_RST_VLD_Msk          (0x01 << R308_SYNC_TIMEOUT_RST_VLD_Pos)

#define  R308_SIGN_SWITCH_IN_REG_Pos            1
#define  R308_SIGN_SWITCH_IN_REG_Msk            (0x01 << R308_SIGN_SWITCH_IN_REG_Pos)

#define  R308_REG_MANU_CFO_DIR_Pos              2
#define  R308_REG_MANU_CFO_DIR_Msk              (0x01 << R308_REG_MANU_CFO_DIR_Pos)

#define  R308_IQ_COMP_CLK_MASK_Pos              3
#define  R308_IQ_COMP_CLK_MASK_Msk              (0x01 << R308_IQ_COMP_CLK_MASK_Pos)

#define  R308_REG_MANU_FREQ_DIR_EN_Pos          4
#define  R308_REG_MANU_FREQ_DIR_EN_Msk          (0x01 << R308_REG_MANU_FREQ_DIR_EN_Pos)

#define  R308_REG_MANU_FREQ_DIR_Pos             5
#define  R308_REG_MANU_FREQ_DIR_Msk             (0x01 << R308_REG_MANU_FREQ_DIR_Pos)

#define  R308_IQ_SWITCH_IN_REG_Pos              6
#define  R308_IQ_SWITCH_IN_REG_Msk              (0x01 << R308_IQ_SWITCH_IN_REG_Pos)

#define  R308_REG_SOFT_DEC_Pos                  7
#define  R308_REG_SOFT_DEC_Msk                  (0x01 << R308_REG_SOFT_DEC_Pos)

//--------------------------------------------------------------------------------------------------
#define   R309_REG_SW_MATCH_IN_TH                0x309
#define   R309                                   0x309

//--------------------------------------------------------------------------------------------------
#define   R30A_REG_SW_MATCH_OUT_TH               0x30a
#define   R30A                                   0x30a

//--------------------------------------------------------------------------------------------------
#define   R30B                                   0x30b

#define  R30B_REG_BL_FREQ_TR_ALPH_Pos           0
#define  R30B_REG_BL_FREQ_TR_ALPH_Msk           (0x0f << R30B_REG_BL_FREQ_TR_ALPH_Pos)

#define  R30B_REG_BL_FREQ_TR_BETA_Pos           4
#define  R30B_REG_BL_FREQ_TR_BETA_Msk           (0x0f << R30B_REG_BL_FREQ_TR_BETA_Pos)

//--------------------------------------------------------------------------------------------------
#define   R30C                                   0x30c

#define  R30C_REG_BL_FSK_SYNC_KP_Pos            0
#define  R30C_REG_BL_FSK_SYNC_KP_Msk            (0x0f << R30C_REG_BL_FSK_SYNC_KP_Pos)

#define  R30C_REG_BL_FSK_SYNC_KI_Pos            4
#define  R30C_REG_BL_FSK_SYNC_KI_Msk            (0x0f << R30C_REG_BL_FSK_SYNC_KI_Pos)

//--------------------------------------------------------------------------------------------------
#define   R30D                                   0x30d

#define  R30D_REG_FD_FREQ_TR_ALPH1_Pos          0
#define  R30D_REG_FD_FREQ_TR_ALPH1_Msk          (0x0f << R30D_REG_FD_FREQ_TR_ALPH1_Pos)

#define  R30D_REG_FD_FREQ_TR_ALPH2_Pos          4
#define  R30D_REG_FD_FREQ_TR_ALPH2_Msk          (0x0f << R30D_REG_FD_FREQ_TR_ALPH2_Pos)

//--------------------------------------------------------------------------------------------------
#define   R30E                                   0x30e

#define  R30E_REG_FD_FREQ_TR_EN_Pos             0
#define  R30E_REG_FD_FREQ_TR_EN_Msk             (0x01 << R30E_REG_FD_FREQ_TR_EN_Pos)

#define  R30E_REG_SLOPE_FREQ_VLD_Pos            1
#define  R30E_REG_SLOPE_FREQ_VLD_Msk            (0x01 << R30E_REG_SLOPE_FREQ_VLD_Pos)

#define  R30E_DIRECT_BYPASS_MODE_Pos            2
#define  R30E_DIRECT_BYPASS_MODE_Msk            (0x01 << R30E_DIRECT_BYPASS_MODE_Pos)

#define  R30E_FALSE_SYNC_TIMEOUT_VLD_Pos        3
#define  R30E_FALSE_SYNC_TIMEOUT_VLD_Msk        (0x01 << R30E_FALSE_SYNC_TIMEOUT_VLD_Pos)

#define  R30E_REG_FD_SYNC_VLD_Pos               4
#define  R30E_REG_FD_SYNC_VLD_Msk               (0x01 << R30E_REG_FD_SYNC_VLD_Pos)

#define  R30E_REG_BL_FREQ_TR_EN_Pos             5
#define  R30E_REG_BL_FREQ_TR_EN_Msk             (0x01 << R30E_REG_BL_FREQ_TR_EN_Pos)

#define  R30E_REG_BL_FSK_SYNC_EN_Pos            6
#define  R30E_REG_BL_FSK_SYNC_EN_Msk            (0x01 << R30E_REG_BL_FSK_SYNC_EN_Pos)

#define  R30E_REG_FD_EQU_EN_Pos                 7
#define  R30E_REG_FD_EQU_EN_Msk                 (0x01 << R30E_REG_FD_EQU_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R30F_REG_FD_EQU_FFE_COEF1              0x30f
#define   R30F                                   0x30f

//--------------------------------------------------------------------------------------------------
#define   R310_REG_FD_EQU_FFE_COEF2              0x310
#define   R310                                   0x310

//--------------------------------------------------------------------------------------------------
#define   R311_REG_FD_EQU_FFE_COEF3              0x311
#define   R311                                   0x311

//--------------------------------------------------------------------------------------------------
#define   R312_REG_FD_EQU_DFE_COEF1              0x312
#define   R312                                   0x312

//--------------------------------------------------------------------------------------------------
#define   R313_REG_FD_EQU_DFE_COEF2              0x313
#define   R313                                   0x313

//--------------------------------------------------------------------------------------------------
#define   R314_REG_SNR_POW_TH                    0x314
#define   R314                                   0x314

//--------------------------------------------------------------------------------------------------
#define   R315                                   0x315

#define  R315_REG_SNR_POW_PARA2_Pos             0
#define  R315_REG_SNR_POW_PARA2_Msk             (0x0f << R315_REG_SNR_POW_PARA2_Pos)

#define  R315_REG_SNR_POW_PARA1_Pos             4
#define  R315_REG_SNR_POW_PARA1_Msk             (0x0f << R315_REG_SNR_POW_PARA1_Pos)

//--------------------------------------------------------------------------------------------------
#define   R316                                   0x316

#define  R316_REG_DAGC_EN_Pos                   0
#define  R316_REG_DAGC_EN_Msk                   (0x01 << R316_REG_DAGC_EN_Pos)

#define  R316_REG_DAGC_MANU_EN_Pos              1
#define  R316_REG_DAGC_MANU_EN_Msk              (0x01 << R316_REG_DAGC_MANU_EN_Pos)

#define  R316_REG_AGC_IN_MODE_Pos               2
#define  R316_REG_AGC_IN_MODE_Msk               (0x01 << R316_REG_AGC_IN_MODE_Pos)

#define  R316_REG_DC_CAL_TRIG_Pos               3
#define  R316_REG_DC_CAL_TRIG_Msk               (0x01 << R316_REG_DC_CAL_TRIG_Pos)

#define  R316_REG_SPE_PRE_SEL_Pos               4
#define  R316_REG_SPE_PRE_SEL_Msk               (0x07 << R316_REG_SPE_PRE_SEL_Pos)

#define  R316_REG_SPE_XCORR_SEL_Pos             7
#define  R316_REG_SPE_XCORR_SEL_Msk             (0x01 << R316_REG_SPE_XCORR_SEL_Pos)

//--------------------------------------------------------------------------------------------------
#define   R317_REG_DAGC_TARGET_POW               0x317
#define   R317                                   0x317

//--------------------------------------------------------------------------------------------------
#define   R318                                   0x318

#define  R318_REG_DAGC_ALPH1_Pos                0
#define  R318_REG_DAGC_ALPH1_Msk                (0x0f << R318_REG_DAGC_ALPH1_Pos)

#define  R318_REG_DAGC_ALPH2_Pos                4
#define  R318_REG_DAGC_ALPH2_Msk                (0x0f << R318_REG_DAGC_ALPH2_Pos)

//--------------------------------------------------------------------------------------------------
#define   R319_REG_DAGC_PARA_SW_TH               0x319
#define   R319                                   0x319

//--------------------------------------------------------------------------------------------------
#define   R31A_REG_DAGC_GAIN_MANU                0x31a
#define   R31A                                   0x31a

//--------------------------------------------------------------------------------------------------
#define   R31B_REG_FD_END_TH_L                   0x31b
#define   R31B                                   0x31b

//--------------------------------------------------------------------------------------------------
#define   R31C                                   0x31c

#define  R31C_SYNC_SRC_SEL_Pos                  0
#define  R31C_SYNC_SRC_SEL_Msk                  (0x01 << R31C_SYNC_SRC_SEL_Pos)

#define  R31C_PRE_CMP_LEN_Pos                   1
#define  R31C_PRE_CMP_LEN_Msk                   (0x07 << R31C_PRE_CMP_LEN_Pos)

#define  R31C_REG_PULSE_SYNC_MUX_Pos            4
#define  R31C_REG_PULSE_SYNC_MUX_Msk            (0x01 << R31C_REG_PULSE_SYNC_MUX_Pos)

#define  R31C_REG_FLTR_COEF_MUX_Pos             5
#define  R31C_REG_FLTR_COEF_MUX_Msk             (0x01 << R31C_REG_FLTR_COEF_MUX_Pos)

#define  R31C_REG_MAX_VLD_Pos                   6
#define  R31C_REG_MAX_VLD_Msk                   (0x01 << R31C_REG_MAX_VLD_Pos)

#define  R31C_REG_FD_END_TH_H_Pos               7
#define  R31C_REG_FD_END_TH_H_Msk               (0x01 << R31C_REG_FD_END_TH_H_Pos)

//--------------------------------------------------------------------------------------------------
#define   R31D_REG_FD_SYNC_TH                    0x31d
#define   R31D                                   0x31d

//--------------------------------------------------------------------------------------------------
#define   R31E                                   0x31e

#define  R31E_REG_FD_AFC_DATA_KI_Pos            0
#define  R31E_REG_FD_AFC_DATA_KI_Msk            (0x0f << R31E_REG_FD_AFC_DATA_KI_Pos)

#define  R31E_REG_FD_AFC_DATA_KP_Pos            4
#define  R31E_REG_FD_AFC_DATA_KP_Msk            (0x0f << R31E_REG_FD_AFC_DATA_KP_Pos)

//--------------------------------------------------------------------------------------------------
#define   R31F_FALSE_SYNC_TIMEOUT_TH             0x31f
#define   R31F                                   0x31f

//--------------------------------------------------------------------------------------------------
#define   R320_REG_PR_MATCH_IN_TH                0x320
#define   R320                                   0x320

//--------------------------------------------------------------------------------------------------
#define   R321_REG_PR_MATCH_OUT_TH               0x321
#define   R321                                   0x321

//--------------------------------------------------------------------------------------------------
#define   R322                                   0x322

#define  R322_SLOPE_NUM_SEL_Pos                 0
#define  R322_SLOPE_NUM_SEL_Msk                 (0x03 << R322_SLOPE_NUM_SEL_Pos)

#define  R322_AGC_LOCK_SEL_Pos                  2
#define  R322_AGC_LOCK_SEL_Msk                  (0x01 << R322_AGC_LOCK_SEL_Pos)

#define  R322_TX_PRE_ABA_SEL_Pos                3
#define  R322_TX_PRE_ABA_SEL_Msk                (0x01 << R322_TX_PRE_ABA_SEL_Pos)

#define  R322_SINC5_4_CLK_MANUE_EN_Pos          4
#define  R322_SINC5_4_CLK_MANUE_EN_Msk          (0x01 << R322_SINC5_4_CLK_MANUE_EN_Pos)

#define  R322_SINC5_4_CLK_MANUE_Pos             5
#define  R322_SINC5_4_CLK_MANUE_Msk             (0x01 << R322_SINC5_4_CLK_MANUE_Pos)

#define  R322_REG_PPM_ENABLE_Pos                6
#define  R322_REG_PPM_ENABLE_Msk                (0x01 << R322_REG_PPM_ENABLE_Pos)

#define  R322_REG_PPM_DIR_EN_Pos                7
#define  R322_REG_PPM_DIR_EN_Msk                (0x01 << R322_REG_PPM_DIR_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R323_MANU_PREAMBLE_CFO_L1              0x323
#define   R323                                   0x323

//--------------------------------------------------------------------------------------------------
#define   R324_MANU_PREAMBLE_CFO_L2              0x324
#define   R324                                   0x324

//--------------------------------------------------------------------------------------------------
#define   R325                                   0x325

#define  R325_MANU_PREAMBLE_CFO_H_Pos           0
#define  R325_MANU_PREAMBLE_CFO_H_Msk           (0x3f << R325_MANU_PREAMBLE_CFO_H_Pos)

#define  R325_MANU_PREAMBLE_CFO_EN_Pos          6
#define  R325_MANU_PREAMBLE_CFO_EN_Msk          (0x01 << R325_MANU_PREAMBLE_CFO_EN_Pos)

#define  R325_AFC_TR_FREQ_NVLD_Pos              7
#define  R325_AFC_TR_FREQ_NVLD_Msk              (0x01 << R325_AFC_TR_FREQ_NVLD_Pos)

//--------------------------------------------------------------------------------------------------
#define   R326                                   0x326

#define  R326_REG_AFC_POW_PARA2_Pos             0
#define  R326_REG_AFC_POW_PARA2_Msk             (0x0f << R326_REG_AFC_POW_PARA2_Pos)

#define  R326_REG_AFC_POW_PARA1_Pos             4
#define  R326_REG_AFC_POW_PARA1_Msk             (0x0f << R326_REG_AFC_POW_PARA1_Pos)

//--------------------------------------------------------------------------------------------------
#define   R327                                   0x327

#define  R327_REG_FIFO_THRE_Pos                 0
#define  R327_REG_FIFO_THRE_Msk                 (0x7f << R327_REG_FIFO_THRE_Pos)

#define  R327_REG_GAUSS_COEF_MUX_Pos            7
#define  R327_REG_GAUSS_COEF_MUX_Msk            (0x01 << R327_REG_GAUSS_COEF_MUX_Pos)

//--------------------------------------------------------------------------------------------------
#define   R328_REG_AFC_POW_TH                    0x328
#define   R328                                   0x328

//--------------------------------------------------------------------------------------------------
#define   R329_FD_AFC_FREQ_L0                    0x329
#define   R329                                   0x329

//--------------------------------------------------------------------------------------------------
#define   R32A_FD_AFC_FREQ_L1                    0x32a
#define   R32A                                   0x32a

//--------------------------------------------------------------------------------------------------
#define   R32B_FD_AFC_FREQ_H                     0x32b
#define   R32B                                   0x32b

#define  R32B_FD_AFC_FREQ_H_Pos                 0
#define  R32B_FD_AFC_FREQ_H_Msk                 (0x3f << R32B_FD_AFC_FREQ_H_Pos)

//--------------------------------------------------------------------------------------------------
#define   R32C_AFC_FREQ_L0                       0x32c
#define   R32C                                   0x32c

//--------------------------------------------------------------------------------------------------
#define   R32D_AFC_FREQ_L1                       0x32d
#define   R32D                                   0x32d

//--------------------------------------------------------------------------------------------------
#define   R32E_AFC_FREQ_H                        0x32e
#define   R32E                                   0x32e

#define  R32E_AFC_FREQ_H_Pos                    0
#define  R32E_AFC_FREQ_H_Msk                    (0x3f << R32E_AFC_FREQ_H_Pos)

//--------------------------------------------------------------------------------------------------
#define   R32F_PREAMBLE_CFO_L0                   0x32f
#define   R32F                                   0x32f

//--------------------------------------------------------------------------------------------------
#define   R330_PREAMBLE_CFO_L1                   0x330
#define   R330                                   0x330

//--------------------------------------------------------------------------------------------------
#define   R331_PREAMBLE_CFO_H                    0x331
#define   R331                                   0x331

#define  R331_PREAMBLE_CFO_H_Pos                0
#define  R331_PREAMBLE_CFO_H_Msk                (0x3f << R331_PREAMBLE_CFO_H_Pos)

//--------------------------------------------------------------------------------------------------
#define   R332                                   0x332

#define  R332_REG_POWER_GATE_EN_Pos             0
#define  R332_REG_POWER_GATE_EN_Msk             (0x01 << R332_REG_POWER_GATE_EN_Pos)

#define  R332_REG_CLK_DEBUG_INF_EN_Pos          1
#define  R332_REG_CLK_DEBUG_INF_EN_Msk          (0x01 << R332_REG_CLK_DEBUG_INF_EN_Pos)

#define  R332_REG_CLK_FIFO_SEL_Pos              2
#define  R332_REG_CLK_FIFO_SEL_Msk              (0x01 << R332_REG_CLK_FIFO_SEL_Pos)

#define  R332_REG_CLK_MAC_EN_Pos                3
#define  R332_REG_CLK_MAC_EN_Msk                (0x01 << R332_REG_CLK_MAC_EN_Pos)

#define  R332_REG_CLK_MDM_RX_EN_Pos             4
#define  R332_REG_CLK_MDM_RX_EN_Msk             (0x01 << R332_REG_CLK_MDM_RX_EN_Pos)

#define  R332_REG_CLK_MDM_TX_EN_Pos             5
#define  R332_REG_CLK_MDM_TX_EN_Msk             (0x01 << R332_REG_CLK_MDM_TX_EN_Pos)

#define  R332_REG_CLK_LP_EN_Pos                 6
#define  R332_REG_CLK_LP_EN_Msk                 (0x01 << R332_REG_CLK_LP_EN_Pos)

#define  R332_REG_CLK_GATED_TEST_Pos            7
#define  R332_REG_CLK_GATED_TEST_Msk            (0x01 << R332_REG_CLK_GATED_TEST_Pos)

//--------------------------------------------------------------------------------------------------
#define   R333_REG_OSC_SETUP_TIME                0x333
#define   R333                                   0x333

#define  R333_REG_OSC_SETUP_TIME_Pos            0
#define  R333_REG_OSC_SETUP_TIME_Msk            (0x0f << R333_REG_OSC_SETUP_TIME_Pos)

//--------------------------------------------------------------------------------------------------
#define   R334_REG_LDO_ANA_SETUP_TIME            0x334
#define   R334                                   0x334

#define  R334_REG_LDO_ANA_SETUP_TIME_Pos        0
#define  R334_REG_LDO_ANA_SETUP_TIME_Msk        (0x1f << R334_REG_LDO_ANA_SETUP_TIME_Pos)

//--------------------------------------------------------------------------------------------------
#define   R335_REG_LDO_ANA_CLOSE_TIME            0x335
#define   R335                                   0x335

#define  R335_REG_LDO_ANA_CLOSE_TIME_Pos        0
#define  R335_REG_LDO_ANA_CLOSE_TIME_Msk        (0x07 << R335_REG_LDO_ANA_CLOSE_TIME_Pos)

//--------------------------------------------------------------------------------------------------
#define   R336_REG_TX_RFPLL_SETUP_TIME           0x336
#define   R336                                   0x336

#define  R336_REG_TX_RFPLL_SETUP_TIME_Pos       0
#define  R336_REG_TX_RFPLL_SETUP_TIME_Msk       (0x0f << R336_REG_TX_RFPLL_SETUP_TIME_Pos)

//--------------------------------------------------------------------------------------------------
#define   R337_REG_TX_RFPLL_CLOSE_TIME           0x337
#define   R337                                   0x337

#define  R337_REG_TX_RFPLL_CLOSE_TIME_Pos       0
#define  R337_REG_TX_RFPLL_CLOSE_TIME_Msk       (0x07 << R337_REG_TX_RFPLL_CLOSE_TIME_Pos)

//--------------------------------------------------------------------------------------------------
#define   R338_REG_TX_ANA_SETUP_TIME_L           0x338
#define   R338                                   0x338

//--------------------------------------------------------------------------------------------------
#define   R339                                   0x339

#define  R339_REG_TX_ANA_SETUP_TIME_H_Pos       0
#define  R339_REG_TX_ANA_SETUP_TIME_H_Msk       (0x01 << R339_REG_TX_ANA_SETUP_TIME_H_Pos)

#define  R339_REG_TX_ANA_CLOSE_TIME_Pos         4
#define  R339_REG_TX_ANA_CLOSE_TIME_Msk         (0x07 << R339_REG_TX_ANA_CLOSE_TIME_Pos)

#define  R339_REG_FIFO_CLK_EN_Pos               7
#define  R339_REG_FIFO_CLK_EN_Msk               (0x01 << R339_REG_FIFO_CLK_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R33A_REG_RX_RFPLL_SETUP_TIME           0x33a
#define   R33A                                   0x33a

//--------------------------------------------------------------------------------------------------
#define   R33B_REG_RX_RFPLL_CLOSE_TIME           0x33b
#define   R33B                                   0x33b

#define  R33B_REG_RX_RFPLL_CLOSE_TIME_Pos       0
#define  R33B_REG_RX_RFPLL_CLOSE_TIME_Msk       (0x07 << R33B_REG_RX_RFPLL_CLOSE_TIME_Pos)

//--------------------------------------------------------------------------------------------------
#define   R33C_REG_RX_ANA_SETUP_TIME             0x33c
#define   R33C                                   0x33c

#define  R33C_REG_RX_ANA_SETUP_TIME_Pos         0
#define  R33C_REG_RX_ANA_SETUP_TIME_Msk         (0x1f << R33C_REG_RX_ANA_SETUP_TIME_Pos)

//--------------------------------------------------------------------------------------------------
#define   R33D_REG_RX_ANA_CLOSE_TIME             0x33d
#define   R33D                                   0x33d

#define  R33D_REG_RX_ANA_CLOSE_TIME_Pos         0
#define  R33D_REG_RX_ANA_CLOSE_TIME_Msk         (0x07 << R33D_REG_RX_ANA_CLOSE_TIME_Pos)

//--------------------------------------------------------------------------------------------------
#define   R33E                                   0x33e

#define  R33E_REG_LDO_ANA_EN_Pos                3
#define  R33E_REG_LDO_ANA_EN_Msk                (0x01 << R33E_REG_LDO_ANA_EN_Pos)

#define  R33E_REG_OSC_BUF_EN_Pos                4
#define  R33E_REG_OSC_BUF_EN_Msk                (0x01 << R33E_REG_OSC_BUF_EN_Pos)

#define  R33E_REG_LP_TEST_MODE_Pos              7
#define  R33E_REG_LP_TEST_MODE_Msk              (0x01 << R33E_REG_LP_TEST_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R33F                                   0x33f

#define  R33F_REG_RX_EN_ANA_Pos                 2
#define  R33F_REG_RX_EN_ANA_Msk                 (0x01 << R33F_REG_RX_EN_ANA_Pos)

#define  R33F_REG_TX_EN_ANA_Pos                 3
#define  R33F_REG_TX_EN_ANA_Msk                 (0x01 << R33F_REG_TX_EN_ANA_Pos)

#define  R33F_REG_RX_RFPLL_EN_Pos               4
#define  R33F_REG_RX_RFPLL_EN_Msk               (0x01 << R33F_REG_RX_RFPLL_EN_Pos)

#define  R33F_REG_TX_RFPLL_EN_Pos               5
#define  R33F_REG_TX_RFPLL_EN_Msk               (0x01 << R33F_REG_TX_RFPLL_EN_Pos)

#define  R33F_REG_RX_EN_DIG_Pos                 6
#define  R33F_REG_RX_EN_DIG_Msk                 (0x01 << R33F_REG_RX_EN_DIG_Pos)

#define  R33F_REG_TX_EN_DIG_Pos                 7
#define  R33F_REG_TX_EN_DIG_Msk                 (0x01 << R33F_REG_TX_EN_DIG_Pos)

//--------------------------------------------------------------------------------------------------
#define   R340_REG_PA2_DLY_TIME_UP               0x340
#define   R340                                   0x340

#define  R340_REG_PA2_DLY_TIME_UP_Pos           0
#define  R340_REG_PA2_DLY_TIME_UP_Msk           (0x3f << R340_REG_PA2_DLY_TIME_UP_Pos)

//--------------------------------------------------------------------------------------------------
#define   R341_REG_RAMP_DLY_TIME_UP              0x341
#define   R341                                   0x341

#define  R341_REG_RAMP_DLY_TIME_UP_Pos          0
#define  R341_REG_RAMP_DLY_TIME_UP_Msk          (0x3f << R341_REG_RAMP_DLY_TIME_UP_Pos)

//--------------------------------------------------------------------------------------------------
#define   R342_REG_RAMP_DLY_TIME_DN              0x342
#define   R342                                   0x342

#define  R342_REG_RAMP_DLY_TIME_DN_Pos          0
#define  R342_REG_RAMP_DLY_TIME_DN_Msk          (0x3f << R342_REG_RAMP_DLY_TIME_DN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R343_REG_PA2_DLY_TIME_DN               0x343
#define   R343                                   0x343

#define  R343_REG_PA2_DLY_TIME_DN_Pos           0
#define  R343_REG_PA2_DLY_TIME_DN_Msk           (0x3f << R343_REG_PA2_DLY_TIME_DN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R344_REG_RAMP_STEP_UP                  0x344
#define   R344                                   0x344

#define  R344_REG_RAMP_STEP_UP_Pos              0
#define  R344_REG_RAMP_STEP_UP_Msk              (0x07 << R344_REG_RAMP_STEP_UP_Pos)

//--------------------------------------------------------------------------------------------------
#define   R345_REG_RAMP_STEP_DN                  0x345
#define   R345                                   0x345

#define  R345_REG_RAMP_STEP_DN_Pos              0
#define  R345_REG_RAMP_STEP_DN_Msk              (0x07 << R345_REG_RAMP_STEP_DN_Pos)

//--------------------------------------------------------------------------------------------------
#define   R346                                   0x346

#define  R346_REG_EN_PA_BUF_Pos                 0
#define  R346_REG_EN_PA_BUF_Msk                 (0x01 << R346_REG_EN_PA_BUF_Pos)

#define  R346_REG_EN_PA_2ND_Pos                 2
#define  R346_REG_EN_PA_2ND_Msk                 (0x01 << R346_REG_EN_PA_2ND_Pos)

#define  R346_REG_EN_RAMP_Pos                   3
#define  R346_REG_EN_RAMP_Msk                   (0x01 << R346_REG_EN_RAMP_Pos)

//--------------------------------------------------------------------------------------------------
#define   R347                                   0x347

#define  R347_PAD_TEST_MODE_EN_Pos              0
#define  R347_PAD_TEST_MODE_EN_Msk              (0x01 << R347_PAD_TEST_MODE_EN_Pos)

#define  R347_PAD_TEST_MODE_Pos                 1
#define  R347_PAD_TEST_MODE_Msk                 (0x0f << R347_PAD_TEST_MODE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R348                                   0x348

#define  R348_IQMISMATCH_COMPENSATE_EN_Pos      0
#define  R348_IQMISMATCH_COMPENSATE_EN_Msk      (0x01 << R348_IQMISMATCH_COMPENSATE_EN_Pos)

#define  R348_IQMISMATCH_PHSERR_CAL_EN_Pos      1
#define  R348_IQMISMATCH_PHSERR_CAL_EN_Msk      (0x01 << R348_IQMISMATCH_PHSERR_CAL_EN_Pos)

#define  R348_IQMISMATCH_START_CAL_Pos          2
#define  R348_IQMISMATCH_START_CAL_Msk          (0x01 << R348_IQMISMATCH_START_CAL_Pos)

//--------------------------------------------------------------------------------------------------
#define  R349_IQMISMATCH_COMPENSATE_COSG0       0x349

#define   R349_IQMISMATCH_COMPENSATE_COSG0_L     0x349
#define   R349                                   0x349

#define   R34A_IQMISMATCH_COMPENSATE_COSG0_H     0x34a
#define   R34A                                   0x34a

//--------------------------------------------------------------------------------------------------
#define  R34B_IQMISMATCH_COMPENSATE_SING0       0x34b

#define   R34B_IQMISMATCH_COMPENSATE_SING0_L     0x34b
#define   R34B                                   0x34b

#define   R34C_IQMISMATCH_COMPENSATE_SING0_H     0x34c
#define   R34C                                   0x34c

//--------------------------------------------------------------------------------------------------
#define  R34D_IQMISMATCH_COMPENSATE_COSG1       0x34d

#define   R34D_IQMISMATCH_COMPENSATE_COSG1_L     0x34d
#define   R34D                                   0x34d

#define   R34E_IQMISMATCH_COMPENSATE_COSG1_H     0x34e
#define   R34E                                   0x34e

//--------------------------------------------------------------------------------------------------
#define  R34F_IQMISMATCH_COMPENSATE_SING1       0x34f

#define   R34F_IQMISMATCH_COMPENSATE_SING1_L     0x34f
#define   R34F                                   0x34f

#define   R350_IQMISMATCH_COMPENSATE_SING1_H     0x350
#define   R350                                   0x350

//--------------------------------------------------------------------------------------------------
#define  R351_IQMISMATCH_COMPENSATE_COSG2       0x351

#define   R351_IQMISMATCH_COMPENSATE_COSG2_L     0x351
#define   R351                                   0x351

#define   R352_IQMISMATCH_COMPENSATE_COSG2_H     0x352
#define   R352                                   0x352

//--------------------------------------------------------------------------------------------------
#define  R353_IQMISMATCH_COMPENSATE_SING2       0x353

#define   R353_IQMISMATCH_COMPENSATE_SING2_L     0x353
#define   R353                                   0x353

#define   R354_IQMISMATCH_COMPENSATE_SING2_H     0x354
#define   R354                                   0x354

//--------------------------------------------------------------------------------------------------
#define  R355_IQMISMATCH_COMPENSATE_COSG3       0x355

#define   R355_IQMISMATCH_COMPENSATE_COSG3_L     0x355
#define   R355                                   0x355

#define   R356_IQMISMATCH_COMPENSATE_COSG3_H     0x356
#define   R356                                   0x356

//--------------------------------------------------------------------------------------------------
#define  R357_IQMISMATCH_COMPENSATE_SING3       0x357

#define   R357_IQMISMATCH_COMPENSATE_SING3_L     0x357
#define   R357                                   0x357

#define   R358_IQMISMATCH_COMPENSATE_SING3_H     0x358
#define   R358                                   0x358

//--------------------------------------------------------------------------------------------------
#define   R359_IQMISMATCH_GAIN_I_L0              0x359
#define   R359                                   0x359

//--------------------------------------------------------------------------------------------------
#define   R35A_IQMISMATCH_GAIN_I_L1              0x35a
#define   R35A                                   0x35a

//--------------------------------------------------------------------------------------------------
#define   R35B_IQMISMATCH_GAIN_I_L2              0x35b
#define   R35B                                   0x35b

//--------------------------------------------------------------------------------------------------
#define   R35C_IQMISMATCH_GAIN_I_L3              0x35c
#define   R35C                                   0x35c

//--------------------------------------------------------------------------------------------------
#define   R35D_IQMISMATCH_GAIN_I_L4              0x35d
#define   R35D                                   0x35d

//--------------------------------------------------------------------------------------------------
#define   R35E_IQMISMATCH_GAIN_I_L5              0x35e
#define   R35E                                   0x35e

//--------------------------------------------------------------------------------------------------
#define   R35F                                   0x35f

#define  R35F_IQMISMATCH_GAIN_I_H_Pos           0
#define  R35F_IQMISMATCH_GAIN_I_H_Msk           (0x03 << R35F_IQMISMATCH_GAIN_I_H_Pos)

#define  R35F_IQMISMATCH_PHSERR_CALDONE_Pos     2
#define  R35F_IQMISMATCH_PHSERR_CALDONE_Msk     (0x01 << R35F_IQMISMATCH_PHSERR_CALDONE_Pos)

#define  R35F_IQMISMATCH_GAIN_CALDONE_Pos       3
#define  R35F_IQMISMATCH_GAIN_CALDONE_Msk       (0x01 << R35F_IQMISMATCH_GAIN_CALDONE_Pos)

//--------------------------------------------------------------------------------------------------
#define   R360_IQMISMATCH_GAIN_Q_L0              0x360
#define   R360                                   0x360

//--------------------------------------------------------------------------------------------------
#define   R361_IQMISMATCH_GAIN_Q_L1              0x361
#define   R361                                   0x361

//--------------------------------------------------------------------------------------------------
#define   R362_IQMISMATCH_GAIN_Q_L2              0x362
#define   R362                                   0x362

//--------------------------------------------------------------------------------------------------
#define   R363_IQMISMATCH_GAIN_Q_L3              0x363
#define   R363                                   0x363

//--------------------------------------------------------------------------------------------------
#define   R364_IQMISMATCH_GAIN_Q_L4              0x364
#define   R364                                   0x364

//--------------------------------------------------------------------------------------------------
#define   R365_IQMISMATCH_GAIN_Q_L5              0x365
#define   R365                                   0x365

//--------------------------------------------------------------------------------------------------
#define   R366_IQMISMATCH_GAIN_Q_H               0x366
#define   R366                                   0x366

#define  R366_IQMISMATCH_GAIN_Q_H_Pos           0
#define  R366_IQMISMATCH_GAIN_Q_H_Msk           (0x03 << R366_IQMISMATCH_GAIN_Q_H_Pos)

//--------------------------------------------------------------------------------------------------
#define   R367_IQMISMATCH_IQ_DC_L0               0x367
#define   R367                                   0x367

//--------------------------------------------------------------------------------------------------
#define   R368_IQMISMATCH_IQ_DC_L1               0x368
#define   R368                                   0x368

//--------------------------------------------------------------------------------------------------
#define   R369_IQMISMATCH_IQ_DC_L2               0x369
#define   R369                                   0x369

//--------------------------------------------------------------------------------------------------
#define   R36A_IQMISMATCH_IQ_DC_L3               0x36a
#define   R36A                                   0x36a

//--------------------------------------------------------------------------------------------------
#define   R36B_IQMISMATCH_IQ_DC_L4               0x36b
#define   R36B                                   0x36b

//--------------------------------------------------------------------------------------------------
#define   R36C_IQMISMATCH_IQ_DC_L5               0x36c
#define   R36C                                   0x36c

//--------------------------------------------------------------------------------------------------
#define   R36D_IQMISMATCH_IQ_DC_H                0x36d
#define   R36D                                   0x36d

#define  R36D_IQMISMATCH_IQ_DC_H_Pos            0
#define  R36D_IQMISMATCH_IQ_DC_H_Msk            (0x03 << R36D_IQMISMATCH_IQ_DC_H_Pos)

//--------------------------------------------------------------------------------------------------
#define   R36E_NOTCHFLTRCOEFF_L                  0x36e
#define   R36E                                   0x36e

//--------------------------------------------------------------------------------------------------
#define   R36F                                   0x36f

#define  R36F_NOTCHFLTRCOEFF_H_Pos              0
#define  R36F_NOTCHFLTRCOEFF_H_Msk              (0x0f << R36F_NOTCHFLTRCOEFF_H_Pos)

#define  R36F_DC_CLK_EN_Pos                     4
#define  R36F_DC_CLK_EN_Msk                     (0x01 << R36F_DC_CLK_EN_Pos)

//--------------------------------------------------------------------------------------------------
#define  R370_NOTCHFLTRGAIN                     0x370

#define   R370_NOTCHFLTRGAIN_L                   0x370
#define   R370                                   0x370

#define   R371_NOTCHFLTRGAIN_H                   0x371
#define   R371                                   0x371

//--------------------------------------------------------------------------------------------------
#define   R372                                   0x372

#define  R372_REG_BL_FREQ_TR_ALPH1_Pos          0
#define  R372_REG_BL_FREQ_TR_ALPH1_Msk          (0x0f << R372_REG_BL_FREQ_TR_ALPH1_Pos)

#define  R372_REG_BL_FREQ_TR_BETA1_Pos          4
#define  R372_REG_BL_FREQ_TR_BETA1_Msk          (0x0f << R372_REG_BL_FREQ_TR_BETA1_Pos)

//--------------------------------------------------------------------------------------------------
#define   R373_REG_BL_COEF_SW_TH                 0x373
#define   R373                                   0x373

//--------------------------------------------------------------------------------------------------
#define   R374_O_DC_OUT_I_L                      0x374
#define   R374                                   0x374

//--------------------------------------------------------------------------------------------------
#define   R375_O_DC_OUT_Q_L                      0x375
#define   R375                                   0x375

//--------------------------------------------------------------------------------------------------
#define   R376                                   0x376

#define  R376_O_DC_OUT_Q_H_Pos                  0
#define  R376_O_DC_OUT_Q_H_Msk                  (0x0f << R376_O_DC_OUT_Q_H_Pos)

#define  R376_O_DC_OUT_I_H_Pos                  4
#define  R376_O_DC_OUT_I_H_Msk                  (0x0f << R376_O_DC_OUT_I_H_Pos)

//--------------------------------------------------------------------------------------------------
#define   R377_REG_XCORR_2ND_TH                  0x377
#define   R377                                   0x377

//--------------------------------------------------------------------------------------------------
#define   R378                                   0x378

#define  R378_PRE_SPE_CNT_TH_Pos                0
#define  R378_PRE_SPE_CNT_TH_Msk                (0x7f << R378_PRE_SPE_CNT_TH_Pos)

#define  R378_PRE_SPE_CNT_VLD_Pos               7
#define  R378_PRE_SPE_CNT_VLD_Msk               (0x01 << R378_PRE_SPE_CNT_VLD_Pos)

//--------------------------------------------------------------------------------------------------
#define   ACTIMER_OVR_BYTE0                      0x400
#define   ACTIMER_OVR_BYTE1                      0x401
#define   ACTIMER_OVR_BYTE2                      0x402
#define   ACTIMER_OVR_BYTE3                      0x403
#define   ACTIMER_OVR_BYTE4                      0x404
#define   ACTIMER_OVR_BYTE5                      0x405
#define   ACTIMER_OVR_BYTE6                      0x406
#define   ACTIMER_OVR_BYTE7                      0x407

#define  ACTIMER_OVR_L32                        0x400
#define  ACTIMER_OVR_H32                        0x404

//--------------------------------------------------------------------------------------------------
#define   ACTIMER_CMP0_BYTE0                     0x408
#define   ACTIMER_CMP0_BYTE1                     0x409
#define   ACTIMER_CMP0_BYTE2                     0x40A
#define   ACTIMER_CMP0_BYTE3                     0x40B
#define   ACTIMER_CMP0_BYTE4                     0x40C
#define   ACTIMER_CMP0_BYTE5                     0x40D
#define   ACTIMER_CMP0_BYTE6                     0x40E
#define   ACTIMER_CMP0_BYTE7                     0x40F

#define  ACTIMER_CMP0_L32                       0x408
#define  ACTIMER_CMP0_H32                       0x40C

//--------------------------------------------------------------------------------------------------
#define   ACTIMER_CMP1_BYTE0                     0x410
#define   ACTIMER_CMP1_BYTE1                     0x411
#define   ACTIMER_CMP1_BYTE2                     0x412
#define   ACTIMER_CMP1_BYTE3                     0x413
#define   ACTIMER_CMP1_BYTE4                     0x414
#define   ACTIMER_CMP1_BYTE5                     0x415
#define   ACTIMER_CMP1_BYTE6                     0x416
#define   ACTIMER_CMP1_BYTE7                     0x417

#define  ACTIMER_CMP1_L32                       0x410
#define  ACTIMER_CMP1_H32                       0x414

//--------------------------------------------------------------------------------------------------
#define   ACTIMER_CMP2_BYTE0                     0x418
#define   ACTIMER_CMP2_BYTE1                     0x419
#define   ACTIMER_CMP2_BYTE2                     0x41A
#define   ACTIMER_CMP2_BYTE3                     0x41B
#define   ACTIMER_CMP2_BYTE4                     0x41C
#define   ACTIMER_CMP2_BYTE5                     0x41D
#define   ACTIMER_CMP2_BYTE6                     0x41E
#define   ACTIMER_CMP2_BYTE7                     0x41F

#define  ACTIMER_CMP2_L32                       0x418
#define  ACTIMER_CMP2_H32                       0x41C

//--------------------------------------------------------------------------------------------------
#define   ACTIMER_CAP0_BYTE0                     0x420
#define   ACTIMER_CAP0_BYTE1                     0x421
#define   ACTIMER_CAP0_BYTE2                     0x422
#define   ACTIMER_CAP0_BYTE3                     0x423
#define   ACTIMER_CAP0_BYTE4                     0x424
#define   ACTIMER_CAP0_BYTE5                     0x425
#define   ACTIMER_CAP0_BYTE6                     0x426
#define   ACTIMER_CAP0_BYTE7                     0x427

#define  ACTIMER_CAP0_L32                       0x420
#define  ACTIMER_CAP0_H32                       0x424

//--------------------------------------------------------------------------------------------------
#define   ACTIMER_CAP1_BYTE0                     0x428
#define   ACTIMER_CAP1_BYTE1                     0x429
#define   ACTIMER_CAP1_BYTE2                     0x42A
#define   ACTIMER_CAP1_BYTE3                     0x42B
#define   ACTIMER_CAP1_BYTE4                     0x42C
#define   ACTIMER_CAP1_BYTE5                     0x42D
#define   ACTIMER_CAP1_BYTE6                     0x42E
#define   ACTIMER_CAP1_BYTE7                     0x42F

#define  ACTIMER_CAP1_L32                       0x428
#define  ACTIMER_CAP1_H32                       0x42C

//--------------------------------------------------------------------------------------------------
#define   ACTIMER_CNT_BYTE0                      0x430
#define   ACTIMER_CNT_BYTE1                      0x431
#define   ACTIMER_CNT_BYTE2                      0x432
#define   ACTIMER_CNT_BYTE3                      0x433
#define   ACTIMER_CNT_BYTE4                      0x434
#define   ACTIMER_CNT_BYTE5                      0x435
#define   ACTIMER_CNT_BYTE6                      0x436
#define   ACTIMER_CNT_BYTE7                      0x437

#define  ACTIMER_CNT_L32                        0x430
#define  ACTIMER_CNT_H32                        0x434

//--------------------------------------------------------------------------------------------------
#define   RCLTRIM_CALCNT_BYTE0                   0x440
#define   RCLTRIM_CALCNT_BYTE1                   0x441
#define   RCLTRIM_CALCNT_BYTE2                   0x442

//--------------------------------------------------------------------------------------------------
#define   RCLTRIM_WAITCNT                        0x443

//--------------------------------------------------------------------------------------------------
#define   RCLTRIM_IDEACNT_BYTE0                  0x444
#define   RCLTRIM_IDEACNT_BYTE1                  0x445
#define   RCLTRIM_IDEACNT_BYTE2                  0x446
#define   RCLTRIM_IDEACNT_BYTE3                  0x447

#define  RCLTRIM_IDEACNT_L16                    0x444
#define  RCLTRIM_IDEACNT_H16                    0x446

#define  RCLTRIM_IDEACNT                        0x444

//--------------------------------------------------------------------------------------------------
#define   RCLTRIM_REFCNT_BYTE0                   0x448
#define   RCLTRIM_REFCNT_BYTE1                   0x449
#define   RCLTRIM_REFCNT_BYTE2                   0x44A
#define   RCLTRIM_REFCNT_BYTE3                   0x44B

#define  RCLTRIM_REFCNT_L16                     0x448
#define  RCLTRIM_REFCNT_H16                     0x44A

#define  RCLTRIM_REFCNT                         0x448

//--------------------------------------------------------------------------------------------------

#endif //__PAN312X_XSFR_H
