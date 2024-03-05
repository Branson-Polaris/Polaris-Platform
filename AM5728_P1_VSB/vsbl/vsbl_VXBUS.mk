# Automatically generated file: do not edit

##########################
# VXBUS Section
##########################


ifdef _WRS_CONFIG_VXBUS
VSBL_VXBUS_SRC = 
VSBL_VXBUS_DEPEND = 

ifdef _WRS_CONFIG_VXBUS_2_1_4_2
ifdef _WRS_CONFIG_VXBUS_DRV
VSBL_VXBUS_SRC += VXBUS_DRV
endif
VSBL_VXBUS_SRC += VXBUS
VSBL_VXBUS_DEPEND += SERVICE
ifdef _WRS_CONFIG_FDT
VSBL_VXBUS_DEPEND += FDT
endif
ifdef _WRS_CONFIG_FDT*
VSBL_VXBUS_DEPEND += FDT
endif
VSBL_VXBUS_DEPEND += CORE
VXBUS_FASTBUILD = YES
VSBL_VXBUS_PATH = $(WIND_BASE)/os/drv/vxbus
VSBL_VXBUS_VERSION = VXBUS_2_1_4_2
endif
endif

