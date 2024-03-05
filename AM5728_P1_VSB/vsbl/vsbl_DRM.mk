# Automatically generated file: do not edit

##########################
# DRM Section
##########################


ifdef _WRS_CONFIG_DRM
VSBL_DRM_SRC = 
VSBL_DRM_DEPEND = 

ifdef _WRS_CONFIG_DRM_4_9_0_17
VSBL_DRM_SRC += DRM
VSBL_DRM_DEPEND += LIBDRM
VSBL_DRM_DEPEND += CORE
VSBL_DRM_DEPEND += CORE
DRM_FASTBUILD = YES
DRM_FRIEND = ITLI915 GPUDEV_RCAR_DU
VSBL_DRM_PATH = $(WIND_BASE)/contrib/drm-4.9.0
VSBL_DRM_VERSION = DRM_4_9_0_17
endif
endif

