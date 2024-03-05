# Automatically generated file: do not edit

##########################
# BDM Section
##########################


ifdef _WRS_CONFIG_BDM
VSBL_BDM_SRC = 
VSBL_BDM_DEPEND = 

ifdef _WRS_CONFIG_BDM_2_0_8_0
ifdef _WRS_CONFIG_BDM_FLASH
VSBL_BDM_SRC += BDM_FLASH
endif
ifdef _WRS_CONFIG_BDM_SIM
VSBL_BDM_SRC += BDM_SIM
endif
ifdef _WRS_CONFIG_BDM_LOOPFS
VSBL_BDM_SRC += BDM_LOOPFS
endif
ifdef _WRS_CONFIG_BDM_NVME
VSBL_BDM_SRC += BDM_NVME
endif
ifdef _WRS_CONFIG_BDM_NVRAM
VSBL_BDM_SRC += BDM_NVRAM
endif
ifdef _WRS_CONFIG_BDM_SATA
VSBL_BDM_SRC += BDM_SATA
endif
ifdef _WRS_CONFIG_BDM_SDMMC
VSBL_BDM_SRC += BDM_SDMMC
endif
VSBL_BDM_SRC += BDM
VSBL_BDM_DEPEND += SERVICE_ERF
BDM_FASTBUILD = YES
VSBL_BDM_PATH = $(WIND_BASE)/os/storage/bdm
VSBL_BDM_VERSION = BDM_2_0_8_0
endif
endif

