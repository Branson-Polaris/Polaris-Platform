# Automatically generated file: do not edit

##########################
# USB_PHY Section
##########################


ifdef _WRS_CONFIG_USB_PHY
VSBL_USB_PHY_SRC = 
VSBL_USB_PHY_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_PHY_2_0_8_0
VSBL_USB_PHY_SRC += USB_PHY
VSBL_USB_PHY_DEPEND += VXBUS
USB_PHY_FASTBUILD = YES
VSBL_USB_PHY_PATH = $(WIND_BASE)/os/connectivity/usb/phy
VSBL_USB_PHY_VERSION = USB_2_0_8_0_PHY_2_0_8_0
endif
endif

