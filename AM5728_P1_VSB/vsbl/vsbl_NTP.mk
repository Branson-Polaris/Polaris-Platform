# Automatically generated file: do not edit

##########################
# NTP Section
##########################


ifdef _WRS_CONFIG_NTP
VSBL_NTP_SRC = 
VSBL_NTP_DEPEND = 

ifdef _WRS_CONFIG_NTP_4_2_8p15_6
VSBL_NTP_SRC += NTP
VSBL_NTP_DEPEND += IPNET_COREIP
VSBL_NTP_DEPEND += IPNET_SNTP
VSBL_NTP_DEPEND += CORE
VSBL_NTP_DEPEND += NET_BASE
VSBL_NTP_DEPEND += OPENSSL
VSBL_NTP_DEPEND += NET_BASE
NTP_FASTBUILD = YES
VSBL_NTP_PATH = $(WIND_BASE)/contrib/ntp-4.2.8p15
VSBL_NTP_VERSION = NTP_4_2_8p15_6
endif
endif

