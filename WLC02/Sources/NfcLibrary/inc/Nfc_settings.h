/*
*         Copyright (c), NXP Semiconductors Caen / France
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/
#include "hal.h"
/***** NFC dedicated setting ****************************************/

/* Following definitions specifies which settings will apply when NxpNci_ConfigureSettings()
 * API is called from the application
 */
#define NXP_CORE_CONF        0
#define NXP_CORE_CONF_EXTN   0
#define NXP_CORE_STANDBY     0
#define NXP_CLK_CONF         0 // 1=Xtal, 2=PLL
#define NXP_TVDD_CONF        0 // 1=CFG1, 2=CFG2

#if NXP_CORE_CONF
/* NCI standard dedicated settings
 * Refer to NFC Forum NCI standard for more details
 */
uint8_t NxpNci_CORE_CONF[]={0x20, 0x02, 0x05, 0x01,         /* CORE_SET_CONFIG_CMD */
    0x00, 0x02, 0x00, 0x01                                  /* TOTAL_DURATION */
};
#endif

#if NXP_CORE_CONF_EXTN
/* NXP-NCI extension dedicated setting
 * Refer to NFC controller User Manual for more details
 */
uint8_t NxpNci_CORE_CONF_EXTN[]={0x20, 0x02, 0x0D, 0x03,    /* CORE_SET_CONFIG_CMD */
    0xA0, 0x40, 0x01, 0x00,                                 /* TAG_DETECTOR_CFG */
    0xA0, 0x41, 0x01, 0x04,                                 /* TAG_DETECTOR_THRESHOLD_CFG */
    0xA0, 0x43, 0x01, 0x00                                  /* TAG_DETECTOR_FALLBACK_CNT_CFG */
};
#endif

#if NXP_CORE_STANDBY
/* NXP-NCI standby enable setting
 * Refer to NFC controller User Manual for more details
 */
uint8_t NxpNci_CORE_STANDBY[]={0x2F, 0x00, 0x01, 0x01};    /* last byte indicates enable/disable */
#endif

#if NXP_CLK_CONF
/* NXP-NCI CLOCK configuration
 * Refer to NFC controller Hardware Design Guide document for more details
 */
 #if (NXP_CLK_CONF == 1)
  /* Xtal configuration */
  uint8_t NxpNci_CLK_CONF[]={0x20, 0x02, 0x05, 0x01,        /* CORE_SET_CONFIG_CMD */
    0xA0, 0x03, 0x01, 0x08                                  /* CLOCK_SEL_CFG */
  };
  #else
  /* PLL configuration */
  uint8_t NxpNci_CLK_CONF[]={0x20, 0x02, 0x09, 0x02,        /* CORE_SET_CONFIG_CMD */
    0xA0, 0x03, 0x01, 0x11,                                 /* CLOCK_SEL_CFG */
    0xA0, 0x04, 0x01, 0x01                                  /* CLOCK_TO_CFG */
  };
  #endif
#endif

#if NXP_TVDD_CONF
/* NXP-NCI TVDD configuration
 * Refer to NFC controller Hardware Design Guide document for more details
 */
/* RF configuration related to 1st generation of NXP-NCI controller (e.g PN7120) */
uint8_t NxpNci_TVDD_CONF_1stGen[]={0x20, 0x02, 0x05, 0x01, 0xA0, 0x13, 0x01, 0x00};

/* RF configuration related to 2nd generation of NXP-NCI controller (e.g PN7150)*/
 #if (NXP_TVDD_CONF == 1)
 /* CFG1: Vbat is used to generate the VDD(TX) through TXLDO */
 uint8_t NxpNci_TVDD_CONF_2ndGen[]={0x20, 0x02, 0x07, 0x01, 0xA0, 0x0E, 0x03, 0x02, 0x09, 0x00};
 #else
 /* CFG2: external 5V is used to generate the VDD(TX) through TXLDO */
 uint8_t NxpNci_TVDD_CONF_2ndGen[]={0x20, 0x02, 0x07, 0x01, 0xA0, 0x0E, 0x03, 0x06, 0x64, 0x00};
 #endif
#endif
