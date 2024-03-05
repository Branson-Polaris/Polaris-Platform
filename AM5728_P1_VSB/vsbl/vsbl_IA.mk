# Automatically generated file: do not edit

##########################
# IA Section
##########################


ifdef _WRS_CONFIG_IA
VSBL_IA_SRC = 
VSBL_IA_DEPEND = 

ifdef _WRS_CONFIG_IA_2_0_4_2
VSBL_IA_SRC += IA
ifndef _WRS_CONFIG_CERT
VSBL_IA_DEPEND += ACPI
endif
VSBL_IA_DEPEND += ITL_X86_COMMON
IA_FASTBUILD = YES
VSBL_IA_PATH = $(WIND_BASE)/os/arch/ia
VSBL_IA_VERSION = IA_2_0_4_2
endif
endif

