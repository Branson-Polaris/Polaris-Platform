# Automatically generated file: do not edit

##########################
# DEBUG Section
##########################


ifdef _WRS_CONFIG_DEBUG
VSBL_DEBUG_SRC = 
VSBL_DEBUG_DEPEND = 

ifdef _WRS_CONFIG_DEBUG_2_0_3_3
ifdef _WRS_CONFIG_DEBUG_SYSTEMVIEWER
VSBL_DEBUG_SRC += DEBUG_SYSTEMVIEWER
endif
VSBL_DEBUG_SRC += DEBUG
VSBL_DEBUG_DEPEND += UTILS_LOADER
DEBUG_FASTBUILD = YES
VSBL_DEBUG_PATH = $(WIND_BASE)/os/debug_analysis/debug
VSBL_DEBUG_VERSION = DEBUG_2_0_3_3
endif
endif

