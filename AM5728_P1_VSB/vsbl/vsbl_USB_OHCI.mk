# Automatically generated file: do not edit

##########################
# USB_OHCI Section
##########################


ifdef _WRS_CONFIG_USB_OHCI
VSBL_USB_OHCI_SRC = 
VSBL_USB_OHCI_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_CTLR_2_0_8_0_OHCI_2_0_8_0
VSBL_USB_OHCI_SRC += USB_OHCI
VSBL_USB_OHCI_DEPEND += USB_HOST
VSBL_USB_OHCI_DEPEND += USB_PHY
USB_OHCI_FASTBUILD = YES
VSBL_USB_OHCI_PATH = $(WIND_BASE)/os/connectivity/usb/ctlr/ohci
VSBL_USB_OHCI_VERSION = USB_2_0_8_0_CTLR_2_0_8_0_OHCI_2_0_8_0
endif
endif

