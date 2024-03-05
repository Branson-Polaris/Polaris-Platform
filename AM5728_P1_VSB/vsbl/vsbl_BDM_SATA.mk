# Automatically generated file: do not edit

##########################
# BDM_SATA Section
##########################


ifdef _WRS_CONFIG_BDM_SATA
VSBL_BDM_SATA_SRC = 
VSBL_BDM_SATA_DEPEND = 

ifdef _WRS_CONFIG_BDM_2_0_8_0_SATA_2_0_8_0
VSBL_BDM_SATA_SRC += BDM_SATA
VSBL_BDM_SATA_DEPEND += FS
VSBL_BDM_SATA_DEPEND += SERVICE_ERF
VSBL_BDM_SATA_DEPEND += VXBUS
BDM_SATA_FASTBUILD = YES
VSBL_BDM_SATA_PATH = $(WIND_BASE)/os/storage/bdm/sata
VSBL_BDM_SATA_VERSION = BDM_2_0_8_0_SATA_2_0_8_0
endif
endif

