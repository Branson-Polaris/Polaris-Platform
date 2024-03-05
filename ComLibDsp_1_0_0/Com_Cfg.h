/*
 * Com_Cfg.h
 *
 *  Created on: 25.05.2021
 *      Author: hjouini_3P13713
 */

#ifndef COM_CFG_H_
#define COM_CFG_H_

#define COM_CMD_REQUEST_DATA_MAX  (128)
#define COM_CMD_RESPONSE_DATA_MAX (128)

#define COM_DSP_DATA_LENGTH      (7)
#define COM_ARM_DATA_LENGTH      (11)

#define COM_COMMAND_SET_LED    0x1
#define COM_COMMAND_TOGGLE_LED 0x2

#pragma pack ( push, 1)

typedef struct DspInfoData_t
{
    uint32_t FwVersion;
}
DspInfoData;

typedef struct DspConfigData_t
{
    uint32_t Cfg_A;
}
DspConfigData;

typedef struct CmdSetLedRequest_t
{
    uint32_t Led;
    uint32_t Value;
}
CmdSetLedRequest;

typedef struct CmdToggleLedRequest_t
{
    uint32_t Led;
}
CmdToggleLedRequest;

typedef struct DspRealTimeDataDetailed_t
{
    uint32_t Entry0;   //DspAmplitude
    int32_t  Entry1;   //DspPhase
    uint32_t Entry2;   //DspFrequency
    uint32_t Entry3;   //DspCurrent
    uint32_t Entry4;   //DspStatus
    uint32_t Entry5;   //DspUnused0
    uint32_t Entry6;   //DspUnused1
}
DspRealTimeDataDetailed;

typedef struct ArmRealTimeDataDetailed_t
{
    uint32_t Entry0;   //ArmMasterState
    uint32_t Entry1;   //ArmTargetAmplitude
    uint32_t Entry2;   //ArmStartFrequency 
    uint32_t Entry3;   //ArmMasterEvents
    uint32_t Entry4;  //ArmAmplitudeRampTime (in ms)
    int32_t  Entry5; //ArmAmpProportionalGain
    int32_t  Entry6; //ArmAmpIntegralGain
    int32_t  Entry7; //ArmAmpDerivativeGain
    int32_t  Entry8; //ArmPhaseProportionalGain
    int32_t  Entry9; //ArmPhaseIntegralGain
    int32_t  Entry10; //ArmPhaseDerivativeGain
}
ArmRealTimeDataDetailed;

#pragma pack (pop)
#endif /* COM_CFG_H_ */
