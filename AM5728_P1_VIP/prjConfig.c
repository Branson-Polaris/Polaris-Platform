/* prjConfig.c - dynamically generated configuration file */


/*
GENERATED: Wed Oct 13 13:35:25 +0800 2021
DO NOT EDIT - file is regenerated whenever the project changes.
This file contains the non-BSP system initialization code
to Create a bootable VxWorks image (custom configured).
*/


/* includes */

#include <vxWorks.h>
#include <prjParams.h>
#include <adrSpaceLib.h>
#include <applUtilLib.h>
#include <auxv.h>
#include <boardLib.h>
#include <cacheLib.h>
#include <classLib.h>
#include <condVarLib.h>
#include <cplusLib.h>
#include <dataCollectorLib.h>
#include <dbgLib.h>
#include <dosFsLib.h>
#include <drv/erf/erfLib.h>
#include <drv/manager/device.h>
#include <drv/xbd/xbd.h>
#include <edrLib.h>
#include <endLib.h>
#include <envLib.h>
#include <etherMultiLib.h>
#include <eventLib.h>
#include <excLib.h>
#include <fioLib.h>
#include <fsEventUtilLib.h>
#include <fsMonitor.h>
#include <ftpLib.h>
#include <hashLib.h>
#include <hookLib.h>
#include <hostLib.h>
#include <hrFsLib.h>
#include <hwif/drv/sio/vxbSioUtil.h>
#include <hwif/util/vxbDmaBufLib.h>
#include <hwif/util/vxbIsrDeferLib.h>
#include <hwif/util/vxbParamLib.h>
#include <hwif/vxBus.h>
#include <intLib.h>
#include <ioLib.h>
#include <iosLib.h>
#include <iosScLib.h>
#include <jobQueueLib.h>
#include <loadElfLib.h>
#include <logLib.h>
#include <lstLib.h>
#include <miiBus.h>
#include <moduleLib.h>
#include <msgQLib.h>
#include <mux2Lib.h>
#include <muxLib.h>
#include <net/mbuf.h>
#include <net/utils/ifconfig.h>
#include <netBufLib.h>
#include <netDrv.h>
#include <netLib.h>
#include <netdb.h>
#include <objLib.h>
#include <pipeDrv.h>
#include <private/adrSpaceLibP.h>
#include <private/condVarLibP.h>
#include <private/coprocLibP.h>
#include <private/cpcLibP.h>
#include <private/cplusLibP.h>
#include <private/dbgLibP.h>
#include <private/eventDefsP.h>
#include <private/eventPointLibP.h>
#include <private/eventPointStubLibP.h>
#include <private/excLibP.h>
#include <private/fioLibP.h>
#include <private/ftpLibP.h>
#include <private/isrLibP.h>
#include <private/jobLibP.h>
#include <private/kernelBaseLibP.h>
#include <private/kernelLibP.h>
#include <private/ledLibP.h>
#include <private/logLibP.h>
#include <private/memPartLibP.h>
#include <private/moduleHookLibP.h>
#include <private/offsetsP.h>
#include <private/pgMgrLibP.h>
#include <private/pgPoolLibP.h>
#include <private/pgPoolPhysLibP.h>
#include <private/pgPoolVirtLibP.h>
#include <private/poolLibP.h>
#include <private/qLibP.h>
#include <private/randomNumGenP.h>
#include <private/rtpDbgCmdLibP.h>
#include <private/rtpLibP.h>
#include <private/rtpSigLibP.h>
#include <private/sdLibP.h>
#include <private/seqDrvP.h>
#include <private/shellCmdP.h>
#include <private/shellLibP.h>
#include <private/sigLibP.h>
#include <private/svDataCollectorLibP.h>
#include <private/sysDbgLibP.h>
#include <private/syscallLibP.h>
#include <private/taskMemLibP.h>
#include <private/timerLibP.h>
#include <private/tipLibP.h>
#include <private/tlsLibP.h>
#include <private/trgLibP.h>
#include <private/vmLibP.h>
#include <private/vxMemProbeLibP.h>
#include <private/workQLibP.h>
#include <private/wvFileUploadPathLibP.h>
#include <private/wvUploadPathP.h>
#include <ptyDrv.h>
#include <rBuffLib.h>
#include <rawFsLib.h>
#include <rebootLib.h>
#include <remLib.h>
#include <romfsLib.h>
#include <rtpLib.h>
#include <sdLib.h>
#include <selectLib.h>
#include <semLib.h>
#include <shellConfigLib.h>
#include <shellInterpLib.h>
#include <shellLib.h>
#include <shlLib.h>
#include <sigLib.h>
#include <sigevent.h>
#include <sockLib.h>
#include <stdio.h>
#include <string.h>
#include <subsys/int/vxbIntLib.h>
#include <subsys/int/vxbIsrHandler.h>
#include <symLib.h>
#include <sysLib.h>
#include <sysSymTbl.h>
#include <syscallLib.h>
#include <syscallTbl.h>
#include <sysctlLib.h>
#include <syslog.h>
#include <taskHookLib.h>
#include <taskLib.h>
#include <tickLib.h>
#include <time.h>
#include <timerDev.h>
#include <timexLib.h>
#include <trgLib.h>
#include <ttyLib.h>
#include <tyLib.h>
#include <unistd.h>
#include <unldLib.h>
#include <usbd.h>
#include <usrLib.h>
#include <usrNetIoctlScLib.h>
#include <vmLib.h>
#include <vrfsLib.h>
#include <vxAtomicLib.h>
#include <vxLib.h>
#include <vxdbgLibInit.h>
#include <wdLib.h>
#include <wvLib.h>
#include <wvTmrLib.h>


/* imports */

IMPORT char etext [];                   /* defined by loader */
IMPORT char end [];                     /* defined by loader */
IMPORT char edata [];                   /* defined by loader */

/* forward declarations */

IMPORT void mmcPreInit(char *);
IMPORT void sdPreInit(char *);
IMPORT void usrSioIoctlLibInit (void);
IMPORT STATUS adrSpaceShellCmdInit (void);
IMPORT void usrBoardLibInit (void );
extern STATUS cacheDma32PartInit (void);
IMPORT void usrAimCpuInit (void);
IMPORT void vxCpuInit (void); IMPORT VOID vxMmuEarlyInit (UINT32 baseAddr, UINT32 linkAddr, UINT32 length); IMPORT void excVecBaseSet (UINT32 base);
IMPORT STATUS dbgShellCmdInit ();
IMPORT void vxbClkLibInit(void);
IMPORT STATUS iosDevNullInit (void);
IMPORT STATUS usrFsShellCmdInit ();
IMPORT STATUS vxbDmaLibInit (void);
IMPORT STATUS eepromDrv (void);
IMPORT void endEtherHdrInit (void);
IMPORT STATUS evdevInit (UINT32 msgNum);
IMPORT STATUS eventPointLibInit (void);
IMPORT STATUS eventPointStubLibInit (void);
IMPORT void usrFdtInit (void *, int);
IMPORT STATUS vxbGpioLibInit (void);
extern void hostnameSysctlSetup (void);
IMPORT void randomEntropyInterruptAddInit (unsigned int rounds);
IMPORT STATUS vxbIntLibInit (UINT32);
IMPORT STATUS vxbIsrHandlerInit (UINT32, UINT32);
extern STATUS vxstdioKernInit (void);
extern STATUS logInit (int, int, UINT);
extern void miiBusMonitorTaskInit (void);
extern void miiBusLibInit (void);
IMPORT STATUS mmanLibInit (void);
extern STATUS moduleShellCmdInit (void);
extern void usrHostnameSetup (const char * defaultTargetHostname);
IMPORT STATUS objInfoInit (void);
IMPORT void usrOsmInit (UINT32, UINT32);
IMPORT STATUS vxbPhyLibInit(void);
IMPORT STATUS vxbPinMuxLibInit (void);
IMPORT void pmapInit (void);
extern STATUS umaskLibInit (int);
extern STATUS pxUserGroupLibInit (void);
IMPORT STATUS vxbPdLibInit(void);
IMPORT void usrKernelIntStkProtect (void);
IMPORT void usrKernelIntStkProtectNonCore0 (void);
IMPORT void usrRtpAppInit (void);
IMPORT void rtpIoLimitsInit (void);
extern STATUS usrRtpLibInit (void);
IMPORT STATUS rtpShowShellCmdInit (void);
extern STATUS rtpSymLibInit (void);
IMPORT STATUS envScInit (void);
IMPORT STATUS windScInit (void);
IMPORT void mmanScLibInit (void);
extern void usrPosixScInit (void);
IMPORT void sdScInit (void);
IMPORT void shlScLibInit (void);
IMPORT STATUS sockScLibInit (void);
IMPORT STATUS sysctlScLibInit (void);
IMPORT void secHashMd5OpensslInit(void);
IMPORT void secHashSha1OpensslInit(void);
IMPORT void secHashSha256OpensslInit(void);
IMPORT void secHashWhirlpoolOpensslInit(void);
IMPORT void semBCreateLibInit (void);
IMPORT void semCCreateLibInit (void);
IMPORT void semMCreateLibInit (void);
IMPORT STATUS sdShowShellCmdInit (void);
extern STATUS sigeventLibInit (void);
IMPORT void usrStacktraceInit(void);
extern char * startupScriptFieldSplit (char * field);
IMPORT STATUS stdioShowInit (void);
IMPORT STATUS symShellCmdInit ();
extern void syslogLibInit (void);
IMPORT void taskCreateLibInit (void);
IMPORT STATUS taskShellCmdInit ();
IMPORT void randomEntropyAddSwitchHookInit (unsigned int rounds);
IMPORT STATUS tyLibInit (int xoffThresh, int xonThresh, size_t wrtThresh, BOOL monTrapDisable);
extern STATUS unloadShellCmdInit (void);
IMPORT STATUS usrUsb2MseInit (void);
IMPORT STATUS usrUsb2MscInit (void);
IMPORT void usbHstClassInit (void);
IMPORT STATUS usbInit (void);
extern void usrAppInit (void);
IMPORT STATUS vmShowShellCmdInit (void);
IMPORT STATUS vxbAuxClkLibInit (void);
IMPORT STATUS vxbSysClkLibInit (void);
IMPORT STATUS vxbTimestampLibInit (void);
IMPORT STATUS vxIpiLibInit (void);
IMPORT void vxmux_mux_mblk_init (void);


/* BSP_STUBS */



/* configlettes */

#include <sysComms.c>
#include <armGenTimerCfg.c>
#include <armGicCfg.c>
#include <armMonitorStub.c>
#include <edrDefaultPolicy.c>
#include <edrNonFatalPolicy.c>
#include <edrStub.c>
#include <intrinsics.c>
#include <ipcom_config.c>
#include <ipcom_ipd_config.c>
#include <ipcrypto_config.c>
#include <ipnet_config.c>
#include <ipnet_radvd_config.c>
#include <ipssl_config.c>
#include <iptcp_config.c>
#include <memLayoutCheck.c>
#include <omap3TimerCfg.c>
#include <sysClkInit.c>
#include <usrAdjustDtb.c>
#include <usrAimCpu.c>
#include <usrBanner.c>
#include <usrBoardLibInit.c>
#include <usrBootLine.c>
#include <usrBreakpoint.c>
#include <usrCache.c>
#include <usrCoprocs.c>
#include <usrCplus.c>
#include <usrDosfs.c>
#include <usrDwc3UsbInit.c>
#include <usrFdt.c>
#include <usrFtp.c>
#include <usrHostnameSetup.c>
#include <usrHrfs.c>
#include <usrHwSysctl.c>
#include <usrIo.c>
#include <usrIsrDefer.c>
#include <usrKernel.c>
#include <usrKernelStack.c>
#include <usrMemDesc.c>
#include <usrMmuInit.c>
#include <usrNetApplUtil.c>
#include <usrNetBoot.c>
#include <usrNetDaemon.c>
#include <usrNetEndLib.c>
#include <usrNetHostTblCfg.c>
#include <usrNetIfconfig.c>
#include <usrNetIoctlScLib.c>
#include <usrNetM2ifLib.c>
#include <usrNetRemoteCfg.c>
#include <usrNetSysctl.c>
#include <usrOsm.c>
#include <usrPmap.c>
#include <usrPosixSc.c>
#include <usrRomfs.c>
#include <usrRtpAppInitBootline.c>
#include <usrRtpBaseLib.c>
#include <usrScript.c>
#include <usrSecureConfig.c>
#include <usrSemLib.c>
#include <usrSerial.c>
#include <usrShell.c>
#include <usrSioIoctlLib.c>
#include <usrSmcProtocol.c>
#include <usrSmp.c>
#include <usrStacktrace.c>
#include <usrStandalone.c>
#include <usrStartup.c>
#include <usrStatTbl.c>
#include <usrSysSymTbl.c>
#include <usrSysctl.c>
#include <usrSyslog.c>
#include <usrTextProtect.c>
#include <usrTip.c>
#include <usrTty.c>
#include <usrUsb2MscInit.c>
#include <usrUsbDebug.c>
#include <usrUsbInit.c>
#include <usrVxbTimerSys.c>
#include <usrVxdbg.c>
#include <usrWindview.c>


/* user configlettes */



/******************************************************************************
*
* usrKernelExtraInit - Extended kernel facilities
*/

void usrKernelExtraInit (void)
    {
                                        /* This component includes the hash library. This library supports the creation and maintenance of a chained hash table. Hash tables efficiently store hash nodes for fast access. They are frequently used for symbol tables, or other name-to-identifier functions. A chained hash table is an array of singly-linked list heads, with one list head per element of the hash table. During creation, a hash table is passed two user-definable functions, the hashing function, and the hash node comparator. The hashTblCreate( ) function creates a hash table. The hashTblInit( ) function initializes a hash table. The hashTblDelete() function deletes a hash table. The hashTblTerminate() function terminates a hash table. The hashTblDestroy() function destroys a hash table. The hashTblPut() function puts a hash node into the specified hash table. The hashTblFind() function finds a hash node that matches the specified key. The hashTblRemove() function removes a hash node from a hash table. The hashTblEach() function calls a function for each node in a hash table. The hashFuncIterScale() function provides an iterative scaling hashing function for strings. The hashFuncModulo() function provides a hashing function using a remainder technique. The hashFuncMultiply() function is a multiplicative hashing function. The hashKeyCmp() function compares keys as 32-bit identifiers. The hashKeyStrCmp() function compares keys based on strings they point to. */
    excSigLibInit();                    /* This component enables signal generation on an exception. */
    sigInit (POSIX_SIGNAL_MODE);        /* This component provides the sigLib library. This library provides the signal interfaces in the RTP environment. The signal model in user-mode is designed to follow the POSIX process model. Signals alter the flow of control of tasks by communicating asynchronous events within or between task contexts. Using the APIs provided by this library, signals can be sent from an RTP task to either another RTP or a public task in another RTP. Signals can be sent to an RTP using the kill() or raise() functions, and will be caught by any task in that RTP which has unmasked that signal. Signals can also be sent to specific tasks in the current or another RTP using the taskKill() function. Tasks that receive signals can either be waiting synchronously for the signal, or can have their signal mask setup to unblock that signal. If there is no such task waiting for the signal, the signal remains pended in the RTP and is delivered when one such task becomes available. */
    sigeventLibInit ();                 /* This component provides kernel signal event support. This is required for SIGEV_THREAD support in an RTP. */
                                        /* Includes the POSIX directory utilities. */
    pxUserGroupLibInit();               /* This component adds support for POSIX users and groups in the kernel environment. */
    clockLibInit (HIGH_RES_POSIX_CLOCK, POSIX_CLOCK_TIMER); /* This component includes support for POSIX clocks. */
    timerLibInit (TIMER_SETTIME_RESTRICTED); /* This component provides support for POSIX timers. */
    timerOpenInit ();                   /* This component provides the open/close/unlink interfaces for timers. */
    jobQueueLibInit();                  /* Includes the jobQueueLib library. It provides a prioritized work deferral mechanism. */
    jobQueueUtilInit ();                /* This component supports clean termination of job queue processing, and job queue and standard job pool deletion. */
    syscallHookLibInit ();              /* This component includes hook functions that can be called on system calls. */
    symLibInit ();                      /* Set of routines to manipulate symbols and symbol tables */
    }



/******************************************************************************
*
* usrNetMib2Init - Initialize MIB2
*/

void usrNetMib2Init (void)
    {
    usrNetM2IfStart ();                 /* MIB2 Variables for Interface Layer */
    }



/******************************************************************************
*
* usrNetworkInit0 - Initialize the network subsystem for drivers
*/

void usrNetworkInit0 (void)
    {
    netBufLibInitialize (NETBUF_LEADING_CLSPACE_DRV); /* Network Buffer Library */
    netBufPoolInit ();                  /* netBufLib Generic Pool */
    linkBufPoolInit ();                 /* Network Buffer Library */
    vxmux_null_buf_init ();             /* Minimal clusterless network pool implementation for IPCOM */
    usrNetDaemonInit(NET_JOB_NUM_CFG, NET_TASK_DEFAULT_PRIORITY, NET_TASK_OPTIONS, NET_TASK_STACKSIZE); /* This component includes support for the network daemon. The network daemon, tNet0, performs network driver and network protocol processing for the VxWorks network stack. */
    usrNetMib2Init ();                  /* Initialize MIB2 */
    muxCommonInit();                    /* MUX common support (all protocol and device styles) */
    muxLibInit();                       /* Support muxBind() protocols and their APIs */
    mux2LibInit();                      /* Support mux2Bind() protocols and their APIs */
    vxmux_mux_mblk_init ();             /* MUX private support for M_BLK/Ipcom_pkt conversion */
    mux2OverEndInit();                  /* Support mux2Bind() protocols over END-style devices */
    endEtherHdrInit ();                 /* M_BLK ethernet/802.3 header build and parse */
    endLibInit();                       /* Support for END-style network devices. */
    }



/******************************************************************************
*
* usrIosCoreInit - core I/O system
*/

void usrIosCoreInit (void)
    {
    iosPathResLegacyInit (DEV_NAME_POLICY); /* The traditional VxWorks handling of pathnames and devices. Note that support for this option will be removed at some point in the future. */
    vrfsInit ();                        /* File System which exports the Core I/O device table */
    iosInit (NUM_DRIVERS, NUM_FILES, "/null"); /* Basic IO system component */
    iosPathLibInit ();                  /* File System IO component without removable device support */
    iosRmvLibInit ();                   /* Removable IO component */
    iosPxLibInit ();                    /* POSIX IO component */
    iosDevNullInit ();                  /* Create /dev/null data sink */
                                        /* Miscellaneous IO component */
    selectInit (NUM_FILES);             /* This provides the kernel selectLib library which includes select() and related functions. */
    usrIsrDeferInit ();                 /* This component provides the ISR defferal library used by interrupt service routines to defer interrupt processing from interrupt context to task context. Device drivers use this library by allocating a deferral task, and then enqueueing work on the task's work queue. This library is designed to work with VxBus-compliant device drivers. */
    tyLibInit (TYLIB_XOFF_PCNT, TYLIB_XON_PCNT, TYLIB_WRT_THRESHLD, TYLIB_MON_TRAP_DISABLE); /* Allows communication between processes */
    ttyLibInit (NULL);                  /* Provides terminal device access to serial channels. */
    coprocLibInit();                    /* Generalized coprocessor support. */
    erfEventTaskOptionsSet (ERF_EVENT_TASK_OPTIONS); /* Provides parameter for change options of event task */
    erfLibInit (ERF_MAX_USR_CATEGORIES, ERF_MAX_USR_TYPES, ERF_TASK_STACK_SIZE, ERF_MAX_EVENT_QUEUE_SIZE); /* Provides support for the event reporting framework for use by other libraries. */
    eepromDrv ();                       /* This component provides the EEPROM driver, which attaches the EEPROM device to standard I/O streams. */
    }



/******************************************************************************
*
* usrIosExtraInit - extended I/O system
*/

void usrIosExtraInit (void)
    {
    jobTaskLibInit (JOB_TASK_STACK_SIZE, JOB_TASK_PRIORITY); /* This component provides task-level work deferral. */
    excInit (MAX_ISR_JOBS, EXC_TASK_PRIORITY); /* This component includes the excLib facility. This generic exception handling facility includes the following functions: excInit(), which initializes the exception handling package; excJobAdd(), which requests a task-level function call from the interrupt level; excJobAddDefer(), which requests a deferred task-level function call; and excHookAdd(), which specifies a function to be called with exceptions. */
    syslogLibInit ();                   /* This component provides the system logging facility. The syslogLib facility can be configured to log messages before it is initialized. These messages are stored in static memory until initialization is complete and the system logger has started (tLogTask). As the POSIX clocks facility is also not yet initialized when log messages are written to static memory, the timestamp assigned to these messages is not accurate (it starts from 1970-01-01T00:00:00.000000Z). */
    logInit (consoleFd, MAX_LOG_MSGS, LOG_TASK_PRIORITY); /* This component provides the logLib library. This library handles message logging. It is usually used to display error messages on the system console, but such messages can also be sent to a disk file or printer. The logMsg() and logTask() functions are the basic components of the logging system. The logMsg() function has the same calling sequence as printf(), but instead of formatting and outputting the message directly, it sends the format string and arguments to a message queue. The logTask() task waits for messages on this message queue. It formats each message according to the format string and arguments in the message, prepends the ID of the sender, and writes it on one or more file descriptors that have been specified as logging output streams (by logInit() or subsequently set by logFdSet() or logFdAdd()). */
    pipeDrv (PIPE_MAX_OPEN_FDS);        /* This component enables the use of pipes. Pipes provide an alternative interface to the message queue facility that goes through the VxWorks I/O system. Pipe devices are managed by the pipeDrv virtual I/O device, and use the kernel message queue facility to bear the actual message traffic. Tasks write messages to pipes, which are then read by other tasks. This allows you to implement a client-server model of intertask communications. For more information about pipes, see the ioLib entry in the VxWorks User Space COREOS API Reference, and the pipeDrv entry in the VxWorks Kernel COREOS API Reference. */
    fioLibInit ();                      /* This component provides non-ANSI standard I/O routines such as oprintf, fdprintf and so forth. */
    devInit (DEVICE_MANAGER_MAX_NUM_DEVICES); /* Device Manager */
    xbdInit ();                         /* This component includes support for an extended block device. */
    fsMonitorInit ();                   /* This component includes the file system monitor. */
    fsEventUtilLibInit ();              /* This component includes the file system event utilities. */
    usrDosfsInit (DOSFS_DEFAULT_MAX_FILES, DOSFS_DEFAULT_CREATE_OPTIONS); /* MS-DOS-Compatible File System: dosFs main module */
    dosFsCacheLibInit (DOSFS_DEFAULT_DATA_DIR_CACHE_SIZE, DOSFS_DEFAULT_FAT_CACHE_SIZE, DOSFS_CACHE_BACKGROUND_FLUSH_TASK_ENABLE); /* Dos FS cache size is set on per-device basis */
    dosFsShowInit();                    /* Includes the show routines for Dos FS provided by the dosFsShow library. */
    usrHrfsInit (HRFS_DEFAULT_MAX_BUFFERS, HRFS_DEFAULT_MAX_FILES, HRFS_DEFAULT_COMMIT_TASK_PRIORITY); /* Highly Reliable File System */
    rawFsInit (NUM_RAWFS_FILES, NUM_RAWFS_BLOCKS); /* Raw block device file system interface */
    ptyDrv ();                          /* Allows communication between processes */
    romfsFsInit (ROMFS_MAX_OPEN_FILES); /* Includes a driver for read-only memory-based file system. It is initialized at runtime. */
    usrRomfsConfig ();                  /* Includes a read-only memory-based file system. */
    eepromDrv ();                       /* This component provides the EEPROM driver, which attaches the EEPROM device to standard I/O streams. */
    usrUsb2MscInit ();                  /* USB GEN2 Mass Storage Driver Initialization */
    usrUsb2MseInit ();                  /* USB GEN2 Mouse Driver Initialization */
    usrBootLineParse ((char *)BOOT_LINE_ADRS); /* This component provides support to parse some boot device configuration information. */
    evdevInit (EVDEV_MSG_NUM);          /* Includes the event devices core library. */
    mmcPreInit(MMC_DEVNAME);            /* MMC card driver */
    sdPreInit(SD_DEVNAME);              /* SD card driver */
    }



/******************************************************************************
*
* usrShowInit - Enable object show routines
*/

void usrShowInit (void)
    {
    taskShowInit ();                    /* This component provides functions to show task-related information, such as task status, register values, and so forth. Task information is crucial as a debugging aid and user-interface convenience during the development cycle of an application. The taskShow() and taskRegsShow() functions are used to display task information. It is important to keep in mind that tasks may change their state or even get deleted between the time the information is gathered and the time it is utilized. Information provided by these functions should therefore be viewed as a snapshot of the system, and not relied upon unless the task is consigned to a known state, such as suspended. */
    classShowInit ();                   /* This component provides the classShow library which provides functions to show class-related information. */
    memShowInit ();                     /* This component includes the memShow library. This library contains memory partition information display functions. The memShow() function shows blocks and statistics for the current heap partition. The memPartShow() function shows available and allocated memory in the specified partition. */
    taskHookShowInit ();                /* This component provides support for the task hook show functions: taskHookShowInit() initializes the task hook show facility. taskCreateHookShow() shows the list of task create functions. taskDeleteHookShow() shows the list of task delete functions. taskSwitchHookShow() shows the list of task switch functions. */
    semShowInit ();                     /* This component includes the semShow library in your project. This library provides functions to show semaphore statistics, such as semaphore type, semaphore queuing method, tasks pended, and so forth. Functions in this library are meant to be used as debugging aids that display semaphore information to standard output. Due to the dynamic nature of semaphore operations, the information displayed may no longer be accurate by the time it is provided. */
    condVarShowInit ();                 /* This component provides the conVarShow() function. This function can be used to show information about a conditional variable. */
    msgQShowInit ();                    /* This component includes the msgQShow library in your project. This library provides functions to show message queue statistics, such as the task queuing method, messages queued, and receivers blocked. The msgQShowInit() function links the message queue show facility into the VxWorks system. It is called automatically when you include this component in your project. The msgQShow() function displays information about message queues. */
    wdShowInit ();                      /* This component provides the wdShow library. This library provides functions to show watchdog statistics, such as watchdog activity, a watchdog function, and so forth. The wdShowInit() function links the watchdog show facility into the VxWorks system. It is called automatically when this component is included in your project. The wdShow() function shows information about a watchdog. */
    symShowInit ();                     /* Routines to display information about symbols and symbol tables */
    vmShowInit ();                      /* This component provides support for the virtual memory show routines for the shell C interpreter. */
                                        /* This component provides functions to check for available floating-point registers and to print their contents. */
    trgShowInit ();                     /* This component provides the trgShow library. This library provides routines to show event triggering information, such as list of triggers, associated actions, trigger states, and so on. The routine trgShowInit() links the triggering show facility into the VxWorks system. It is called automatically when this component is included. */
    rBuffShowInit ();                   /* Displays rBuff information and statistics about ring buffer performance. Optional and only available if you include RBUFF. */
    stdioShowInit ();                   /* stdio show routine */
                                        /* This component provides the handleShow library. This library provides functions to show handle information. */
    timerShowInit();                    /* This component includes a utility that allows the user to display a snap shot of the selected timer. It provides the timer_show() function which shows information on a specified timer. It requires INCLUDE_POSIX_TIMERS. */
    adrSpaceShowInit();                 /* This component includes the adrSpaceShow() show function for the C interpreter. It can be used to display an overview of the address space usage at the time of the call. */
    pgMgrShowInit();                    /* Page manager show routines: display information on page managers. */
    pgPoolShowInit();                   /* Generic page pool allocator show routines: display information on page pools. */
    rtpShowInit ();                     /* This component provides support for the rtpMemShow(), rtpShow(), and rtpHookShow() functions. It is also a requirement for syscallShow(). This component, along with INCLUDE_DISK_UTIL, provide useful shell functions. */
    sdShowInit ();                      /* This component adds sdShow() to display information on shared data regions. It is included in the BUNDLE_RTP_DEVELOP bundle. */
    shlShowInit ();                     /* This component adds show functions to display information about shared libraries in RTPs. It is included in the BUNDLE_RTP_DEVELOP bundle. */
    coprocShowInit ();                  /* This component includes a function to show the task coprocessor registers. */
    }



/******************************************************************************
*
* usrWindviewInit - 
*/

void usrWindviewInit (void)
    {
    windviewConfig ();                  /* Initialize and control event logging of the System Viewer. */
    wvTmrRegister ((UINTFUNCPTR) seqStamp, (UINTFUNCPTR) seqStampLock, (FUNCPTR) seqEnable, (FUNCPTR) seqDisable, (FUNCPTR) seqConnect, (UINTFUNCPTR) seqPeriod, (UINTFUNCPTR) seqFreq); /* Supports sequential timestamping. This is recommended if you are new to the System Viewer. */
    rBuffLibInit ();                    /* System Viewer ring of buffers for event logging */
    wvFileUploadPathLibInit ();         /* Initialize the path for the file upload. */
    }



/******************************************************************************
*
* usrLoaderInit - The target loader initialization sequence.
*/

void usrLoaderInit (void)
    {
    moduleLibInit ();                   /* This component includes the support library for module entities. */
    loadElfInit ();                     /* This component includes the ELF object support for the DKM and RTP loader. */
    loadLibInit (STORE_ABS_SYMBOLS);    /* This component provides support to download modules to running targets. */
    unldLibInit ();                     /* This component enables removal of dynamically-loaded modules. */
    moduleHookLibInit ();               /* This component includes pluggable hooks to extend the loader/unloader behavior. */
    }



/******************************************************************************
*
* usrSymTblInit - Enable onboard symbol tables
*/

void usrSymTblInit (void)
    {
    usrSysSymTblInit ();                /* initialize system symbol table */
    usrStandaloneInit ();               /* Preferred method if not booting from the network */
    usrStatTblInit ();                  /* Table of error strings for perror() */
    rtpSymLibInit();                    /* This component provides symbol table support for RTPs. To support debugging, this feature allows you to register symbols during or after you load any RTPs and shared libraries. */
    }



/******************************************************************************
*
* usrShellCmdInit - The kernel shell commands initialization sequence
*/

void usrShellCmdInit (void)
    {
    taskShellCmdInit ();                /* This component provides shell commands related to tasks: task, task info, task spawn, task stack, task delete, task default, task regs, task suspend, task resume, task hooks, task stop, task wait. Aliases: edrs (edr show), edrc (edr clear). */
    dbgShellCmdInit ();                 /* This component provides shell commands related to debugging: task trace, task continue, task stepover, task step, mem list, bp, dprintf. Aliases: l (mem list), bd (bp -u), bdall (bp -u *), b (bp), bi (bp -v), dp (dprintf), tt (task trace), s (task step), so (task stepover), c (task continue), cret (task continue -r). */
    symShellCmdInit ();                 /* This component provides shell commands related to symbol access: printf, set symbol, set, demangle, lookup. Aliases: lkup (lookup), lkAddr (lookup -a). */
    usrFsShellCmdInit ();               /* This component provides shell commands related to the file system: cd, file list, pwd, file copy, file move, file remove, file create, mkdir, file concat, more. Aliases: ls (file list), cp (file copy), mv (file move), rm (file remove), mkdir (file create -d), cat (file concat). */
    vmShowShellCmdInit ();              /* This component provides the 'vm context' shell command which displays information on the virtual memory context. */
    adrSpaceShellCmdInit ();            /* This component provides the 'adrsp' shell command which displays information on the address space. */
    sdShowShellCmdInit ();              /* This component provides shared data show shell commands: sd, sd info. */
    moduleShellCmdInit();               /* This component provides target loader shell commands: module, module info, module load. Aliases: ld (module load). */
    unloadShellCmdInit();               /* This component provides the 'module unload' shell command, and its alias 'unld', which is used to unload an object module from the kernel. */
    rtpShellCmdInit (RTP_SHELL_CMD_VERBOSITY, RTP_SHELL_CMD_PRIORITY, RTP_SHELL_CMD_OPTIONS, RTP_SHELL_CMD_STACK_SIZE, RTP_SHELL_CMD_DELAY, RTP_SHELL_CMD_TASK_OPTIONS); /* This component provides shell commands related to real-time processes (RTPs): rtp, rtp stop, rtp continue, rtp delete, rtp exec, rtp attach, rtp detach, rtp symbols add, rtp symbols remove, rtp symbols override, set cwc, rtp background, rtp foreground. Aliases: rtps (rtp stop), rtpc (rtp continue), rtpd (rtp delete), kill (rtp delete), rtpi (rtp task), run (rtp exec), jobs (rtp attach), fg (rtp foreground), bg (rtp background), attach (rtp attach), detach (rtp detach), symsAdd (rtp symbols add), symsRm (rtp symbols remove), symsOvrd (rtp symbols override). */
    rtpShowShellCmdInit ();             /* This component provides real-time process (RTP) show shell commands: rtp info, rtp list, rtp shl, syscall hooks, rtp hooks, rtp meminfo, syscalls, syscall monitor. Aliases: info (rtp info), shls (rtp shl), sc (syscalls), scm (syscall monitor), rtpm (rtp meminfo), ps (rtp list). */
    shlShellCmdInit ();                 /* This component provides shared library shell commands: shl, shl info. */
    tipShellCmdInit ();                 /* This component provides the 'tip' shell command which is used to connect to one or several remote systems over serial lines. */
    }



/******************************************************************************
*
* usrShellInit - The kernel shell initialization sequence
*/

void usrShellInit (void)
    {
    shellLibInit ();                    /* This component includes the shell core files. */
    dbgLibInit (DEBUG_STACK_TRACE_BUF_SIZE); /* This component includes the primary interactive functions for VxWorks. The following facilities are provided: task breakpoints, task single-stepping, symbolic disassembly, symbolic task stack tracing. */
    vxdbgRtpLibInit ();                 /* This component includes the process debugging library. */
    ledModeRegister (viLedLibInit);     /* This component provides an editing mode similar to the vi editor. */
    ledModeRegister (emacsLedLibInit);  /* This component provides an editing mode similar to the Emacs editor. */
    shellInterpRegister (shellInterpCInit); /* This component provides the C interpreter for the kernel shell. */
    shellInterpRegister (shellInterpCmdInit); /* This component provides the command interpreter for the kernel shell. */
    usrShellCmdInit ();                 /* The kernel shell commands initialization sequence */
    usrStartupScript (startupScriptFieldSplit (sysBootParams.startupScript)); /* Including this component results in the execution of a kernel shell script at VxWorks startup. */
    usrShell ();                        /* This component includes the target-resident kernel shell, which is spawned as a task. Any function that is invoked from the kernel shell, rather than spawned, runs in the shell's context. The task name for a shell on the console is "tShell0". The kernel shell is re-entrant, and more than one shell task can run at a time (hence the number suffix). In addition, if a user logs in remotely (using rlogin or telnet) to a VxWorks target, the name reflects that fact as well. For example, "tShellRem1". The "tShell" basename is configurable, see the VxWorks Kernel Shell User's Guide. */
    }



/******************************************************************************
*
* usrToolsInit - Software development tools
*/

void usrToolsInit (void)
    {
    timexInit ();                       /* utility to measure function execution time */
    eventPointStubLibInit ();           /* stub eventpoint implementation */
    eventPointLibInit ();               /* eventpoints instrumentation */
    dataCollectorLibInit ();            /* This component provides data collectors for generic analysis tools. See the dataCollectorLib entry in the VxWorks Kernel DEBUG ANALYSIS API Reference for detailed description of the different routines in this library. */
    svDataCollectorLibInit ();          /* Data collectors for System Viewer */
    usrLoaderInit ();                   /* The target loader initialization sequence. */
    usrStacktraceInit();                /* Stack tracing logic */
    usrSymTblInit ();                   /* Enable onboard symbol tables */
    trgLibInit ();                      /* Adds support for triggering for system and user events */
    usrVxdbgInit (VXDBG_EVT_TASK_PRIORITY, VXDBG_EVT_TASK_OPTIONS, VXDBG_EVT_TASK_STACK_SIZE); /* Support for the runtime debug library */
    usrWindviewInit ();                 /* usrWindviewInit */
    tlsLoadLibInit ();                  /* __thread variables loader support */
    rtpDbgCmdLibInit ();                /* Allows to send commands to perform operations in a RTP context */
    usrTipInit (TIP_CONFIG_STRING, TIP_ESCAPE_CHARACTER); /* interactive utility to connect to and manage multiple serial lines */
    usrShowInit ();                     /* Enable object show routines */
    usrRtpLibInit ();                   /* This component provides a list of commands for the shell C interpreter related to RTPs. Before starting an RTP, you must build a VxWorks image project with either this component or INCLUDE_RTP_SHOW_SHELL_CMD enabled. However, using this component allows you to use the rtpSp command directly (without a prior cmd). */
    usrShellInit ();                    /* The kernel shell initialization sequence */
    }



/******************************************************************************
*
* usrKernelCreateInit - Object creation functions
*/

void usrKernelCreateInit (void)
    {
    semDeleteLibInit ();                /* This component provides the semDeleteLib library that contains functions that terminate and delete semaphores. The semDelete() call terminates a semaphore and deallocates any associated memory. The deletion of a semaphore unblocks tasks pended on that semaphore; the functions that were pended return ERROR. Take care when deleting semaphores, particularly those used for mutual exclusion, to avoid deleting a semaphore out from under a task that already has taken (owns) that semaphore. Applications should adopt the protocol of only deleting semaphores that the deleting task has successfully taken. */
    taskCreateLibInit ();               /* This component provides the capability to dynamically instantiate and delete tasks. */
    taskMemLibInit ();                  /* taskStackAlloc and taskStackFree routines */
    msgQCreateLibInit ();               /* This component provides the msgQCreateLib library. This library contains functions for creating and deleting message queues. The functions to initialize and operate on message queues are implemented in msgQLib. */
    wdCreateLibInit ();                 /* This component provides wdCreateLib. This library provides creation and deletion functions for the watchdog facility. The functions to initialize and operate on watchdogs are implemented in wdLib. */
    }



/******************************************************************************
*
* usrRtpInit - RTP init functions
*/

void usrRtpInit (void)
    {
    rtpHookLibInit (RTP_HOOK_TBL_SIZE); /* This component includes hook functions that can be called on RTP operations. It also enables the initialization of a shared library. In addition, it allows you to register kernel functions that can be executed at various points in a process' life cycle. This component is included in the BUNDLE_RTP_DEPLOY bundle. */
    rtpLibInit (RTP_HOOK_TBL_SIZE, SYSCALL_HOOK_TBL_SIZE, RTP_SIGNAL_QUEUE_SIZE, TASK_USER_EXC_STACK_OVERFLOW_SIZE, TASK_USER_EXEC_STACK_OVERFLOW_SIZE, TASK_USER_EXEC_STACK_UNDERFLOW_SIZE, RTP_FD_NUM_MAX, RTP_MEM_FILL); /* This component defines a real-time process (RTP). This component is the foundation for user space applications. */
    rtpSigLibInit ();                   /* This component provides POSIX signal support for RTPs. */
    sdLibInit (SD_HOOK_TBL_SIZE);       /* This component provides data sharing between RTPs or the kernel. It is included in the BUNDLE_RTP_DEPLOY bundle. */
    shlLibInit ();                      /* This component provides support for the sharing of code between RTPs. This component is required for shared library support. */
    }



/******************************************************************************
*
* usrKernelCoreInit - Core kernel facilities
*/

void usrKernelCoreInit (void)
    {
    eventLibInit (VXEVENTS_OPTIONS);    /* This component provides event facilities. VxWorks events provide a means of communication and synchronization between tasks and other tasks, interrupt service routines (ISRs) and tasks, semaphores and tasks, and message queues and tasks. Events can be sent explicitly by tasks and ISRs, and can be sent when message queues or semaphores are free. Only tasks can receive events. Events can be used as a lighter-weight alternative to binary semaphores for task-to-task and ISR-to-task synchronization (because no object must be created). They can also be used to notify a task that a semaphore has become available, or that a message has arrived on a message queue. The events facility provides a mechanism for coordinating the activity of a task using up to thirty-two events that can be sent to it explicitly by other tasks and ISRs, or when semaphores and message queues are free. A task can wait on multiple events from multiple sources. Events thereby provide a means for coordination of a complex matrix of activity without allocation of additional system resources. */
                                        /* This component provides a library that provides the interface to VxWorks binary semaphores. Binary semaphores are the most versatile, efficient, and conceptually simple type of semaphore. They can be used to control mutually exclusive access to shared devices or data structures, or synchronize multiple tasks, or task-level and interrupt-level processes. Binary semaphores form the foundation of numerous VxWorks facilities. */
                                        /* This component provides the semCLib library. This library provides the interface to VxWorks counting semaphores. Counting semaphores are useful for guarding multiple instances of a resource. A counting semaphore can be viewed as a cell in memory whose contents keep track of a count. */
                                        /* This component provides the semRWLib and windSemRWLib libraries. semRWLib provides the interface to VxWorks reader/writer semaphores. Reader/writer semaphores provide a method of synchronizing groups of tasks that can be granted concurrent access to a resource with those tasks that require mutually exclusive access to that resource. Typically, this correlates to those tasks that intend to modify a resource and those which intend only to view it. windSemRWLib contains the implementation of the windSemRWDelete() function. A call to windSemRWDelete() unblocks any tasks pending on a read/write semaphore. If the deletion safety option is enabled, any and all owners have their safety count decremented. If the inversion safe option is enabled, any and all owners have their priority inheritance information updated. */
    semOpenInit ();                     /* This component provides the open/close/unlink interfaces for semaphores. */
    condVarOpenInit ();                 /* This component provides the open/close/unlink interfaces for condition variables. */
    msgQLibInit ();                     /* This component provides message queue support using the msgQLib library. This library contains functions for creating and using message queues, the primary inter-task communication mechanism in VxWorks. Message queues allow a variable number of messages (varying in length) to be queued in first-in-first-out (FIFO) order. Any task or interrupt service routine (ISR) can send messages to a message queue. Any task can receive messages from a message queue. Multiple tasks can send to, and receive from, the same message queue. Full-duplex communication between two tasks generally requires two message queues, one for each direction. For more information, see the reference information for msgQLib. */
    msgQOpenInit ();                    /* This component provides the open/close/unlink interfaces for message queues. */
    wdLibInit ();                       /* This component provides a general watchdog timer facility. Any task can create a watchdog timer and use it to run a specified function in the context of the system-clock ISR, after a specified delay. Once a timer has been created with wdCreate(), it can be started with wdStart(). The wdStart() function specifies what function to run, a parameter for that function, and the amount of time (in ticks) before the function is to be called. The timeout value is in ticks as determined by the system clock; see sysClkRateSet() for more information. After the specified delay ticks have elapsed, unless wdCancel() is called first to cancel the timer, the timeout function is invoked with the parameter specified in the wdStart() call. The timeout function is invoked whether the task which started the watchdog is running, suspended, or deleted. The timeout function executes only once per wdStart() invocation; there is no need to cancel a timer with wdCancel() after it has expired, or in the expiration callback itself. Note that the timeout function is invoked at interrupt level, rather than in the context of the task. Thus, there are restrictions on what the function can do. Watchdog functions are constrained to the same rules as interrupt service routines. For example, they cannot take semaphores, issue other calls that can block, or use I/O system functions like printf(). Note: You can defer watchdog function invocation. As such, isrIdCurrent is either a valid ISR_ID or is NULL in the case of deferral. */
    taskOpenInit ();                    /* This component provides the open/close/unlink interfaces for tasks. */
    vxdbgHooksInit ();                  /* hooks for the runtime debug library */
    vxdbgRtpLibInit ();                 /* Initialize process debugging library. */
    }



/******************************************************************************
*
* _WRS_NO_STACK_PROTECTOR - random number generator
*/

void _WRS_NO_STACK_PROTECTOR randomInit (void)
    {
    randomSWNumGenInit ();              /* This component provides the randomSWGenLib library. This library provides the implementation to generate a software random number. When an application requests random bytes, the content of the destination buffer is first used as random seed. Thereafter, the random state buffer is hashed and the hash output is returned as random bytes. If more bytes are requested than the hash output size, the hash output is used as seed and thereafter the random state buffer is hashed again. This process is repeated until the requested number of random bytes has been generated. */
    randomEntropyInterruptAddInit (RANDOM_INTERRUPT_ROUNDS); /* This component installs a callback function invoked from the interrupt handler that adds entropy to randomSWGenLib. The hook will read a high- resolution timer/counter and add the value as entropy to randomGenLib. The timer/counter read is CPU architecture dependent. This component requires that the VSB option RANDOM_ENTROPY_INJECT is enabled */
    randomEntropyAddSwitchHookInit (RANDOM_TASK_SWITCH_ROUNDS); /* This component installs a task switch hook that adds entropy to randomGenLib. The hook will read a high- resolution timer/counter and add the value as entropy to randomSWGenLib. The timer/counter read is CPU architecture dependent. */
    }



/******************************************************************************
*
* usrSecHashInit - Initialize the secHash providers
*/

void usrSecHashInit (void)
    {
    secHashMd5OpensslInit();            /* Registers an MD5 provider for the secHash MD5 API. The implementation is based on the low-level openssl APIs. This provider does not require the full openssl lib to be linked in. */
    secHashSha1OpensslInit();           /* Registers an SHA1 provider for the secHash SHA1 API. The implementation is based on the low-level openssl APIs. This provider does not require the full openssl lib to be linked in. */
    secHashSha256OpensslInit();         /* Registers an SHA256 provider for the secHash SHA256 API. The implementation is based on the low-level openssl APIs. This provider does not require the full openssl lib to be linked in. */
    secHashWhirlpoolOpensslInit();      /* Registers an WHIRLPOOL provider for the secHash Whirlpool API. The implementation is based on the low-level openssl APIs. This provider does not require the full openssl lib to be linked in. */
    }



/******************************************************************************
*
* usrClkInit - Clock system initialization.
*/

void usrClkInit (void)
    {
    usrVxbTimerSysInit();               /* This component includes support for the VxBus timer. */
    vxbSysClkLibInit();                 /* This component includes support for the VxBus system clock. */
    vxbAuxClkLibInit();                 /* This component includes support for the VxBus auxiliary clock. */
    sysClkInit ();                      /* This component starts the system clock. */
    vxbTimestampLibInit();              /* This component includes support for the VxBus timestamps. */
    }



/******************************************************************************
*
* usrScInit - The system call initialization sequence
*/

void usrScInit (void)
    {
    usrPosixScInit ();                  /* This component includes system call handlers for POSIX-based calls. */
    envScInit ();                       /* This component provides the envAccess() system call, which allows (read-only) access to the kernel global environment from a user-space application (RTP). */
    sockScLibInit ();                   /* System call support for socket API */
    memRtpLibInit (RTP_HEAP_INIT_SIZE,RTP_HEAP_DEFAULT_OPTIONS); /* This component initializes memory parameters to pass to the RTP. */
    windScInit ();                      /* system call handlers for WIND kernel */
    mmanScLibInit ();                   /* system call handlers for memory management */
    sdScInit ();                        /* system call handlers for shared data */
    shlScLibInit ();                    /* system call handlers for shared libraries */
    rtpIoLimitsInit ();                 /* library for RTP I/O system limits */
                                        /* system call handler for pipes */
    iosScLibInit ();                    /* IOS system calls */
    sysctlScLibInit ();                 /* System call support for sysctl(). */
    }



/******************************************************************************
*
* usrNetHostInit - 
*/

void usrNetHostInit (void)
    {
    usrNetHostTblSetup ();              /* host table support */
                                        /* get servce by name */
    usrHostnameSetup (TARGET_HOSTNAME_DEFAULT); /* This component assigns a local hostname to a target. */
    }



/******************************************************************************
*
* usrNetRemoteInit - 
*/

void usrNetRemoteInit (void)
    {
    remLibInit(RSH_STDERR_SETUP_TIMEOUT); /* Remote Command Library */
    remLibSysctlInit();                 /* Network sysctl tree support for remlib */
    usrFtpInit();                       /* File Transfer Protocol (FTP) library */
                                        /* Allows access to file system on boot host */
    usrNetRemoteCreate ();              /* Allows access to file system on boot host */
    }



/******************************************************************************
*
* usrNetUtilsInit - Initialize network utility routines
*/

void usrNetUtilsInit (void)
    {
    usrNetIfconfigInit ();              /* ifconfig */
    }



/******************************************************************************
*
* usrNetworkInit - Initialize the rest of the network subsystem
*/

void usrNetworkInit (void)
    {
    usrNetBoot ();                      /* Copy boot parameters for futher use by network */
    usrNetmaskGet ();                   /* Extracts netmask value from address field */
    usrNetSysctlInit();                 /* Networking System control support */
    usrNetHostInit ();                  /* initialize host table */
    rtpHostLibInit ();                  /* network sysctl tree support for host tables */
    rtpGetaddrinfoInit ();              /* network sysctl tree support for RTP getaddrinfo() */
    rtpGetnameinfoInit ();              /* network sysctl tree support for RTP getnameinfo() */
    usrNetRemoteInit ();                /* initialize network remote I/O access */
    usrNetEndLibInit();                 /* Support for network devices using MUX/END interface. */
    ipcom_config_usr_create ();         /* Includes the IPCOM user-side functions. */
    ipcom_config_create ();             /* Includes VxWorks IPCOM support. */
    netSysctlInit (TRUE);               /* Integrates IPNet sysctl nodes into VxWorks sysctl tree. */
    netIoctlScLibInit ();               /* Provides Network stack ioctl command validation. */
    usrNetUtilsInit ();                 /* Initialize network utility routines */
    }



/******************************************************************************
*
* usrOpensslInit - Initialize OpenSSL library
*/

void usrOpensslInit (void)
    {
    ipcrypto_init();                    /* Includes the Wind River Cryptography Libraries in the image. This is required for any application using cryptography. */
    ipssl_init();                       /* This component includes Wind River SSL in the image and loads the ciphers. */
    }



/******************************************************************************
*
* usrUsbPreStageInit - The usb earlier initialization before vxBus init
*/

void usrUsbPreStageInit (void)
    {
    usbInit ();                         /* USB Common Stack Initialization */
    }



/******************************************************************************
*
* usrUsbGroupInit - The USB group initialization
*/

void usrUsbGroupInit (void)
    {
    usbMsgAsynLibInit();                /* USB Message Asynchronous Library Initialization */
    usbHstClassInit();                  /* USB Host Class Driver Initialization */
    }



/******************************************************************************
*
* _WRS_NO_STACK_PROTECTOR - Entry point for post-kernel initialization
*/

void _WRS_NO_STACK_PROTECTOR usrRoot (char *pMemPoolStart, unsigned memPoolSize)
    {
    usrKernelCoreInit ();               /* Core kernel facilities */
    poolLibInit ();                     /* This component includes the Memory Pool library. Pools provide a fast and efficient memory management when an application uses a large number of identically sized memory blocks (for example, structures and objects) by minimizing the number of allocations from a memory partition. The use of pools also reduces possible fragmentation caused by frequent memory allocation and freeing. A pool is a dynamic set of statically sized memory blocks. All blocks in a pool are of the same size. The size of blocks are specified at pool creation and all the blocks are aligned on the block size; the block size must be a power of 2. */
    memInit (pMemPoolStart, memPoolSize, MEM_PART_DEFAULT_OPTIONS); /* This component provides the memLib library. This library provides the API for allocating and freeing blocks of memory of arbitrary size from an RTP heap. This library implements an RTP heap as a dedicated memory partition. One private heap is created automatically for every RTP. The library provides ANSI allocation functions and enhanced memory management features, including error handling and aligned allocation. Most of the memLib functions are simple wrappers to the memory partition management functions which implement the actual memory management functionality. For more information about the memory partition management facility, see the reference entry for memPartLib. */
    memPartLibInit (pMemPoolStart, memPoolSize); /* This component includes the core memory partition manager. */
    kProxHeapInit (pMemPoolStart, memPoolSize); /* This component provides the kProxHeapLib library. This library provides the function that initializes the kernel proximity heap partition. The kernel proximity heap is a memory partition created in the kernel system memory region. */
    pgPoolLibInit();                    /* Generic Page Pool Allocator */
    pgPoolVirtLibInit();                /* Page Pool Allocator for Virtual Space */
    pgPoolPhysLibInit();                /* Page Pool Allocator for Physical Space */
                                        /* This is the basic MMU component. It includes an API which is used for programmatic management of virtual memory. */
    usrMmuInit ();                      /* This component initializes the kernel's global MMU mappings according to the BSP's sysPhysMemDesc[ ] table. */
    pmapInit();                         /* This component provides the functionality to map or unmap physical address to the kernel/RTP context. */
    kCommonHeapInit (KERNEL_COMMON_HEAP_INIT_SIZE, KERNEL_COMMON_HEAP_INCR_SIZE); /* This component includes the kernel common heap which is the memory partition used by the kernel and kernel applications for dynamic memory allocation. Physical memory is allocated from the global RAM pool and virtual memory is allocated from the kernel virtual memory pool region. The heap is managed using the standard ANSI memory allocation functions, malloc(), free(), and so on. For more information, see the reference entries for memPartLib and memLib. */
    vxstdioKernInit ();                 /* This component supports task-specific standard streams (stdin, stdout, and stderr) within the kernel. */
    usrKernelCreateInit ();             /* Object creation functions */
    usrSecHashInit ();                  /* Initialize the secHash providers */
    boardInit();                        /* This component provides a function to initialize the board. */
    usrTextProtect ();                  /* Write-protect program text */
    usrOsmInit (TASK_USER_EXC_STACK_OVERFLOW_SIZE, VM_PAGE_SIZE); /* This component includes a handler for an exception stack overflow. */
    usrKernelIntStkProtect ();          /* Insert underflow and overflow guard pages on interrupt stack. */
    taskStackGuardPageEnable();         /* This component is used to insert underflow and overflow guard pages to kernel task stacks (including the root task). Also inserts guard pages on the idle task exception stack (in SMP), to protect against overflow while running task switch or swap hooks. */
    taskStackNoExecEnable();            /* This component causes exception and execution stacks for RTP and kernel tasks to be marked non-executable. */
    usrNetApplUtilInit ();              /* This component provides support for the stack and application logging utility. */
    memInfoInit ();                     /* This component provides the memInfo library. This library provides functions for obtaining information about a memory partition or the kernel heap. */
    envLibInit (ENV_VAR_USE_HOOKS);     /* This component provides the envLib library. This library provides a UNIX-compatible environment variable facility. Environment variables are created or modified with a call to putenv(): putenv ("variableName=value"); . The value of a variable can be retrieved with a call to getenv(), which returns a pointer to the value string. Tasks can share a common set of environment variables, or they can optionally create their own private environments, either automatically when the task create hook is installed, or by an explicit call to envPrivateCreate(). The task must be spawned with the VX_PRIVATE_ENV option set to receive a private set of environment variables. Private environments created by the task creation hook inherit the values of the environment of the task that called taskSpawn() (because task create hooks run in the context of the calling task). */
    usrShellBannerInit ();              /* This component toggles shell-specific elements in the banner. */
    intVecTableWriteProtect ();         /* Write-protect vector table */
    cacheDma32PartInit ();              /* This component provides a cache DMA partition manager for 32-bit physical memory. VxWorks must be configured with this component to use the DMA32 partition manager. */
    edrStubInit ();                     /* This component provides the error detection and reporting (ED&R) error-injection stub. */
    usrSysctlInit();                    /* This component provides SYSCTL function support. */
    kernelIdleTaskActivate();           /* Add Idle Tasks Support (SMP Only) */
    randomInit ();                      /* random number generator */
    usrIosCoreInit ();                  /* core I/O system */
    usrNetworkInit0 ();                 /* Initialize the network subsystem for drivers */
    usrHwSysctlInit();                  /* System control hardware info registration. */
    vxbDmaLibInit();                    /* This component provides a function to initialize the VxBus DMA subsystem. */
    vxbGpioLibInit();                   /* This component provides a routine to initialize the VxBus GPIO subsystem. */
    vxbIsrHandlerInit (VXB_MAX_INTR_VEC, VXB_MAX_INTR_CHAIN); /* This component supports provides the VxBus ISR handler module initialization function. */
    vxbIntLibInit (VXB_MAX_INTR_DEFER); /* This component includes support for VxBus interrupt library initialization. */
    vxIpiLibInit ();                    /* This component includes inter-processor interrupts for symmetric multiprocessing (SMP) and asymmetric multiprocessing (AMP). */
    miiBusFdtLibInit();                 /* MII bus FDT subsystem */
    miiBusLibInit();                    /* Includes the MII bus subsystem. */
    vxbPhyLibInit();                    /* This component provides VxBus generic PHY subsystem. */
    vxbPinMuxLibInit();                 /* This component provides a routine to initialize the VxBus PinMUX subsystem. */
    vxbPdLibInit();                     /* This component enables the VxBus power domain device subsystem. */
    vxbParamLibInit ();                 /* This component provides the mechanism for drivers to obtain parameter values. Driver parameters are values which have a useful default value which can be overridden by BSPs (DTS file). */
    vxbClkLibInit();                    /* This component enables the VxBus clock device subsystem. */
    usrSioIoctlLibInit ();              /* This component provides VxBus SIO IOCTL command validation. */
    usrUsbPreStageInit();               /* The usb earlier initialization before vxBus init */
    vxbLibInit ();                      /* This component provides a routines to initalize the VxBus subsystem. */
    intCpuUnlock(0); sysIntEnableFlagSet (); /* This component adds support to enable interrupts at an appropriate point in root task execution. */
    usrSerialInit ();                   /* This component provides initialization for the Serial I/O component. */
    usrClkInit ();                      /* Clock system initialization. */
    cpcInit ();                         /* CPUs Cross-Processor Call (SMP Only) */
    vxdbgCpuLibInit ();                 /* CPU control support for VxDBG */
                                        /* This component provides a low-level interface to the ARM floating-point unit (FPU). For the architecture-independent portion of the implementation, see fppLib. The ARM architecture optionally implements the hardware math coprocessor provided on various cores. Generally, the math coprocessor supports vector floating point and may support other functions. */
    pgMgrBaseLibInit();                 /* Basic Page Manager Library */
    pgMgrLibInit();                     /* Page Manager Library */
    usrRtpInit ();                      /* RTP init functions */
    mmanLibInit ();                     /* This component provides memory mapping and unmapping functions. */
    usrKernelExtraInit ();              /* Extended kernel facilities */
    usrIosExtraInit ();                 /* extended I/O system */
    usrHostnameSetup (TARGET_HOSTNAME_DEFAULT); /* This component assigns a local hostname to a target. */
    hostnameSysctlSetup();              /* Support to set and get the target hostname via sysctl(). This is necessary to use gethostname() or sethostname() in user-space (RTP) code. */
    sockLibInit ();                     /* Socket API */
    selTaskDeleteHookAdd ();            /* selectInit, part 2, install task delete hook */
    cplusCtorsLink ();                  /* Ensures that compiler-generated initialization functions, including initializers for C++ static objects, are called at kernel start up time. */
    usrCplusLibInit ();                 /* This component includes basic support for C++ applications. It is typically used in conjunction with INCLUDE_CPLUS_LANG. */
    cplusDemanglerInit ();              /* Includes the C++ demangler, which is useful when using the kernel shell loader because it provides for returning demangled symbol names to kernel shell symbol table queries. This component is added by default if both the INCLUDE_CPLUS and INCLUDE_SYM_TBL components are included in VxWorks. */
    usrScInit ();                       /* The system call initialization sequence */
    usrKernelIntStkProtectNonCore0 ();  /* insert underflow and overflow guard pages on interrupt stack on non-primary cores */
    usrSmpInit ();                      /* Enable multi-processor capability of the kernel */
    usrBanner ();                       /* This component displays the Wind River banner on startup. */
    usrOpensslInit ();                  /* Initialize OpenSSL library */
    miiBusMonitorTaskInit();            /* This component spawns the MII bus monitor task. */
    usrNetworkInit ();                  /* Initialize the rest of the network subsystem */
    usrUsbGroupInit();                  /* The USB group initialization */
    usrToolsInit ();                    /* Software development tools */
    { int status; printf("IMG1.. Enable EXT PWR GPIO\n"); status = vxbGpioAlloc(0x69); printf("IMG1.. GPIO allocation status: %d\n", status); status = vxbGpioSetDir(0x69,1); printf("IMG1.. GPIO direction set status: %d\n", status); } /* This component enables the externel power GPIO. */
    usrAppInit ();                      /* This component calls the initialization function for your application, usrAppInit() in your usrAppInit.c project file, after system start up. */
    usrRtpAppInit ();                   /* This component launches an RTP from a user-defined function. It is used to configure usrRtpAppInit() and is in the BUNDLE_RTP_DEPLOY bundle. */
    usrRtpAppInitBootline ();           /* This parameter launches RTPs from a string-encoded list in the boot parameters (see also INCLUDE_RTP_APPL_INIT_STRING). These RTPs are started automatically at boot time. */
    }



/******************************************************************************
*
* _WRS_NO_STACK_PROTECTOR - Pre-kernel initialization
*/

void _WRS_NO_STACK_PROTECTOR usrInit (int startType)
    {
    { void (* cpuInit) (void) = vxCpuInit; void (* mmuEarlyInit) (UINT32, UINT32, UINT32) = vxMmuEarlyInit; cpuInit = (void (*) (void)) ((uintptr_t) cpuInit + LOCAL_MEM_PHYS_ADRS); mmuEarlyInit = (void (*) (UINT32, UINT32, UINT32)) ((uintptr_t) mmuEarlyInit + LOCAL_MEM_PHYS_ADRS); cpuInit (); mmuEarlyInit (STATIC_MMU_TABLE_BASE, LOCAL_MEM_LOCAL_ADRS, IMA_SIZE); excVecBaseSet ((UINT32)VEC_BASE_ADRS); } /* This component includes the ARM architecture APU initialization. */
    armMonitorStub(startType);          /* This component includes the monitor stub (architecture internal usage). */
    sysStart (startType);               /* This component clears BSS and sets up the vector table base address. */
    usrAdjustDtb ();                    /* This compnoent includes support for adjusting the device tree blob (DTB) address (architecture internal usage). */
    usrFdtInit ((void*)DTB_RELOC_ADDR, (int)DTB_MAX_LEN); /* This component provides the flattened device tree library. */
    usrBoardLibInit();                  /* This component provides a function to initialize the board subsystem, supplying BSP access APIs. */
    usrAimCpuInit ();                   /* This component includes CPU library support. */
    cacheLibInit (USER_I_CACHE_MODE, USER_D_CACHE_MODE); /* This component is used to include cache support. */
    excShowInit ();                     /* This component provides detailed descriptions of exceptions in the error logs. */
    excVecInit ();                      /* This component provides architecture-dependent facilities for handling processor exceptions. */
    usrCacheEnable ();                  /* This component can be used to optionally enable caches. */
    objOwnershipInit ();                /* This component provides the objOwnerLib library which includes object ownership functions. */
    objInfoInit ();                     /* This component provides object management functions that require lookup in a list of objects, such as the objNameToId() function. */
    objLibInit ((OBJ_ALLOC_FUNC)FUNCPTR_OBJ_MEMALLOC_RTN, (OBJ_FREE_FUNC)FUNCPTR_OBJ_MEMFREE_RTN, OBJ_MEM_POOL_ID, OBJ_LIBRARY_OPTIONS); /* This component provides the objLib library. This library provides the interface to the VxWorks user object management facilities. */
    vxMemProbeInit ();                  /* This component initializes vxMemProbe( ) exception handler support. */
    wvLibInit ();                       /* Low-level kernel instrumentation needed by System Viewer */
    classListLibInit ();                /* This component provides object class list management. */
    semLibInit ();                      /* This component provides the semaphore support infrastructure. Semaphores are the basis for synchronization and mutual exclusion in VxWorks. They are powerful in their simplicity and form the foundation for numerous VxWorks facilities. Different semaphore types serve different needs, and while the behavior of the types differs, their basic interface is the same. This library provides semaphore functions common to all VxWorks semaphore types. For all types, the two basic operations are semTake() and semGive(), the acquisition or relinquishing of a semaphore. Mutex semaphores offer the greatest speed while binary semaphores offer the broadest applicability. The semLib library provides all of the semaphore operations, including functions for semaphore control, deletion, and information. Semaphores must be validated before any semaphore operation can be undertaken. An invalid semaphore ID results in ERROR, and an appropriate `errno' is set. */
                                        /* This component provides a library that provides the interface to VxWorks mutual-exclusion semaphores. Mutual-exclusion semaphores offer convenient options suited for situations requiring mutually exclusive access to resources. Typical applications include sharing devices and protecting data structures. Mutual-exclusion semaphores are used by many higher-level VxWorks facilities. The mutual-exclusion semaphore is a specialized version of the binary semaphore, designed to address issues inherent in mutual exclusion, such as recursive access to resources, priority inversion, and deletion safety. The fundamental behavior of the mutual-exclusion semaphore is identical to the binary semaphore (see the reference entry for semBLib), except for the following restrictions: it can only be used for mutual exclusion; it can only be given by the task that took it; it may not be taken or given from interrupt level; and the semFlush() operation is illegal. These last two operations have no meaning in mutual-exclusion situations. */
                                        /* This component provides the semMCreate() function. This function creates mutual-exclusion semaphores. */
    condVarLibInit ();                  /* This component provides support for condition variables. Condition variables allow tasks to wait on both an event to occur, and to acquire a mutex that protects an object associated with that event. Thus, condition variables are acquired by taking a mutex, and waiting on the condition variable. When the event is signaled, a task is unblocked and the mutex given to that task, which can then access the protected resource. Note that signaling a condition variable only unblocks a waiting resource - if a condition variable is signaled before a task waits on that condition variable, then the waiting task must wait until the condition variable is signaled again. A condition variable can only be associated with one mutex at a time (if there are waiters, all waiters must have held the same mutex when the condition variable was waited on. No condition variable function is callable from an ISR. For detailed descriptions of the functions provided in this component, see the reference entry for condVarLib. */
    classLibInit ();                    /* This component provides object class management. */
    kernelBaseInit ();                  /* This is a required component. DO NOT REMOVE. */
    taskCreateHookInit ();              /* This component provides user callouts on task creation and deletion. It is required to use the task hook library. */
                                        /* This component provides thread-local storage, a compiler facility that allows for allocation of a variable such that there are unique instances of the variable for each thread (or task, in VxWorks terms). */
    sysDebugModeInit ();                /* This component provides a flag indicating the system is in 'debug' mode. */
    umaskLibInit(UMASK_DEFAULT);        /* This component adds support for the POSIX file mode creation mask in the kernel environment. That is, it supports the unmask() function. */
    mmuDataNoExec = TRUE;               /* Including this component will result in only the memory pages containing the .text (and .rodata) ELF sections being executable. All other memory pages, such as pages containing the .data ELF section, task stack, and heaps, are marked non-executable. */
    usrKernelInit (VX_GLOBAL_NO_STACK_FILL); /* Context switch and interrupt handling. This is a required component. DO NOT REMOVE */
    }

