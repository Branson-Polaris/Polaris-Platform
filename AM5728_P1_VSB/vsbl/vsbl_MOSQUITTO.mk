# Automatically generated file: do not edit

##########################
# MOSQUITTO Section
##########################


ifdef _WRS_CONFIG_MOSQUITTO
VSBL_MOSQUITTO_SRC = 
VSBL_MOSQUITTO_DEPEND = 

ifdef _WRS_CONFIG_MOSQUITTO_1_6_8_3
VSBL_MOSQUITTO_SRC += MOSQUITTO
VSBL_MOSQUITTO_DEPEND += SECURITY_MISC_SEC_CRYPTO
VSBL_MOSQUITTO_DEPEND += UTILS_UNIX
VSBL_MOSQUITTO_DEPEND += LIBC_STD
VSBL_MOSQUITTO_DEPEND += OPENSSL
MOSQUITTO_FASTBUILD = YES
MOSQUITTO_SUBSCRIBE = UTILS_UNIX
VSBL_MOSQUITTO_PATH = $(WIND_BASE)/contrib/mosquitto-1.6.8
VSBL_MOSQUITTO_VERSION = MOSQUITTO_1_6_8_3
endif
endif

