# Automatically generated file: do not edit

##########################
# IPNET_SNTP Section
##########################


ifdef _WRS_CONFIG_IPNET_SNTP
VSBL_IPNET_SNTP_SRC = 
VSBL_IPNET_SNTP_DEPEND = 

ifdef _WRS_CONFIG_IPNET_SNTP_2_0_1_0
VSBL_IPNET_SNTP_SRC += IPNET_SNTP
VSBL_IPNET_SNTP_DEPEND += IPNET_COREIP
IPNET_SNTP_FASTBUILD = YES
VSBL_IPNET_SNTP_PATH = $(WIND_BASE)/os/net/ipnet/app/sntp
VSBL_IPNET_SNTP_VERSION = IPNET_SNTP_2_0_1_0
endif
endif

