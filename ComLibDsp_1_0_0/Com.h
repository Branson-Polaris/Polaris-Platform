/*
 * Com.h
 *
 *  Created on: 18.05.2021
 *      Author: hjouini_3P13713
 */

#ifndef COM_H_
#define COM_H_

#include "Com_Cfg.h"

#define COM_MODULE_VERSION_MAJ 1
#define COM_MODULE_VERSION_MIN 0
#define COM_MODULE_VERSION_REV 0

#pragma pack ( push, 1)

typedef struct DspRealTimeData_t
{
    uint32_t Valid;
    uint32_t Entries[COM_DSP_DATA_LENGTH];
}
DspRealTimeData;

typedef struct ArmRealTimeData_t
{
    uint32_t Valid;
    uint32_t Entries[COM_ARM_DATA_LENGTH]; // DSS: the sizes can be the same 4 or 7 words, let's start with 4
}
ArmRealTimeData;

#pragma pack ( pop )

typedef void (*CommandExecutiondelegate) (uint32_t commandId, uint8_t* commandRequestData);

typedef struct ComConfig_t
{
    uint32_t ShmBaseAddress;
    DspInfoData* dspInfoData;
    DspConfigData* dspConfigData;
    CommandExecutiondelegate dspCommandCallback;
}
ComConfig;


void Com_init(ComConfig* config);
void Com_deinit(void);
bool Com_start(ComConfig* config);
bool Com_armWaitForDsp(uint32_t timeoutMs);
DspInfoData* Com_getDspInfo();
DspConfigData* Com_getDspConfig();
uint32_t Com_getShmSize();
void Com_delayUs(uint32_t delayUs);

bool Com_sendCommand(uint32_t commandId, void* data, uint32_t dataLength);

DspRealTimeData* Com_dspDataBeginWrite();
void Com_dspDataEndWrite();
void Com_dspDataWrite(DspRealTimeData* data);
bool Com_dspDataRead(DspRealTimeData* data);
void Com_dspDataInvalidate();

ArmRealTimeData* Com_armDataBeginWrite();
void Com_armDataEndWrite();
void Com_armDataWrite(ArmRealTimeData* data);
bool Com_armDataRead(ArmRealTimeData* data);
void Com_armDataInvalidate();

#endif /* COM_H_ */
