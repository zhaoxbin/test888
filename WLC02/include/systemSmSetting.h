/*
 * systemSmSetting.h
 *
 *  Created on: 2019Äê6ÔÂ28ÈÕ
 *      Author: jiangxl
 */

#ifndef SYSTEMSMSETTING_H_
#define SYSTEMSMSETTING_H_



#include "systemStatus.h"



StateTransit stateSelectionTransit[]={
  //eventId                     nextState
  {EvtObjectDetected,           StatePing},
  {EvtUnsafe,                   StateSafe},
  {EvtNull,                     StateInvalid}                      //EvtNull marks end of the table
};

StateTransit statePingTransit[]={
  //eventId                     nextState
  {EvtMsgSigStrength,           StateIdentConfig},
  {EvtTimeOut,                 	StateTerminate},                    //timeout Tfirst or Tping
  {EvtMsgEPT,                   StateTerminate},
  {EvtMsgUnexpected,            StateTerminate},
  {EvtUnsafe,                   StateSafe},
  {EvtNull,                     StateInvalid}                      //EvtNull marks end of the table

};


StateTransit stateIdentConfigTransit[]={
  //eventId                     nextState
  {EvtMsgConfig,                StatePowerTrans},
  {EvtTimeOut,                 	StateTerminate},        //timeout T_NEXT or T_MAX
  {EvtMsgEPT,                   StateTerminate},
  {EvtMsgUnexpected,            StateTerminate},
  {EvtMsgWrongValue,            StateTerminate},
  {EvtUnsafe,                   StateSafe},
  {EvtNull,                     StateInvalid}                      //EvtNull marks end of the table
};


StateTransit statePowerTransTransit[]={
  //eventId                     nextState
  {EvtMsgEPT,                   StateTerminate},
  {EvtTimeOut,                 	StateTerminate},        //timeout T_TIMEOUT or TPOwer
  {EvtMsgUnexpected,            StateTerminate},
  {EvtObjectDetected,           StateSafe},
  {EvtUnsafe,                   StateSafe},
  {EvtNull,                     StateInvalid}                      //EvtNull marks end of the table

};


StateTransit stateTerminateTransit[]={
  //eventId                     nextState
  {EvtReconfig,                 StateIdentConfig},
  {EvtRestart,                  StateSelection},
  {EvtUnsafe,                   StateSafe},
  {EvtNull,                     StateInvalid}                      //EvtNull marks end of the table

};


StateTransit stateSafeTransit[]={
  //eventId                     nextState
  {EvtRestart,                  StateSelection},
  {EvtNull,                     StateInvalid}                      //EvtNull marks end of the table
};


StateSet SM_Table[]=
{
  {SSelectionEntry,             SSelectionExit,         SSelectionAction,               stateSelectionTransit},
  {SPingEntry,                  SPingExit,              SPingAction,                    statePingTransit},
  {SIdentConfigEntry,           SIdentConfigExit,       SIdentConfigAction,             stateIdentConfigTransit},
  {SPowerTransEntry,            SPowerTransExit,        SPowerTransAction,              statePowerTransTransit },
  {STerminateEntry,             STerminateExit,         STerminateAction,               stateTerminateTransit},
  {SSafeEntry,                  SSafeExit,              SSafeAction,                    stateSafeTransit}
};


/*
 *  system status
 */
SysStateTransit SysstateOffTransit[]={
  //eventId                     nextState
  //{EvtLpcdObjExist,           SysStateCharge}
  //{EvtUnsafe,                   StateSafe},
  //{EvtNull,                     StateInvalid}                      //EvtNull marks end of the table
};


SysStateTransit SysstateStandbyTransit[]={
  //eventId                     nextState
  {EvtLpcdObjExist,           SysStateCharge}
  //{EvtUnsafe,                   StateSafe},
  //{EvtNull,                     StateInvalid}                      //EvtNull marks end of the table
};

SysStateTransit SysstateChargeTransit[]={
  //eventId                     nextState
 // {EvtMsgSigStrength,           StateIdentConfig},
 // {EvtTimeOut,                 	StateTerminate},                    //timeout Tfirst or Tping
 // {EvtMsgEPT,                   StateTerminate},
 // {EvtMsgUnexpected,            StateTerminate},
 // {EvtUnsafe,                   StateSafe},
 // {EvtNull,                     StateInvalid}                      //EvtNull marks end of the table

};


SysStateTransit SysstateNfcTransit[]={
  //eventId                     nextState
//  {EvtMsgConfig,                StatePowerTrans},
//  {EvtTimeOut,                 	StateTerminate},        //timeout T_NEXT or T_MAX
//  {EvtMsgEPT,                   StateTerminate},
//  {EvtMsgUnexpected,            StateTerminate},
//  {EvtMsgWrongValue,            StateTerminate},
//  {EvtUnsafe,                   StateSafe},
//  {EvtNull,                     StateInvalid}                      //EvtNull marks end of the table
};


SysStateTransit SysstateFaultTransit[]={
  //eventId                     nextState
//  {EvtMsgEPT,                   StateTerminate},
//  {EvtTimeOut,                 	StateTerminate},        //timeout T_TIMEOUT or TPOwer
//  {EvtMsgUnexpected,            StateTerminate},
//  {EvtObjectDetected,           StateSafe},
//  {EvtUnsafe,                   StateSafe},
//  {EvtNull,                     StateInvalid}                      //EvtNull marks end of the table

};


SysStateTransit SysstatePauseTransit[]={
  //eventId                     nextState
//  {EvtReconfig,                 StateIdentConfig},
//  {EvtRestart,                  StateSelection},
//  {EvtUnsafe,                   StateSafe},
//  {EvtNull,                     StateInvalid}                      //EvtNull marks end of the table

};


SysStateSet Sys_SM_Table[]=
{
  {SysOffEntry,                 SysOffExit,             SysOffAction,                   SysstateOffTransit},
  {SysStandbyEntry,             SysStandbyExit,         SysStandbyAction,               SysstateStandbyTransit},
  {SysChargeEntry,              SysChargeExit,          SysChargeAction,                SysstateChargeTransit},
  {SysNfcEntry,           		SysNfcExit,       		SysNfcAction,             		SysstateNfcTransit},
  {SysFaultEntry,            	SysFaultExit,        	SysFaultAction,              	SysstateFaultTransit},
  {SysPauseEntry,             	SysPauseExit,         	SysPauseAction,               	SysstatePauseTransit}
};



#endif /* SYSTEMSMSETTING_H_ */
