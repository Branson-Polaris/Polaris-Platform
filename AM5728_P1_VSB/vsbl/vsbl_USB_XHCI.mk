# Automatically generated file: do not edit

##########################
# USB_XHCI Section
##########################


ifdef _WRS_CONFIG_USB_XHCI
VSBL_USB_XHCI_SRC = 
VSBL_USB_XHCI_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_CTLR_2_0_8_0_XHCI_2_0_8_0
VSBL_USB_XHCI_SRC += USB_XHCI
VSBL_USB_XHCI_DEPEND += USB_HOST
VSBL_USB_XHCI_DEPEND += USB_PHY
USB_XHCI_FASTBUILD = YES
VSBL_USB_XHCI_PATH = $(WIND_BASE)/os/connectivity/usb/ctlr/xhci
VSBL_USB_XHCI_VERSION = USB_2_0_8_0_CTLR_2_0_8_0_XHCI_2_0_8_0
endif
endif

