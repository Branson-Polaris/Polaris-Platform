# Automatically generated file: do not edit

##########################
# CIVETWEB Section
##########################


ifdef _WRS_CONFIG_CIVETWEB
VSBL_CIVETWEB_SRC = 
VSBL_CIVETWEB_DEPEND = 

ifdef _WRS_CONFIG_CIVETWEB_1_9_1_13
VSBL_CIVETWEB_SRC += CIVETWEB
VSBL_CIVETWEB_DEPEND += SECURITY_MISC_SEC_CRYPTO
VSBL_CIVETWEB_DEPEND += UTILS_UNIX
VSBL_CIVETWEB_DEPEND += CORE
CIVETWEB_FASTBUILD = YES
CIVETWEB_SUBSCRIBE = UTILS_UNIX
VSBL_CIVETWEB_PATH = $(WIND_BASE)/contrib/civetweb-1.9.1
VSBL_CIVETWEB_VERSION = CIVETWEB_1_9_1_13
endif
endif
