# Automatically generated file: do not edit

##########################
# USB_FSLDR Section
##########################


ifdef _WRS_CONFIG_USB_FSLDR
VSBL_USB_FSLDR_SRC = 
VSBL_USB_FSLDR_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_CTLR_2_0_8_0_FSLDR_2_0_8_0
VSBL_USB_FSLDR_SRC += USB_FSLDR
VSBL_USB_FSLDR_DEPEND += USB_PHY
VSBL_USB_FSLDR_DEPEND += USB_TARGET
USB_FSLDR_FASTBUILD = YES
VSBL_USB_FSLDR_PATH = $(WIND_BASE)/os/connectivity/usb/ctlr/fsldr
VSBL_USB_FSLDR_VERSION = USB_2_0_8_0_CTLR_2_0_8_0_FSLDR_2_0_8_0
endif
endif

