# Automatically generated file: do not edit

##########################
# BDM_NVRAM Section
##########################


ifdef _WRS_CONFIG_BDM_NVRAM
VSBL_BDM_NVRAM_SRC = 
VSBL_BDM_NVRAM_DEPEND = 

ifdef _WRS_CONFIG_BDM_2_0_8_0_NVRAM_2_0_8_0
VSBL_BDM_NVRAM_SRC += BDM_NVRAM
VSBL_BDM_NVRAM_DEPEND += FS
VSBL_BDM_NVRAM_DEPEND += SERVICE_ERF
BDM_NVRAM_FASTBUILD = YES
VSBL_BDM_NVRAM_PATH = $(WIND_BASE)/os/storage/bdm/nvram
VSBL_BDM_NVRAM_VERSION = BDM_2_0_8_0_NVRAM_2_0_8_0
endif
endif

