/*
 * systemStatus.h
 *
 *  Created on: 2019年6月28日
 *      Author: jiangxl
 */

#ifndef SYSTEMSTATUS_H_
#define SYSTEMSTATUS_H_

#include "defines.h"

typedef enum
{
  StateSelection,
  StatePing,
  StateIdentConfig,
  StatePowerTrans,
  StateTerminate,
  StateSafe,
  StateCount,
  StateInvalid
}StateId;

typedef enum
{
  EvtMsgSigStrength,
  EvtMsgConfig,
  EvtMsgErrorCtrl,
  EvtMsgEPT,
  EvtMsgTerminate,
  EvtMsgUnexpected,
  EvtMsgWrongValue,
  EvtReconfig,
  EvtRestart,
  EvtObjectDetected,
  EvtObjectRemoved,
  EvtTimeOut,
  EvtUnsafe,
  EventCount ,
  EvtNull                      //for marking the end of a transition tabele
}EventId;

typedef struct
{
  EventId       eventId;
  uint8_t       param1;
}EventInfo;

typedef void (*HStateEntry)(EventId id, uint8 eventParam);
typedef void (*HStateExit)(void);
typedef boolean (*HStateAction)(EventInfo* pEvtInfo);

typedef struct
{
  EventId               eventId;
  StateId               nextState;
}StateTransit;

typedef struct
{
  HStateEntry           hStateEntry;
  HStateExit            hStateExit;
  HStateAction          hStateAction;
  StateTransit*         pStateTransit;
}StateSet;



/*******************************************************************************

各状态机处理函数
*********************************************************************************/
void SSelectionEntry(EventId eventId, uint8_t eventParam);
void SSelectionExit();
boolean SSelectionAction(EventInfo* pEvtInfo);

void SPingEntry(EventId eventId, uint8_t eventParam);
void SPingExit();
boolean SPingAction(EventInfo* pEvtInfo);
uint8 GetSSelectionSignal(void);
boolean HAL_GetKeyCoilObjSts(void);
uint8	HAL_GetKeyCoilSel(void);

void SIdentConfigEntry(EventId eventId, uint8_t eventParam);
void SIdentConfigExit();
boolean SIdentConfigAction(EventInfo* pEvtInfo);

void SPowerTransEntry(EventId eventId, uint8_t eventParam);
void SPowerTransExit();
boolean SPowerTransAction(EventInfo* pEvtInfo);

void SPowerTansSetHoldOfftime(uint8_t holdOffTimeMsg);
uint8_t GetRecvPower(void);
uint16 GetActCurrent(void);
uint16 GetActVol(void);
uint8 GetchargeStatus(void);
//void ResetPreRxDetectFlag(void);
uint8_t GetControlError(void);


void STerminateEntry(EventId eventId, uint8_t eventParam);
void STerminateExit();
boolean STerminateAction(EventInfo* pEvtInfo);

uint8 GetCodeEPT(void);
void SetCodeEPT(void);

void SSafeEntry(EventId eventId, uint8_t eventParam);
void SSafeExit();
boolean SSafeAction(EventInfo* pEvtInfo);
boolean IsRxDetected(void);


boolean GetKeyEvent(StateId KeycurrentState, EventInfo* pEventInfo);
void InitSystemStatus(void);
void ResetSystemStatus(void);
void SysStatusRun(void);


/*
 * system status
 */
typedef enum
{
	SysStateOff,
  SysStateStandby,
  SysStateCharge,
  SysStateNfc,
  SysStateFault,
  SysStatePause,
  SysStateCount,
  SysStateInvalid
}SysStateId;

typedef enum
{
  EvtSysTransNext,
  EvtLpcdObjExist,
  EvtSysChargeDone,
  EvtSysSearchKey,
  EvtSysUnsafe,
  EvtSysCount ,
  EvtSysNull                      //for marking the end of a transition tabele
}SysEventId;

typedef struct
{
  SysEventId    SyseventId;
  uint8_t       Sysparam1;
}SysEventInfo;

typedef void (*SysHStateEntry)(SysEventId id, uint8 eventParam);
typedef void (*SysHStateExit)(void);
typedef boolean (*SysHStateAction)(SysEventInfo* pEvtInfo);

typedef struct
{
  SysEventId               SyseventId;
  SysStateId               SysnextState;
}SysStateTransit;

typedef struct
{
  SysHStateEntry           SyshStateEntry;
  SysHStateExit            SyshStateExit;
  SysHStateAction          SyshStateAction;
  SysStateTransit*         SyspStateTransit;
}SysStateSet;

/*******************************************************************************

各状态机处理函数
*********************************************************************************/
void SysOffEntry(SysEventId eventId, uint8_t eventParam);
void SysOffExit();
boolean SysOffAction(SysEventInfo* pEvtInfo);

void SysStandbyEntry(SysEventId eventId, uint8_t eventParam);
void SysStandbyExit();
boolean SysStandbyAction(SysEventInfo* pEvtInfo);

void SysNfcEntry(SysEventId eventId, uint8_t eventParam);
void SysNfcExit();
boolean SysNfcAction(SysEventInfo* pEvtInfo);

void SysChargeEntry(SysEventId eventId, uint8_t eventParam);
void SysChargeExit();
boolean SysChargeAction(SysEventInfo* pEvtInfo);

void SysFaultEntry(SysEventId eventId, uint8_t eventParam);
void SysFaultExit();
boolean SysFaultAction(SysEventInfo* pEvtInfo);

void SysPauseEntry(SysEventId eventId, uint8_t eventParam);
void SysPauseExit();
boolean SysPauseAction(SysEventInfo* pEvtInfo);

// WLC CAN TX Messages
#define IMOB_WLC_CGW 	0x28
#define DIAG_RESP_WLC	0x6B8
#define NM_WLC			0x538
#define WLC_01			0x3E3
#define WLC_02			0x340
#define WLC_CDC_NFC		0x4AE
#define	WLC_DEVLP_01	0x4BB

// WLC CAN RX Messages
#define	BCU_04			0x5B
#define CDC_IC_01		0x3AA
#define CDC_WLC			0x2BA
#define CDC_WLC_NFC		0x4AF
#define CGW_02			0x2C3
#define CGW_03			0x10C
#define CGW_TCU_01		0x3B2
#define CGW_WLC			0x3BE
#define DIAG_REQ_AllECU	0x601
#define	DIAG_REQ_WLC	0x638
#define IMOB_CGW_WLC	0x27
#define NM_CGW			0x505
#define WLC_DEVLP_02	0x4BC

typedef enum
{
  PChargeDisable,
  PChargeEnable,
  PChargeCount
}WctCommand;

typedef enum
{
  PChargeNoCharge = 0,
  PChargeOnCharging,
  PChargeOVP,
  PChargeUVP,
  PChargeOCP,
  PChargeOTP,
  PChargeInternalErr,
  PChargePreFOD,
  PChargePowerTransferFOD,
  PChargeRxUnknow,
  PChargeRxChargeComplete,
  PChargeRxInternalErr,
  PChargeRxOVP,
  PChargeRxOCP,
  PChargeRxOTP,
  PChargeRxBatteryFailure,
  PChargeRxNoResp,
  PChargeRxNegotFail,
  PChargeStsCount

}PWctStatus;

uint8 GetChargeFlag(void);
void ResetChargeFlag(void);
void SetDevCheckFlag(uint8 flag);
void SetObjDetFlag(uint8 flag);

typedef enum
{
  KChargeNoCharge = 0,
  KChargeOnCharging,
  KChargeOVP,
  KChargeOCP,
  KChargeOTP,
  KChargeInternalErr,
  KChargePowerTransferFOD,
  KChargeRxUnknow,
  KChargeRxChargeComplete,
  KChargeRxInternalErr,
  KChargeRxOVP,
  KChargeRxOCP,
  KChargeRxOTP,
  KChargeRxBatteryFailure,
  KChargeRxNoResp,
  KChargeStsCount

}KWctStatus;


KWctStatus GetKeyChargeSts(void);
void SetKeyChargeSts(KWctStatus chrgsts);


typedef struct
{
	uint8 DiagRespData0_WLC;
	uint8 DiagRespData1_WLC;
	uint8 DiagRespData2_WLC;
	uint8 DiagRespData3_WLC;
	uint8 DiagRespData4_WLC;
	uint8 DiagRespData5_WLC;
	uint8 DiagRespData6_WLC;
	uint8 DiagRespData7_WLC;
} DIAG_RESP_WLC_0X6B8;

typedef struct
{
	uint8 Imob_WLC_CGW_Byte0;
	uint8 Imob_WLC_CGW_Byte1;
	uint8 Imob_WLC_CGW_Byte2;
	uint8 Imob_WLC_CGW_Byte3;
	uint8 Imob_WLC_CGW_Byte4;
	uint8 Imob_WLC_CGW_Byte5;
	uint8 Imob_WLC_CGW_Byte6;
	uint8 Imob_WLC_CGW_Byte7;
} IMOB_WLC_CGW_0X28;

typedef struct
{
	uint8 ActvWakeup_WLC;
	uint8 NetMngtCoorn_WLC;
	uint8 NetMngtCoorrSleepRdy_WLC;
	uint8 PtlNetInfo_WLC;
	uint8 RepMsgReq_WLC;
	uint8 ResdBit1_WLC;
	uint8 ResdBit2_WLC;
	uint8 ScrNodId_WLC;
	uint8 UsrData0_WLC;
	uint8 UsrData1_WLC;
	uint8 UsrData2_WLC;
	uint8 UsrData3_WLC;
	uint8 UsrData4_WLC;
	uint8 UsrData5_WLC;
} NM_WLC_0X538;

typedef enum
{
	FailTypeNoFailure = 0,
	FailTypeOverTemp = 1,
	FailTypeUnderVol = 2,
	FailTypeOverVol = 3,
	FailTypeInternalErr = 4,
	FailTypeFodExist = 5,
	FailTypeUnknownErr = 6,
	FailTypeRxNoResp = 7,
	FailTypeDevDetected = 8,
	FailTypeReserved = 9,
	FailTypeInvalid = 15
} WLCFAILTYPE;

typedef struct
{
	uint8 WLC_01_CRC;
	uint8 WLC_01_MsgCntr;
	uint8 WLCChrgRate;
	uint8 WLCChrgSts;
	uint8 WLCCtrlSts;
	WLCFAILTYPE WLCFailSts;
	uint8 WLCMuteViaHW;
} WLC_01_0X3E3;

typedef enum
{
	Disable = 0,
	Enable = 1,
	Reserved = 2,
	Invalid = 3
} IMOBSTSTYPE;

typedef struct
{
	uint8 WLC_02_CRC;
	uint8 WLC_02_MsgCntr;
	IMOBSTSTYPE WLCImobSts;
} WLC_02_0X340;

typedef struct
{
	uint8 WLCBTInfo_Byte0;
	uint8 WLCBTInfo_Byte1;
	uint8 WLCBTInfo_Byte2;
	uint8 WLCBTInfo_Byte3;
	uint8 WLCBTInfo_Byte4;
	uint8 WLCBTInfo_Byte5;
	uint8 WLCBTInfo_Byte6;
	uint8 WLCBTInfo_Byte7;
} WLC_CDC_NFC_0X4AE;


typedef struct
{
	uint8 WLCDevlpTx_Byte0;
	uint8 WLCDevlpTx_Byte1;
	uint8 WLCDevlpTx_Byte2;
	uint8 WLCDevlpTx_Byte3;
	uint8 WLCDevlpTx_Byte4;
	uint8 WLCDevlpTx_Byte5;
	uint8 WLCDevlpTx_Byte6;
	uint8 WLCDevlpTx_Byte7;
} WLC_DEVLP_01_0X4BB;

typedef struct
{
	uint16 VehSpd;
} BCU_04_0x5B;

typedef struct
{
	uint32 VehOdometer;
} CDC_IC_01_0x3AA;

typedef struct
{
	uint8 WLCChrgFctEnaReq;
} CDC_WLC_0x2BA;

typedef struct
{
	uint8 CDCBTInfo0;
	uint8 CDCBTInfo1;
	uint8 CDCBTInfo2;
	uint8 CDCBTInfo3;
	uint8 CDCBTInfo4;
	uint8 CDCBTInfo5;
	uint8 CDCBTInfo6;
	uint8 CDCBTInfo7;
} CDC_WLC_NFC_0x4AF;

typedef enum
{
  Parked = 0,
  Driver_present = 1,
  Driving = 2,
  Software_Update = 3,
  VehStsReserved = 4,
  VehStsInvalid = 15
}VehSTS;

typedef enum
{
  ImobDisable = 0,
  ImobEnaAID1 = 1,
  ImobEnaAID2 = 2,
  ImobInvalid = 3
}IMOREQTYPE;

typedef enum
{
  ComfNotEna = 0,
  COMFENA = 1,
  ComfReserved = 2,
  ComfInvalid = 3
}COMFENATYPE;

typedef struct
{
	COMFENATYPE Comf_Ena;
	IMOREQTYPE ImobEnaReq;
	VehSTS VehState;
} CGW_02_0x2C3;

typedef struct
{
	uint8 CGW_03_CRC;
	uint8 CGW_03_MsgCntr;
	uint8 ComfEna_ASIL;
	uint8 VehState_ASIL;
} CGW_03_0x10C;

typedef struct
{
	/*uint8 Day;
	uint8 Hr;
	uint8 Min;
	uint8 Mth;
	uint8 Sec;
	uint8 Yr;
	uint8 Day;*/
	uint8 Yr;
	uint8 Mth;
	uint8 Day;
	uint8 Hr;
	uint8 Min;
	uint8 Sec;
} CGW_TCU_01_0x3B2;

typedef struct
{
	uint8 CGW_WLC_CRC;
	uint8 CGW_WLC_MsgCntr;
} CGW_WLC_0x3BE;

typedef struct
{
	uint8 DiagReqData0_AllECU;
	uint8 DiagReqData1_AllECU;
	uint8 DiagReqData2_AllECU;
	uint8 DiagReqData3_AllECU;
	uint8 DiagReqData4_AllECU;
	uint8 DiagReqData5_AllECU;
	uint8 DiagReqData6_AllECU;
	uint8 DiagReqData7_AllECU;
} DIAG_REQ_AllECU_0x3B2;

typedef struct
{
	uint8 DiagReqData0_WLC;
	uint8 DiagReqData1_WLC;
	uint8 DiagReqData2_WLC;
	uint8 DiagReqData3_WLC;
	uint8 DiagReqData4_WLC;
	uint8 DiagReqData5_WLC;
	uint8 DiagReqData6_WLC;
	uint8 DiagReqData7_WLC;
} DIAG_REQ_WLC_0x638;

typedef struct
{
	uint8 Imob_CGW_WLC_Byte0;
	uint8 Imob_CGW_WLC_Byte1;
	uint8 Imob_CGW_WLC_Byte2;
	uint8 Imob_CGW_WLC_Byte3;
	uint8 Imob_CGW_WLC_Byte4;
	uint8 Imob_CGW_WLC_Byte5;
	uint8 Imob_CGW_WLC_Byte6;
	uint8 Imob_CGW_WLC_Byte7;
} IMOB_CGW_WLC_0x27;

typedef struct
{
	uint8 ActvWakeup_CGW;
	uint8 NetMngtCoorn_CGW;
	uint8 NetMngtCoorrSleepRdy_CGW;
	uint8 PtlNetInfo_CGW;
	uint8 RepMsgReq_CGW;
	uint8 ResdBit1_CGW;
	uint8 ResdBit2_CGW;
	uint8 ScrNodId_CGW;
	uint8 UsrData0_CGW;
	uint8 UsrData1_CGW;
	uint8 UsrData2_CGW;
	uint8 UsrData3_CGW;
	uint8 UsrData4_CGW;
	uint8 UsrData5_CGW;
} NM_CGW_0x505;


typedef enum
{
	TestMode_AllClose,
	TestMode_Sleep,
	TestMode_Ping,
	TestMode_PhoneCharge,
	TestMode_PingNFC,
	TestMode_NFCP2P,
	TestMode_KeyCharge,
	TestMode_reserved
}TESTMODETYPE;

typedef struct
{
	uint8 TestModeForEMC;

} WLC_DEVLP_02_0x4BC;


typedef struct
{
	boolean CdcBtReq;
	boolean CdcWifiReq;
	boolean	CdcNotifBt;
	boolean	CdcNotifWifi;
} CDC_BTWIFI_Command;


uint16	GetCanTpDataLength(void);
uint8 NotificationBTHandler(uint8* data, uint16 len);
uint8 NotificationWIFIHandler(uint8* data, uint16 len);

extern uint8	gTestResp_Data[8];

extern boolean	gCanNMWakeupFlag;

#endif /* SYSTEMSTATUS_H_ */
