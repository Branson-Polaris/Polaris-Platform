# Automatically generated file: do not edit

##########################
# USER_MANAGEMENT_POLICY Section
##########################


ifdef _WRS_CONFIG_USER_MANAGEMENT_POLICY
VSBL_USER_MANAGEMENT_POLICY_SRC = 
VSBL_USER_MANAGEMENT_POLICY_DEPEND = 

ifdef _WRS_CONFIG_USER_MANAGEMENT_2_0_1_7_POLICY_2_0_1_7
VSBL_USER_MANAGEMENT_POLICY_SRC += USER_MANAGEMENT_POLICY
VSBL_USER_MANAGEMENT_POLICY_DEPEND += SECURITY_MISC_SEC_CRYPTO
VSBL_USER_MANAGEMENT_POLICY_DEPEND += SECURITY_MISC_SEC_HASH
VSBL_USER_MANAGEMENT_POLICY_DEPEND += UTILS_UTF
USER_MANAGEMENT_POLICY_FASTBUILD = YES
VSBL_USER_MANAGEMENT_POLICY_PATH = $(WIND_BASE)/os/security/user_management/user_management_policy
VSBL_USER_MANAGEMENT_POLICY_VERSION = USER_MANAGEMENT_2_0_1_7_POLICY_2_0_1_7
endif
endif

