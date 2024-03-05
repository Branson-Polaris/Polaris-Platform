# Automatically generated file: do not edit

##########################
# TPM2_TSS Section
##########################


ifdef _WRS_CONFIG_TPM2_TSS
VSBL_TPM2_TSS_SRC = 
VSBL_TPM2_TSS_DEPEND = 

ifdef _WRS_CONFIG_TPM2_TSS_2_2_2_6
VSBL_TPM2_TSS_SRC += TPM2_TSS
ifdef _WRS_CONFIG_CORE_RTP
VSBL_TPM2_TSS_DEPEND += UTILS_UNIX
endif
VSBL_TPM2_TSS_DEPEND += CRYPTOMISC_TPM
VSBL_TPM2_TSS_DEPEND += IPNET_USRSPACE
VSBL_TPM2_TSS_DEPEND += LIBCURL
VSBL_TPM2_TSS_DEPEND += SECURITY_MISC_SEC_HASH
VSBL_TPM2_TSS_DEPEND += WEBCLI
VSBL_TPM2_TSS_DEPEND += OPENSSL
TPM2_TSS_FASTBUILD = YES
TPM2_TSS_SUBSCRIBE = UTILS_UNIX
VSBL_TPM2_TSS_PATH = $(WIND_BASE)/contrib/tpm2_tss-2.2.2
VSBL_TPM2_TSS_VERSION = TPM2_TSS_2_2_2_6
endif
endif

