# Automatically generated file: do not edit

##########################
# SECURE_LOADER Section
##########################


ifdef _WRS_CONFIG_SECURE_LOADER
VSBL_SECURE_LOADER_SRC = 
VSBL_SECURE_LOADER_DEPEND = 

ifdef _WRS_CONFIG_SECURE_LOADER_2_0_2_6
VSBL_SECURE_LOADER_SRC += SECURE_LOADER
VSBL_SECURE_LOADER_DEPEND += SECURITY_MISC_SEC_CRYPTO
SECURE_LOADER_FASTBUILD = YES
SECURE_LOADER_FRIEND = UTILS_LOADER
VSBL_SECURE_LOADER_PATH = $(WIND_BASE)/os/security/secure_loader
VSBL_SECURE_LOADER_VERSION = SECURE_LOADER_2_0_2_6
endif
endif

