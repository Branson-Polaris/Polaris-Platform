# Automatically generated file: do not edit

##########################
# IPNET_FIREWALL Section
##########################


ifdef _WRS_CONFIG_IPNET_FIREWALL
VSBL_IPNET_FIREWALL_SRC = 
VSBL_IPNET_FIREWALL_DEPEND = 

ifdef _WRS_CONFIG_IPNET_FIREWALL_2_0_0_4
VSBL_IPNET_FIREWALL_SRC += IPNET_FIREWALL
VSBL_IPNET_FIREWALL_DEPEND += IPNET_COREIP
VSBL_IPNET_FIREWALL_DEPEND += NET_BASE
IPNET_FIREWALL_FASTBUILD = YES
VSBL_IPNET_FIREWALL_PATH = $(WIND_BASE)/os/net/ipnet/firewall
VSBL_IPNET_FIREWALL_VERSION = IPNET_FIREWALL_2_0_0_4
endif
endif

