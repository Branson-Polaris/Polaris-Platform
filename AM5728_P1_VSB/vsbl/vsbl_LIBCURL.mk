# Automatically generated file: do not edit

##########################
# LIBCURL Section
##########################


ifdef _WRS_CONFIG_LIBCURL
VSBL_LIBCURL_SRC = 
VSBL_LIBCURL_DEPEND = 

ifdef _WRS_CONFIG_LIBCURL_7_71_1_1
VSBL_LIBCURL_SRC += LIBCURL
VSBL_LIBCURL_DEPEND += IPNET_COREIP
VSBL_LIBCURL_DEPEND += SECURITY_MISC_SEC_CRYPTO
VSBL_LIBCURL_DEPEND += ZLIB
LIBCURL_FASTBUILD = YES
VSBL_LIBCURL_PATH = $(WIND_BASE)/contrib/libcurl-7.71.1
VSBL_LIBCURL_VERSION = LIBCURL_7_71_1_1
endif
endif

