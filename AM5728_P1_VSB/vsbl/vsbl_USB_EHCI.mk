# Automatically generated file: do not edit

##########################
# USB_EHCI Section
##########################


ifdef _WRS_CONFIG_USB_EHCI
VSBL_USB_EHCI_SRC = 
VSBL_USB_EHCI_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_CTLR_2_0_8_0_EHCI_2_0_8_0
VSBL_USB_EHCI_SRC += USB_EHCI
VSBL_USB_EHCI_DEPEND += USB_HOST
VSBL_USB_EHCI_DEPEND += USB_PHY
USB_EHCI_FASTBUILD = YES
VSBL_USB_EHCI_PATH = $(WIND_BASE)/os/connectivity/usb/ctlr/ehci
VSBL_USB_EHCI_VERSION = USB_2_0_8_0_CTLR_2_0_8_0_EHCI_2_0_8_0
endif
endif

