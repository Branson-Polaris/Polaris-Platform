# Automatically generated file: do not edit

##########################
# SNMP Section
##########################


ifdef _WRS_CONFIG_SNMP
VSBL_SNMP_SRC = 
VSBL_SNMP_DEPEND = 

ifdef _WRS_CONFIG_SNMP_2_0_1_4
VSBL_SNMP_SRC += SNMP
VSBL_SNMP_DEPEND += IPNET_COREIP
VSBL_SNMP_DEPEND += MIB2
VSBL_SNMP_DEPEND += SERVICE_SOCKET
VSBL_SNMP_DEPEND += OPENSSL
SNMP_FASTBUILD = YES
VSBL_SNMP_PATH = $(WIND_BASE)/os/net/app/snmp
VSBL_SNMP_VERSION = SNMP_2_0_1_4
endif
endif

