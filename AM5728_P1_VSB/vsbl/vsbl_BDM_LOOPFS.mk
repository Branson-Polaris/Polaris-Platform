# Automatically generated file: do not edit

##########################
# BDM_LOOPFS Section
##########################


ifdef _WRS_CONFIG_BDM_LOOPFS
VSBL_BDM_LOOPFS_SRC = 
VSBL_BDM_LOOPFS_DEPEND = 

ifdef _WRS_CONFIG_BDM_2_0_8_0_LOOPFS_2_0_8_0
VSBL_BDM_LOOPFS_SRC += BDM_LOOPFS
VSBL_BDM_LOOPFS_DEPEND += FS
VSBL_BDM_LOOPFS_DEPEND += SERVICE_ERF
BDM_LOOPFS_FASTBUILD = YES
VSBL_BDM_LOOPFS_PATH = $(WIND_BASE)/os/storage/bdm/loopfs
VSBL_BDM_LOOPFS_VERSION = BDM_2_0_8_0_LOOPFS_2_0_8_0
endif
endif

