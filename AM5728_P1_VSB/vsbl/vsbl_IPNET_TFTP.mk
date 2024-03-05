# Automatically generated file: do not edit

##########################
# IPNET_TFTP Section
##########################


ifdef _WRS_CONFIG_IPNET_TFTP
VSBL_IPNET_TFTP_SRC = 
VSBL_IPNET_TFTP_DEPEND = 

ifdef _WRS_CONFIG_IPNET_TFTP_2_0_1_1
VSBL_IPNET_TFTP_SRC += IPNET_TFTP
VSBL_IPNET_TFTP_DEPEND += IPNET_COREIP
IPNET_TFTP_FASTBUILD = YES
VSBL_IPNET_TFTP_PATH = $(WIND_BASE)/os/net/ipnet/app/tftp
VSBL_IPNET_TFTP_VERSION = IPNET_TFTP_2_0_1_1
endif
endif

