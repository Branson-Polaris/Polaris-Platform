# Automatically generated file: do not edit

##########################
# PTP Section
##########################


ifdef _WRS_CONFIG_PTP
VSBL_PTP_SRC = 
VSBL_PTP_DEPEND = 

ifdef _WRS_CONFIG_PTP_2_0_2_0
VSBL_PTP_SRC += PTP
VSBL_PTP_DEPEND += END
VSBL_PTP_DEPEND += IPNET_COREIP
VSBL_PTP_DEPEND += NET_BASE
VSBL_PTP_DEPEND += NET_BASE
PTP_FASTBUILD = YES
VSBL_PTP_PATH = $(WIND_BASE)/os/net/ptp
VSBL_PTP_VERSION = PTP_2_0_2_0
endif
endif

