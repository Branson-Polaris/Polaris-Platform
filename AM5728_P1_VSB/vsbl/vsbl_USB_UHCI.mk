# Automatically generated file: do not edit

##########################
# USB_UHCI Section
##########################


ifdef _WRS_CONFIG_USB_UHCI
VSBL_USB_UHCI_SRC = 
VSBL_USB_UHCI_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_CTLR_2_0_8_0_UHCI_2_0_8_0
VSBL_USB_UHCI_SRC += USB_UHCI
VSBL_USB_UHCI_DEPEND += USB_HOST
USB_UHCI_FASTBUILD = YES
VSBL_USB_UHCI_PATH = $(WIND_BASE)/os/connectivity/usb/ctlr/uhci
VSBL_USB_UHCI_VERSION = USB_2_0_8_0_CTLR_2_0_8_0_UHCI_2_0_8_0
endif
endif

