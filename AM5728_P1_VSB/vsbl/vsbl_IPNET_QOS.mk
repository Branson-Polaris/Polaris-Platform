# Automatically generated file: do not edit

##########################
# IPNET_QOS Section
##########################


ifdef _WRS_CONFIG_IPNET_QOS
VSBL_IPNET_QOS_SRC = 
VSBL_IPNET_QOS_DEPEND = 

ifdef _WRS_CONFIG_IPNET_QOS_2_0_2_0
VSBL_IPNET_QOS_SRC += IPNET_QOS
VSBL_IPNET_QOS_DEPEND += IPNET_COREIP
VSBL_IPNET_QOS_DEPEND += NET_BASE
IPNET_QOS_FASTBUILD = YES
VSBL_IPNET_QOS_PATH = $(WIND_BASE)/os/net/ipnet/qos
VSBL_IPNET_QOS_VERSION = IPNET_QOS_2_0_2_0
endif
endif

