
ifndef __HEADER_ACCESS_BDM_NVME_INCLUDED
__HEADER_ACCESS_BDM_NVME_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_BDM_NVME = 



ifneq ($(wildcard $(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/BDM_NVME),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), BDM_NVME))
VSBL_LKH += $(OPTION_INCLUDE_DIR)$(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/BDM_NVME
endif
endif

endif

endif

