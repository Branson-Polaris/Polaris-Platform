# Automatically generated file: do not edit

##########################
# USB_PCHUDC Section
##########################


ifdef _WRS_CONFIG_USB_PCHUDC
VSBL_USB_PCHUDC_SRC = 
VSBL_USB_PCHUDC_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_CTLR_2_0_8_0_PCHUDC_2_0_8_0
VSBL_USB_PCHUDC_SRC += USB_PCHUDC
VSBL_USB_PCHUDC_DEPEND += USB_PHY
VSBL_USB_PCHUDC_DEPEND += USB_TARGET
USB_PCHUDC_FASTBUILD = YES
VSBL_USB_PCHUDC_PATH = $(WIND_BASE)/os/connectivity/usb/ctlr/pchudc
VSBL_USB_PCHUDC_VERSION = USB_2_0_8_0_CTLR_2_0_8_0_PCHUDC_2_0_8_0
endif
endif

