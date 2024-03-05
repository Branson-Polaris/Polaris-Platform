# Automatically generated file: do not edit

##########################
# GPTP Section
##########################


ifdef _WRS_CONFIG_GPTP
VSBL_GPTP_SRC = 
VSBL_GPTP_DEPEND = 

ifdef _WRS_CONFIG_GPTP_1_0_0_3
VSBL_GPTP_SRC += GPTP
VSBL_GPTP_DEPEND += END
VSBL_GPTP_DEPEND += IPNET_COREIP
GPTP_FASTBUILD = YES
VSBL_GPTP_PATH = $(WIND_BASE)/os/net/gptp
VSBL_GPTP_VERSION = GPTP_1_0_0_3
endif
endif

