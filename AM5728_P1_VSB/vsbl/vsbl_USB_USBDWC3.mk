# Automatically generated file: do not edit

##########################
# USB_USBDWC3 Section
##########################


ifdef _WRS_CONFIG_USB_USBDWC3
VSBL_USB_USBDWC3_SRC = 
VSBL_USB_USBDWC3_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_CTLR_2_0_8_0_USBDWC3_2_0_8_0
VSBL_USB_USBDWC3_SRC += USB_USBDWC3
VSBL_USB_USBDWC3_DEPEND += USB_PHY
VSBL_USB_USBDWC3_DEPEND += USB_XHCI
USB_USBDWC3_FASTBUILD = YES
VSBL_USB_USBDWC3_PATH = $(WIND_BASE)/os/connectivity/usb/ctlr/dwc3
VSBL_USB_USBDWC3_VERSION = USB_2_0_8_0_CTLR_2_0_8_0_USBDWC3_2_0_8_0
endif
endif
