# Automatically generated file: do not edit

##########################
# IPNET_FTP Section
##########################


ifdef _WRS_CONFIG_IPNET_FTP
VSBL_IPNET_FTP_SRC = 
VSBL_IPNET_FTP_DEPEND = 

ifdef _WRS_CONFIG_IPNET_FTP_2_0_1_3
VSBL_IPNET_FTP_SRC += IPNET_FTP
VSBL_IPNET_FTP_DEPEND += IPNET_COREIP
VSBL_IPNET_FTP_DEPEND += OPENSSL
IPNET_FTP_FASTBUILD = YES
VSBL_IPNET_FTP_PATH = $(WIND_BASE)/os/net/ipnet/app/ftp
VSBL_IPNET_FTP_VERSION = IPNET_FTP_2_0_1_3
endif
endif

