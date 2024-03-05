# Automatically generated file: do not edit

##########################
# TSN Section
##########################


ifdef _WRS_CONFIG_TSN
VSBL_TSN_SRC = 
VSBL_TSN_DEPEND = 

ifdef _WRS_CONFIG_TSN_2_0_2_3
VSBL_TSN_SRC += TSN
VSBL_TSN_DEPEND += END
ifdef _WRS_CONFIG_GPTP
VSBL_TSN_DEPEND += GPTP
endif
ifndef _WRS_CONFIG_GPTP
VSBL_TSN_DEPEND += PTP
endif
VSBL_TSN_DEPEND += IPNET_COREIP
VSBL_TSN_DEPEND += JANSSON
TSN_FASTBUILD = YES
VSBL_TSN_PATH = $(WIND_BASE)/os/net/tsn
VSBL_TSN_VERSION = TSN_2_0_2_3
endif
endif

