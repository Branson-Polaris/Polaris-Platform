# Automatically generated file: do not edit

##########################
# CAN Section
##########################


ifdef _WRS_CONFIG_CAN
VSBL_CAN_SRC = 
VSBL_CAN_DEPEND = 

ifdef _WRS_CONFIG_CAN_2_0_5_0
VSBL_CAN_SRC += CAN
VSBL_CAN_DEPEND += SERVICE_SOCKET
VSBL_CAN_DEPEND += VXBUS
CAN_FASTBUILD = YES
VSBL_CAN_PATH = $(WIND_BASE)/os/connectivity/can
VSBL_CAN_VERSION = CAN_2_0_5_0
endif
endif

