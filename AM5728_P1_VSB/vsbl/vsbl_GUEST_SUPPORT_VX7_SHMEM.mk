# Automatically generated file: do not edit

##########################
# GUEST_SUPPORT_VX7_SHMEM Section
##########################


ifdef _WRS_CONFIG_GUEST_SUPPORT_VX7_SHMEM
VSBL_GUEST_SUPPORT_VX7_SHMEM_SRC = 
VSBL_GUEST_SUPPORT_VX7_SHMEM_DEPEND = 

ifdef _WRS_CONFIG_GUEST_SUPPORT_VX7_1_0_1_3_SHMEM_1_0_1_3
VSBL_GUEST_SUPPORT_VX7_SHMEM_SRC += GUEST_SUPPORT_VX7_SHMEM
VSBL_GUEST_SUPPORT_VX7_SHMEM_DEPEND += GUEST_SUPPORT_VX7_HVIF
VSBL_GUEST_SUPPORT_VX7_SHMEM_DEPEND += VXBUS
GUEST_SUPPORT_VX7_SHMEM_FASTBUILD = YES
VSBL_GUEST_SUPPORT_VX7_SHMEM_PATH = $(WIND_BASE)/os/hv/guest_support_vx7/shmem
VSBL_GUEST_SUPPORT_VX7_SHMEM_VERSION = GUEST_SUPPORT_VX7_1_0_1_3_SHMEM_1_0_1_3
endif
endif

