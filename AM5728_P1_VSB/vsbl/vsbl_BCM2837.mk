# Automatically generated file: do not edit

##########################
# BCM2837 Section
##########################


ifdef _WRS_CONFIG_BCM2837
VSBL_BCM2837_SRC = 
VSBL_BCM2837_DEPEND = 

ifdef _WRS_CONFIG_BCM2837_0_1_1_2
VSBL_BCM2837_SRC += BCM2837
VSBL_BCM2837_DEPEND += FDT
VSBL_BCM2837_DEPEND += SERVICE_JOBQUEUE
VSBL_BCM2837_DEPEND += UTILS
VSBL_BCM2837_DEPEND += VXBUS
BCM2837_FASTBUILD = YES
VSBL_BCM2837_PATH = $(WIND_BASE)/os/unsupported/rpi_3/bcm2837
VSBL_BCM2837_VERSION = BCM2837_0_1_1_2
endif
endif

