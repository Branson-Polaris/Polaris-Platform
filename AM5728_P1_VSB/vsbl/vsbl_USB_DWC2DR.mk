# Automatically generated file: do not edit

##########################
# USB_DWC2DR Section
##########################


ifdef _WRS_CONFIG_USB_DWC2DR
VSBL_USB_DWC2DR_SRC = 
VSBL_USB_DWC2DR_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_CTLR_2_0_8_0_DWC2DR_2_0_8_0
VSBL_USB_DWC2DR_SRC += USB_DWC2DR
VSBL_USB_DWC2DR_DEPEND += USB_HOST
VSBL_USB_DWC2DR_DEPEND += USB_PHY
USB_DWC2DR_FASTBUILD = YES
VSBL_USB_DWC2DR_PATH = $(WIND_BASE)/os/connectivity/usb/ctlr/dwc2dr
VSBL_USB_DWC2DR_VERSION = USB_2_0_8_0_CTLR_2_0_8_0_DWC2DR_2_0_8_0
endif
endif

