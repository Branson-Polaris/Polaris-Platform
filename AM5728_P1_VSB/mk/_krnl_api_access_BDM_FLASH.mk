
ifndef __HEADER_ACCESS_BDM_FLASH_INCLUDED
__HEADER_ACCESS_BDM_FLASH_INCLUDED = TRUE





__SUBSCRIBE_ACCESS_BDM_FLASH = 



ifneq ($(wildcard $(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/BDM_FLASH),)

ifneq ($(VSBL_NAME),)
ifeq ($(VSBL_NAME),$(filter $(VSBL_NAME), BDM_FLASH))
VSBL_LKH += $(OPTION_INCLUDE_DIR)$(VSB_KERNEL_PROTECTED_INCLUDE_DIR)/BDM_FLASH
endif
endif

endif

endif

