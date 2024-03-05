# Automatically generated file: do not edit

##########################
# USB_TYPEC Section
##########################


ifdef _WRS_CONFIG_USB_TYPEC
VSBL_USB_TYPEC_SRC = 
VSBL_USB_TYPEC_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_TYPEC_2_0_8_0
VSBL_USB_TYPEC_SRC += USB_TYPEC
VSBL_USB_TYPEC_DEPEND += VXBUS
USB_TYPEC_FASTBUILD = YES
VSBL_USB_TYPEC_PATH = $(WIND_BASE)/os/connectivity/usb/typec
VSBL_USB_TYPEC_VERSION = USB_2_0_8_0_TYPEC_2_0_8_0
endif
endif

