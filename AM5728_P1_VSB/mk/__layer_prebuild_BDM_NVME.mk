
	
# this file is automatically generated by mk/krnl/defs.layers.mk. Please do not edit

__FILE_COPIED += $(__FILES_COPIED_BDM_NVME)
__FILES_GENERATED += $(__FILES_GENERATED_BDM_NVME)




	
	

	
	


	
	
	
	
	
	
	
	
	

	

	
	
	
	
	
	
	


	


	


	

	
BUILD : BDM_NVME_src_llvm__BUILD

.PHONY : BDM_NVME_src_llvm__BUILD

__BUILD_FB_IDS += kernel_top_BDM_NVME_src_llvm

BDM_NVME_src_llvm__BUILD : 
	@ echo building BUILD layer BDM_NVME directory src
	+ @ cd C:/WindRiver2021-07/vxworks/21.07/os/storage/bdm/nvme/src && C:/WindRiver2021-07/vxworks/21.07/host/x86-win64/bin/make _mk CPU=ARMARCH7 TOOL=llvm TOOL_VERSION=llvm_2016_04 _CC_VERSION=llvm_11_1_0_1 SPACE=kernel __LAYER_CC_WARNINGS=CC_WARNINGS_HIGH __LAYER_C++_WARNINGS= _VSB_CONFIG_ADDEDCFLAGS="" _WRS_CONFIG_APP_TOOL=llvm VSBL_NAME=BDM_NVME VSB_DIR=$(VSB_DIR) _WRS_CONFIG_FP=hard _WRS_CLI_CFLAGS="-I. " _FB_ID=kernel_top_BDM_NVME_src_llvm BSPNAME=ti_sitara_ctxa15_branson_2_1_0_0 BUILDSTAGE=BUILD


	

	

	

	

	

	

	


	
# copying directory cdf to $(VSB_DIR)/krnl/cdf




PRENOBUILD : $(VSB_DIR)/krnl/cdf/40vxbNvme.cdf

__FILES_TO_COPY_BDM_NVME += $(VSB_DIR)/krnl/cdf/40vxbNvme.cdf

ifdef __TARGET_RULE_$(VSB_DIR)/krnl/cdf/40vxbNvme.cdf
$(error "while processing layer= BDM_NVME target $(VSB_DIR)/krnl/cdf/40vxbNvme.cdf already defined by layer $(__TARGET_RULE_$(VSB_DIR)/krnl/cdf_40vxbNvme.cdf)")
else
__TARGET_RULE_$(VSB_DIR)/krnl/cdf/40vxbNvme.cdf = BDM_NVME
endif





 

$(VSB_DIR)/krnl/cdf/40vxbNvme.cdf : C:/WindRiver2021-07/vxworks/21.07/os/storage/bdm/nvme/cdf/40vxbNvme.cdf | $(VSB_DIR)/krnl/cdf
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif


	# PRENOBUILD=(PRENOBUILD) BDM_NVME=(layer) cdf=(dir)

PRENOBUILD_BDM_NVME_cdf_FILES = cdf/40vxbNvme.cdf

PRENOBUILD_BDM_NVME_cdf_DIR = C:/WindRiver2021-07/vxworks/21.07/os/storage/bdm/nvme

PRENOBUILD_FILES += $(addprefix $(PRENOBUILD_BDM_NVME_cdf_DIR)/,$(PRENOBUILD_BDM_NVME_cdf_FILES))

PRENOBUILD : PRENOBUILD_BDM_NVME

PRENOBUILD_BDM_NVME : cdf_PRENOBUILD_BDM_NVME

cdf_PRENOBUILD_BDM_NVME : $(VSB_DIR)/krnl/cdf/PRENOBUILD_BDM_NVME_cdf.cdf

__FILES_TO_GENERATE_BDM_NVME += $(VSB_DIR)/krnl/cdf/PRENOBUILD_BDM_NVME_cdf.cdf

$(VSB_DIR)/krnl/cdf/PRENOBUILD_BDM_NVME_cdf.cdf : | $(VSB_DIR)/krnl/cdf

$(VSB_DIR)/krnl/cdf/PRENOBUILD_BDM_NVME_cdf.cdf : $(VSB_DIR)/h/config/auto.conf
	$(file >$(VSB_DIR)/krnl/cdf/PRENOBUILD_BDM_NVME_cdf.tmp,$(call __vsb_tmpl_cdf_inter,$(addprefix $(PRENOBUILD_BDM_NVME_cdf_DIR)/,$(sort $(PRENOBUILD_BDM_NVME_cdf_FILES))),BDM_NVME))
	$(CDFCOMP) -i $(VSB_DIR)/krnl/cdf/PRENOBUILD_BDM_NVME_cdf.tmp -o $@ -cpp "$(CPP) $(__OPTION_LANG_CDF)" -cpu ARMARCH7 -layer BDM_NVME -vsb $(VSB_DIR)
	rm -f $(VSB_DIR)/krnl/cdf/PRENOBUILD_BDM_NVME_cdf.tmp

	
	
	
	

	
# copying directory cfg to $(VSB_DIR)/krnl/configlette




PRENOBUILD : $(VSB_DIR)/krnl/configlette/usrNvme.c

__FILES_TO_COPY_BDM_NVME += $(VSB_DIR)/krnl/configlette/usrNvme.c

ifdef __TARGET_RULE_$(VSB_DIR)/krnl/configlette/usrNvme.c
$(error "while processing layer= BDM_NVME target $(VSB_DIR)/krnl/configlette/usrNvme.c already defined by layer $(__TARGET_RULE_$(VSB_DIR)/krnl/configlette_usrNvme.c)")
else
__TARGET_RULE_$(VSB_DIR)/krnl/configlette/usrNvme.c = BDM_NVME
endif





 

$(VSB_DIR)/krnl/configlette/usrNvme.c : C:/WindRiver2021-07/vxworks/21.07/os/storage/bdm/nvme/cfg/usrNvme.c | $(VSB_DIR)/krnl/configlette
ifdef __LAYER_DEPENDENCY_TEST
	cp -rfLs $< $@
else
	cp -rfL $< $@
endif



	

	
__DIR_TARGETS += $(__DIR_TARGETS_BDM_NVME)

__DIR_TARGETS_BDM_NVME += $(VSB_DIR)/krnl/cdf $(VSB_DIR)/krnl/configlette C:/Stream_ACEPRO_Test/ACEPRO_Test/AM5728_P1_VSB/krnl/cdf C:/Stream_ACEPRO_Test/ACEPRO_Test/AM5728_P1_VSB/krnl/configlette C:/Stream_ACEPRO_Test/ACEPRO_Test/AM5728_P1_VSB/krnl/h C:/Stream_ACEPRO_Test/ACEPRO_Test/AM5728_P1_VSB/share/h C:/Stream_ACEPRO_Test/ACEPRO_Test/AM5728_P1_VSB/usr/h C:/Stream_ACEPRO_Test/ACEPRO_Test/AM5728_P1_VSB/vsblCdf

