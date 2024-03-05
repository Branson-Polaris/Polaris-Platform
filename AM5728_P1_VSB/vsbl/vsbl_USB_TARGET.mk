# Automatically generated file: do not edit

##########################
# USB_TARGET Section
##########################


ifdef _WRS_CONFIG_USB_TARGET
VSBL_USB_TARGET_SRC = 
VSBL_USB_TARGET_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_TARGET_2_0_8_0
ifdef _WRS_CONFIG_USB_MSC
VSBL_USB_TARGET_SRC += USB_MSC
endif
ifdef _WRS_CONFIG_USB_NET
VSBL_USB_TARGET_SRC += USB_NET
endif
VSBL_USB_TARGET_SRC += USB_TARGET
USB_TARGET_FASTBUILD = YES
VSBL_USB_TARGET_PATH = $(WIND_BASE)/os/connectivity/usb/target
VSBL_USB_TARGET_VERSION = USB_2_0_8_0_TARGET_2_0_8_0
endif
endif

