# Automatically generated file: do not edit

##########################
# FS_CDROMFS Section
##########################


ifdef _WRS_CONFIG_FS_CDROMFS
VSBL_FS_CDROMFS_SRC = 
VSBL_FS_CDROMFS_DEPEND = 

ifdef _WRS_CONFIG_FS_2_1_4_0_CDROMFS_2_0_0_6
VSBL_FS_CDROMFS_SRC += FS_CDROMFS
VSBL_FS_CDROMFS_DEPEND += BDM
VSBL_FS_CDROMFS_DEPEND += SERVICE_ERF
VSBL_FS_CDROMFS_DEPEND += UTILS_UTF
FS_CDROMFS_FASTBUILD = YES
VSBL_FS_CDROMFS_PATH = $(WIND_BASE)/os/storage/fs/cdromfs
VSBL_FS_CDROMFS_VERSION = FS_2_1_4_0_CDROMFS_2_0_0_6
endif
endif

