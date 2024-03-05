# Automatically generated file: do not edit

##########################
# QSP Section
##########################


ifdef _WRS_CONFIG_QSP
VSBL_QSP_SRC = 
VSBL_QSP_DEPEND = 

ifdef _WRS_CONFIG_QSP_2_0_2_6
VSBL_QSP_SRC += QSP
ifndef _WRS_CONFIG_CERT
VSBL_QSP_DEPEND += END
endif
VSBL_QSP_DEPEND += FDT
VSBL_QSP_DEPEND += UTILS
VSBL_QSP_DEPEND += VXBUS
QSP_FASTBUILD = YES
VSBL_QSP_PATH = $(WIND_BASE)/os/psl/wrs/qsp
VSBL_QSP_VERSION = QSP_2_0_2_6
endif
endif

