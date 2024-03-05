# Automatically generated file: do not edit

##########################
# OP_TEE Section
##########################


ifdef _WRS_CONFIG_OP_TEE
VSBL_OP_TEE_SRC = 
VSBL_OP_TEE_DEPEND = 

ifdef _WRS_CONFIG_OP_TEE_2_3_0_2
ifdef _WRS_CONFIG_OP_TEE_DEMO
VSBL_OP_TEE_SRC += OP_TEE_DEMO
endif
VSBL_OP_TEE_SRC += OP_TEE
VSBL_OP_TEE_DEPEND += CORE
VSBL_OP_TEE_DEPEND += CORE
OP_TEE_FASTBUILD = YES
VSBL_OP_TEE_PATH = $(WIND_BASE)/os/security/op_tee
VSBL_OP_TEE_VERSION = OP_TEE_2_3_0_2
endif
endif

