# Automatically generated file: do not edit

##########################
# XRT Section
##########################


ifdef _WRS_CONFIG_XRT
VSBL_XRT_SRC = 
VSBL_XRT_DEPEND = 

ifdef _WRS_CONFIG_XRT_2020_1_0_0
VSBL_XRT_SRC += XRT
VSBL_XRT_DEPEND += BOOST
VSBL_XRT_DEPEND += KHRONOS
VSBL_XRT_DEPEND += UTILS_UNIX
XRT_FASTBUILD = YES
XRT_SUBSCRIBE = UTILS_UNIX
VSBL_XRT_PATH = $(WIND_BASE)/contrib/xilinx_xrt-2020.1
VSBL_XRT_VERSION = XRT_2020_1_0_0
endif
endif

