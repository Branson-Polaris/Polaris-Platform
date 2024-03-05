# Automatically generated file: do not edit

##########################
# BDM_NVME Section
##########################


ifdef _WRS_CONFIG_BDM_NVME
VSBL_BDM_NVME_SRC = 
VSBL_BDM_NVME_DEPEND = 

ifdef _WRS_CONFIG_BDM_2_0_8_0_NVME_2_0_8_0
VSBL_BDM_NVME_SRC += BDM_NVME
VSBL_BDM_NVME_DEPEND += FS
VSBL_BDM_NVME_DEPEND += SERVICE_ERF
VSBL_BDM_NVME_DEPEND += SERVICE_JOBQUEUE
BDM_NVME_FASTBUILD = YES
VSBL_BDM_NVME_PATH = $(WIND_BASE)/os/storage/bdm/nvme
VSBL_BDM_NVME_VERSION = BDM_2_0_8_0_NVME_2_0_8_0
endif
endif

