# Automatically generated file: do not edit

##########################
# IPNET_DHCP Section
##########################


ifdef _WRS_CONFIG_IPNET_DHCP
VSBL_IPNET_DHCP_SRC = 
VSBL_IPNET_DHCP_DEPEND = 

ifdef _WRS_CONFIG_IPNET_DHCP_2_0_0_8
ifdef _WRS_CONFIG_IPNET_DHCP_CLIENT
VSBL_IPNET_DHCP_SRC += IPNET_DHCP_CLIENT
endif
ifdef _WRS_CONFIG_IPNET_DHCP_CLIENT6
VSBL_IPNET_DHCP_SRC += IPNET_DHCP_CLIENT6
endif
ifdef _WRS_CONFIG_IPNET_DHCP_RELAY
VSBL_IPNET_DHCP_SRC += IPNET_DHCP_RELAY
endif
ifdef _WRS_CONFIG_IPNET_DHCP_SERVER
VSBL_IPNET_DHCP_SRC += IPNET_DHCP_SERVER
endif
ifdef _WRS_CONFIG_IPNET_DHCP_SERVER6
VSBL_IPNET_DHCP_SRC += IPNET_DHCP_SERVER6
endif
VSBL_IPNET_DHCP_SRC += IPNET_DHCP
VSBL_IPNET_DHCP_DEPEND += IPNET_COREIP
IPNET_DHCP_FASTBUILD = YES
VSBL_IPNET_DHCP_PATH = $(WIND_BASE)/os/net/ipnet/app/dhcp
VSBL_IPNET_DHCP_VERSION = IPNET_DHCP_2_0_0_8
endif
endif
