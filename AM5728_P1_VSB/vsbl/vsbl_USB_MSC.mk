# Automatically generated file: do not edit

##########################
# USB_MSC Section
##########################


ifdef _WRS_CONFIG_USB_MSC
VSBL_USB_MSC_SRC = 
VSBL_USB_MSC_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_TARGET_2_0_8_0_MSC_2_0_8_0
VSBL_USB_MSC_SRC += USB_MSC
VSBL_USB_MSC_DEPEND += BDM
VSBL_USB_MSC_DEPEND += FS
VSBL_USB_MSC_DEPEND += SERVICE_ERF
USB_MSC_FASTBUILD = YES
VSBL_USB_MSC_PATH = $(WIND_BASE)/os/connectivity/usb/target/function/msc
VSBL_USB_MSC_VERSION = USB_2_0_8_0_TARGET_2_0_8_0_MSC_2_0_8_0
endif
endif

