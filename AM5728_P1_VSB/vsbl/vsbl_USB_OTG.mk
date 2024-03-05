# Automatically generated file: do not edit

##########################
# USB_OTG Section
##########################


ifdef _WRS_CONFIG_USB_OTG
VSBL_USB_OTG_SRC = 
VSBL_USB_OTG_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_OTG_2_0_8_0
VSBL_USB_OTG_SRC += USB_OTG
VSBL_USB_OTG_DEPEND += USB_HOST
VSBL_USB_OTG_DEPEND += USB_TARGET
USB_OTG_FASTBUILD = YES
VSBL_USB_OTG_PATH = $(WIND_BASE)/os/connectivity/usb/otg
VSBL_USB_OTG_VERSION = USB_2_0_8_0_OTG_2_0_8_0
endif
endif

