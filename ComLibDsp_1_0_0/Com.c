/*
 * Com.c
 *
 *  Created on: 18.05.2021
 *      Author: hjouini_3P13713
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "Com.h"
#include "InterCoreLock.h"
#if defined (_TMS320C6X)
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/csl/csl_spinlock.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_mailbox.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Event.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/osal/RegisterIntr.h>
#elif defined (__VXWORKS__)
#include "vxWorks.h"
#include "taskLib.h"
#include "spinlock.h"
#include "cacheLib.h"
#include <sysLib.h>
#include <stdio.h>
#include  <sdLib.h>
#include <errno.h>
#include "MemMap.h"

#define MMU_ATTR (MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | MMU_ATTR_CACHE_GUARDED)

#endif
#define CSL_DSP_MAILBOX2_REGS (0x4883a000U)
#define SOC_MAILBOX2_BASE  (CSL_DSP_MAILBOX2_REGS)
#define MAILBOX_BASE_ADDRESS SOC_MAILBOX2_BASE

#define MAILBOX_USER            (0U)
#define MAILBOX_QUEUE_0         0U
#define MAILBOX_IRQ_NO          (55U)
#define IRQ_XBAR_CPU_ID         CSL_XBAR_IRQ_CPU_ID_DSP1
#define IRQ_XBAR_INST_NO        CSL_XBAR_INST_DSP1_IRQ_55
#define IRQ_XBAR_INDEX          CSL_XBAR_MAILBOX2_IRQ_USER0

#define MAILBOX_MEM       SOC_MAILBOX2_BASE
#define MAILBOX_MEM_SIZE  (1024)

#define SPINLOCK_MEM_SIZE  (0x880U)

#define COM_MAGIC_NUMBER         (0xABADCAFE)
#define COM_COUNTER_START        (1)

#define MAILBOX_USER            (0U)

#define COM_CMD_BUSY 1
#define COM_CMD_FREE 0


#pragma pack ( push, 1)

typedef struct ComCmdData_t
{
    uint32_t CommandId;
    uint32_t Busy;
    uint8_t CommandReqData[COM_CMD_REQUEST_DATA_MAX];
    uint8_t CommandRspData[COM_CMD_RESPONSE_DATA_MAX];
}
ComCmdData;

typedef struct ComData_t
{
    uint32_t MagicNumber;
    uint32_t DspComVersion;
    uint32_t ArmComVersion;
    uint64_t Counter;
    uint32_t DspDataLock;
    uint32_t ArmDataLock;
    uint32_t ArmCmdLock;
    DspInfoData DspInfo;
    DspConfigData DspConfig;
    ComCmdData ArmCommandData;
    DspRealTimeData DspRealTimeData;
    ArmRealTimeData ArmRealTimeData;
}
ComData;

#pragma pack ( pop )


static ComData* comData;
void Mailbox_init();
void Mailbox_deinit();
static inline void Com_flushCache(void* ptr, uint32_t length);
static inline void Com_invalidateCache(void* ptr, uint32_t length);

#if defined (__VXWORKS__)
static uint32_t MailboxSendMessage(uint32_t baseAddr, uint32_t queueId, uint32_t msg);
#endif

#if defined (_TMS320C6X)
static CommandExecutiondelegate dspCommandExecuteCallback = NULL;
static Event_Handle cmdEvent;
static Task_Handle cmdTaskhandle;
static void cmdMailboxIsr(uintptr_t arg);
static Void cmdTask(UArg a0, UArg a1);
#endif

#if defined (__VXWORKS__)
//extern UINT32 mySysRead32(UINT32 addr);
//extern void mySysWrite32(UINT32 addr, UINT32 data);
#define MESSAGE_VALID 0
#define MESSAGE_INVALID 1
#endif

#if defined (_TMS320C6X)
void SetupMailboxInt()
{
    CSL_XbarIrq intrSource;
    OsalRegisterIntrParams_t interruptRegParams;
    HwiP_Handle hwiPHandlePtr;
    intrSource = IRQ_XBAR_INDEX;
    /* XBar configuration for mail box interrupt*/
    CSL_xbarIrqConfigure(IRQ_XBAR_CPU_ID, IRQ_XBAR_INST_NO, intrSource);
    /* Initialize with defaults */
    Osal_RegisterInterrupt_initParams(&interruptRegParams);
    /* Populate the interrupt parameters */
    interruptRegParams.corepacConfig.arg = NULL;
    interruptRegParams.corepacConfig.name = NULL;
    interruptRegParams.corepacConfig.isrRoutine = cmdMailboxIsr;
    interruptRegParams.corepacConfig.priority = 0x20U;
    interruptRegParams.corepacConfig.intVecNum = OSAL_REGINT_INTVEC_EVENT_COMBINER;
    interruptRegParams.corepacConfig.corepacEventNum = 55; /* Corresponds to DSP1_IRQ_55 */
    Osal_RegisterInterrupt(&interruptRegParams, &hwiPHandlePtr);
}
#endif
#if defined (_TMS320C6X)
void Com_init(ComConfig* config)
{
    //Only execute by DSP at start
    Icl_init();
    comData = (ComData*)config->ShmBaseAddress;
    comData->DspDataLock = 0;
    comData->ArmDataLock = 1;
    comData->ArmCmdLock = 2;
    memcpy(&comData->DspInfo, config->dspInfoData, sizeof(comData->DspInfo));
    memcpy(&comData->DspConfig, config->dspConfigData, sizeof(comData->DspConfig));
    dspCommandExecuteCallback = config->dspCommandCallback;
    comData->Counter = COM_COUNTER_START;
    comData->MagicNumber = COM_MAGIC_NUMBER;
    Com_flushCache(comData, sizeof(ComData));
    SetupMailboxInt();
    MailboxReset(MAILBOX_BASE_ADDRESS);
    MailboxConfigIdleMode(MAILBOX_BASE_ADDRESS, 0x2);
    MailboxDisableQueueNotFullInt(MAILBOX_BASE_ADDRESS, MAILBOX_USER, MAILBOX_QUEUE_0);
    MailboxEnableNewMsgInt(MAILBOX_BASE_ADDRESS, MAILBOX_USER,
                            MAILBOX_QUEUE_0);
    MailboxClrNewMsgStatus(MAILBOX_BASE_ADDRESS, MAILBOX_USER, MAILBOX_QUEUE_0);
    MailboxClrQueueNotFullStatus(MAILBOX_BASE_ADDRESS, MAILBOX_USER, MAILBOX_QUEUE_0);
    //Start command task
    Error_Block eb;
    Error_init(&eb);
    cmdEvent = Event_create(NULL, &eb);
    Error_init(&eb);
    comData->DspComVersion = (COM_MODULE_VERSION_MAJ << 16) | (COM_MODULE_VERSION_MIN << 8) | COM_MODULE_VERSION_REV;
    cmdTaskhandle = Task_create(cmdTask, NULL, &eb);
    if (cmdTaskhandle == NULL) 
    {
        System_printf("Cmd Task_create() failed!\n");
    }
    if(comData->DspComVersion != comData->ArmComVersion)
    {
        System_printf("Com version mismatch!!! DSP -> %d  ARM -> %d\n", comData->DspComVersion, comData->ArmComVersion);
    }
}
#endif



#if defined (__VXWORKS__)
void Com_init(ComConfig* config)
{
    comData = (ComData*)config->ShmBaseAddress;
    memset((void*)comData, 0, sizeof(ComData));
    comData->ArmComVersion = (COM_MODULE_VERSION_MAJ << 16) | (COM_MODULE_VERSION_MIN << 8) | COM_MODULE_VERSION_REV;
    Com_flushCache(comData, sizeof(ComData));
}
bool Com_start(ComConfig* config)
{
    comData = (ComData*)config->ShmBaseAddress;
    Mailbox_init();
    Icl_init();
    if(comData->DspComVersion != comData->ArmComVersion)
    {
        printf("Com version mismatch!!! DSP -> %d  ARM -> %d\n", comData->DspComVersion, comData->ArmComVersion);
    }
    return comData->MagicNumber == COM_MAGIC_NUMBER;
}
void Com_deinit()
{
    Mailbox_deinit();
    Icl_deinit();
    comData = NULL;
}
#endif
uint32_t Com_getShmSize()
{
    return sizeof(ComData);
}
//If this function returns successfully the DSP info and config are available for read
bool Com_armWaitForDsp(uint32_t timeoutMs)
{
    bool result = false;
#if defined (__VXWORKS__)
    uint32_t timeCounter = 0;
    printf("Waiting for dsp ...\n");
    do
    {
        Com_invalidateCache(comData, sizeof(ComData));
        if(timeCounter >= (timeoutMs * 1000))
        {
            break;
        }
        Com_delayUs(50000);
        timeCounter += 50000;
    }
    while(comData->MagicNumber != COM_MAGIC_NUMBER);
    result = comData->MagicNumber == COM_MAGIC_NUMBER;
    if(result)
    {
        if(comData->DspComVersion != comData->ArmComVersion)
        {
            printf("Com version mismatch!!! DSP -> %d  ARM -> %d\n", comData->DspComVersion, comData->ArmComVersion);
        }
    }
#endif
    return result;
}


/***************** DSP *******************/
DspInfoData* Com_getDspInfo()
{
    return &comData->DspInfo;
}
DspConfigData* Com_getDspConfig()
{
    return &comData->DspConfig;
}
DspRealTimeData* Com_dspDataBeginWrite()
{
    Icl_lock(comData->DspDataLock);
    return &comData->DspRealTimeData;
}
void Com_dspDataEndWrite()
{
    comData->DspRealTimeData.Valid = true;
    Com_flushCache(&comData->DspRealTimeData, sizeof(comData->DspRealTimeData));
    Icl_unlock(comData->DspDataLock);
}
void Com_dspDataWrite(DspRealTimeData* data)
{
    Icl_lock(comData->DspDataLock);
    memcpy(&comData->DspRealTimeData, data, sizeof(comData->DspRealTimeData));
    comData->DspRealTimeData.Valid = true;
    Com_flushCache(&comData->DspRealTimeData, sizeof(comData->DspRealTimeData));
    Icl_unlock(comData->DspDataLock);
}
bool Com_dspDataRead(DspRealTimeData* data)
{
    bool result = false;
    Icl_lock(comData->DspDataLock);
    Com_invalidateCache(&comData->DspRealTimeData, sizeof(comData->DspRealTimeData));
    if(comData->DspRealTimeData.Valid)
    {
        data->Valid = comData->DspRealTimeData.Valid;
        memcpy(data->Entries, comData->DspRealTimeData.Entries, sizeof(data->Entries));
        result = true;
    }
    Icl_unlock(comData->DspDataLock);
    return result;
}
void Com_dspDataInvalidate()
{
    Icl_lock(comData->DspDataLock);
    comData->DspRealTimeData.Valid = false;
    Com_flushCache(&comData->DspRealTimeData, sizeof(comData->DspRealTimeData));
    Icl_unlock(comData->DspDataLock);
}


/***************** ARM *******************/
ArmRealTimeData* Com_armDataBeginWrite()
{
    Icl_lock(comData->ArmDataLock);
    return &comData->ArmRealTimeData;
}
void Com_armDataEndWrite()
{
    comData->ArmRealTimeData.Valid = true;
    Com_flushCache(&comData->ArmRealTimeData, sizeof(comData->ArmRealTimeData));
    Icl_unlock(comData->ArmDataLock);
}
void Com_armDataWrite(ArmRealTimeData* data)
{
    Icl_lock(comData->ArmDataLock);
    memcpy(&comData->ArmRealTimeData, data, sizeof(comData->ArmRealTimeData));
    comData->ArmRealTimeData.Valid = true;
    Com_flushCache(&comData->ArmRealTimeData, sizeof(comData->ArmRealTimeData));
    Icl_unlock(comData->ArmDataLock);
}
bool Com_armDataRead(ArmRealTimeData* data)
{
    bool result = false;
    Icl_lock(comData->ArmDataLock);
    Com_invalidateCache(&comData->ArmRealTimeData, sizeof(comData->ArmRealTimeData));
    if(comData->ArmRealTimeData.Valid)
    {
        data->Valid = comData->ArmRealTimeData.Valid;
        memcpy(data->Entries, comData->ArmRealTimeData.Entries, sizeof(data->Entries));
        result = true;
    }
    Icl_unlock(comData->ArmDataLock);
    return result;
}
void Com_armDataInvalidate()
{
    Icl_lock(comData->ArmDataLock);
    comData->ArmRealTimeData.Valid = false;
    Com_flushCache(&comData->ArmRealTimeData, sizeof(comData->ArmRealTimeData));
    Icl_unlock(comData->ArmDataLock);
}

bool Com_sendCommand(uint32_t commandId, void* data, uint32_t dataLength)
{
    bool result = false;
    if(dataLength <= COM_CMD_REQUEST_DATA_MAX)
    {
        Icl_lock(comData->ArmCmdLock);
        Com_invalidateCache(&comData->ArmCommandData, sizeof(comData->ArmCommandData));
        if(comData->ArmCommandData.Busy != COM_CMD_BUSY)
        {
            comData->ArmCommandData.Busy = COM_CMD_BUSY;
            comData->ArmCommandData.CommandId = commandId;
            memcpy(comData->ArmCommandData.CommandReqData, data, dataLength);
            Com_flushCache(&comData->ArmCommandData, sizeof(comData->ArmCommandData));
            result = MailboxSendMessage(MAILBOX_BASE_ADDRESS, MAILBOX_QUEUE_0, (uint32_t) dataLength) == MESSAGE_VALID;
        }
        Icl_unlock(comData->ArmCmdLock);
    }
    return result;
}
#if defined (_TMS320C6X)
static Void cmdTask(UArg a0, UArg a1)
{
    while(1)
    {
        Event_pend(cmdEvent, Event_Id_00, Event_Id_NONE, BIOS_WAIT_FOREVER);
        Icl_lock(comData->ArmCmdLock);
        Com_invalidateCache(&comData->ArmCommandData, sizeof(comData->ArmCommandData));
        if(dspCommandExecuteCallback != NULL)
        {
            dspCommandExecuteCallback(comData->ArmCommandData.CommandId, comData->ArmCommandData.CommandReqData);
        }
        comData->ArmCommandData.Busy = COM_CMD_FREE;
        Com_flushCache(&comData->ArmCommandData, sizeof(comData->ArmCommandData));
        Icl_unlock(comData->ArmCmdLock);
    }
}

void cmdMailboxIsr(uintptr_t arg)
{
    uint32_t gMsg;
    uint32_t gMsgStatus = MailboxGetMessage(MAILBOX_BASE_ADDRESS, MAILBOX_QUEUE_0, (uint32_t *) &gMsg);
    Event_post(cmdEvent, Event_Id_00);
    /* clear mlb intr */
    MailboxClrNewMsgStatus(MAILBOX_BASE_ADDRESS, MAILBOX_USER, MAILBOX_QUEUE_0);
}
#endif

static inline void Com_invalidateCache(void* ptr, uint32_t length)
{
#if defined (_TMS320C6X)
    Cache_inv(ptr, length, Cache_Type_ALL, TRUE);
#endif
#if defined (__VXWORKS__)
    cacheInvalidate(DATA_CACHE, ptr, length);
#endif
}
static inline void Com_flushCache(void* ptr, uint32_t length)
{
#if defined (_TMS320C6X)
    Cache_wb(ptr, length, Cache_Type_ALL, TRUE);
#endif
#if defined (__VXWORKS__)
    cacheFlush(DATA_CACHE, ptr, length);
#endif
}
#if defined (__VXWORKS__)
void Com_delayUs(uint32_t delayUs)
{
    taskDelay((int)((delayUs) * sysClkRateGet()) / 1000000);
}
#endif

#define MAILBOX_MESSAGE(n)                                                                                 ((uint32_t)0x40U + ((n) * 4U))
#define MAILBOX_FIFOSTATUS(n)                                                                              ((uint32_t)0x80U + ((n) * 4U))
#define MAILBOX_MSGSTATUS(n)                                                                               ((uint32_t)0xc0U + ((n) * 4U))
#define MAILBOX_IRQSTATUS_RAW(n)                                                                           ((uint32_t)0x100U + ((n) * 16U))
#define MAILBOX_IRQSTATUS_CLR(n)                                                                           ((uint32_t)0x104U + ((n) * 16U))
#define MAILBOX_IRQENABLE_CLR(n)                                                                           ((uint32_t)0x10cU + ((n) * 16U))
#define MAILBOX_IRQENABLE_SET(n)                                                                           ((uint32_t)0x108U + ((n) * 16U))

#if defined (__VXWORKS__)
static uint32_t mailboxBaseaddr = NULL;
void Mailbox_init()
{
#if defined (_WRS_KERNEL)
	    mailboxBaseaddr = (uint32_t)MEM_MAP(MAILBOX_MEM, MAILBOX_MEM_SIZE);
#else if defined (__VXWORKS__)
	SD_ID sd;
	    char memName[32];
	    snprintf(memName, 32, "/ComData_%x", MAILBOX_MEM);
	    uint32_t err = 0;
	    /* Create the R/W shared buffer */
	    if ((sd = sdOpen(memName, 0, OM_CREATE, MAILBOX_MEM_SIZE, MAILBOX_MEM, SD_ATTR_RW | SD_CACHE_OFF, (void **)&mailboxBaseaddr)) == SD_ID_NULL)
	    {
	        err = errno;
	        printf("MEM_MAP failed. 0x%x\n", err);
	    }

#endif
}
void Mailbox_deinit()
{
    if(mailboxBaseaddr != NULL)
    {
#if defined (_WRS_KERNEL)
    	MEM_UNMAP((void*)mailboxBaseaddr, MAILBOX_MEM_SIZE);
#endif
        mailboxBaseaddr = NULL;
    }
}
static uint32_t MailboxSendMessage(uint32_t baseAddr, uint32_t queueId, uint32_t msg)
{
    uint32_t fifoFull;
    uint32_t retval = MESSAGE_INVALID;
    if(mailboxBaseaddr != NULL)
    {
        /* Read the FIFO Status */
        fifoFull = *(uint32_t*)(mailboxBaseaddr + MAILBOX_FIFOSTATUS(queueId));
        if (fifoFull == 0U)
        {
            /* FIFO not full write msg */
            *(uint32_t*)(mailboxBaseaddr + MAILBOX_MESSAGE(queueId)) = msg;
            //mySysWrite32(mailboxBaseaddr + MAILBOX_MESSAGE(queueId), msg);
            retval = MESSAGE_VALID;
        }
        else
        {
            retval = MESSAGE_INVALID;
        }
    }
    return retval;
}
#endif
