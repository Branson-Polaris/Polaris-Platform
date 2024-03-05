# Automatically generated file: do not edit

##########################
# XEN Section
##########################


ifdef _WRS_CONFIG_XEN
VSBL_XEN_SRC = 
VSBL_XEN_DEPEND = 

ifdef _WRS_CONFIG_XEN_2_0_3_4
VSBL_XEN_SRC += XEN
VSBL_XEN_DEPEND += FDT
VSBL_XEN_DEPEND += VXBUS
VSBL_XEN_DEPEND += CORE
VSBL_XEN_DEPEND += ARM
XEN_FASTBUILD = YES
VSBL_XEN_PATH = $(WIND_BASE)/os/psl/other/xen
VSBL_XEN_VERSION = XEN_2_0_3_4
endif
endif

