# Automatically generated file: do not edit

##########################
# USB_MHDRC Section
##########################


ifdef _WRS_CONFIG_USB_MHDRC
VSBL_USB_MHDRC_SRC = 
VSBL_USB_MHDRC_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_CTLR_2_0_8_0_MHDRC_2_0_8_0
VSBL_USB_MHDRC_SRC += USB_MHDRC
VSBL_USB_MHDRC_DEPEND += USB_OTG
VSBL_USB_MHDRC_DEPEND += USB_PHY
VSBL_USB_MHDRC_DEPEND += USB_TARGET
USB_MHDRC_FASTBUILD = YES
VSBL_USB_MHDRC_PATH = $(WIND_BASE)/os/connectivity/usb/ctlr/mhdrc
VSBL_USB_MHDRC_VERSION = USB_2_0_8_0_CTLR_2_0_8_0_MHDRC_2_0_8_0
endif
endif

