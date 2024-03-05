# Automatically generated file: do not edit

##########################
# BDM_SDMMC Section
##########################


ifdef _WRS_CONFIG_BDM_SDMMC
VSBL_BDM_SDMMC_SRC = 
VSBL_BDM_SDMMC_DEPEND = 

ifdef _WRS_CONFIG_BDM_2_0_8_0_SDMMC_2_0_8_0
VSBL_BDM_SDMMC_SRC += BDM_SDMMC
VSBL_BDM_SDMMC_DEPEND += FS
VSBL_BDM_SDMMC_DEPEND += SERVICE_ERF
BDM_SDMMC_FASTBUILD = YES
VSBL_BDM_SDMMC_PATH = $(WIND_BASE)/os/storage/bdm/sdmmc
VSBL_BDM_SDMMC_VERSION = BDM_2_0_8_0_SDMMC_2_0_8_0
endif
endif

