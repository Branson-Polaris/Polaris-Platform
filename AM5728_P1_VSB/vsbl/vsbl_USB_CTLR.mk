# Automatically generated file: do not edit

##########################
# USB_CTLR Section
##########################


ifdef _WRS_CONFIG_USB_CTLR
VSBL_USB_CTLR_SRC = 
VSBL_USB_CTLR_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_CTLR_2_0_8_0
ifdef _WRS_CONFIG_USB_CDNSUSB3
VSBL_USB_CTLR_SRC += USB_CDNSUSB3
endif
ifdef _WRS_CONFIG_USB_DWC2DR
VSBL_USB_CTLR_SRC += USB_DWC2DR
endif
ifdef _WRS_CONFIG_USB_EHCI
VSBL_USB_CTLR_SRC += USB_EHCI
endif
ifdef _WRS_CONFIG_USB_FSLDR
VSBL_USB_CTLR_SRC += USB_FSLDR
endif
ifdef _WRS_CONFIG_USB_MHDRC
VSBL_USB_CTLR_SRC += USB_MHDRC
endif
ifdef _WRS_CONFIG_USB_OHCI
VSBL_USB_CTLR_SRC += USB_OHCI
endif
ifdef _WRS_CONFIG_USB_PCHUDC
VSBL_USB_CTLR_SRC += USB_PCHUDC
endif
ifdef _WRS_CONFIG_USB_PLX
VSBL_USB_CTLR_SRC += USB_PLX
endif
ifdef _WRS_CONFIG_USB_RZN1
VSBL_USB_CTLR_SRC += USB_RZN1
endif
ifdef _WRS_CONFIG_USB_UHCI
VSBL_USB_CTLR_SRC += USB_UHCI
endif
ifdef _WRS_CONFIG_USB_USBDWC3
VSBL_USB_CTLR_SRC += USB_USBDWC3
endif
ifdef _WRS_CONFIG_USB_XHCI
VSBL_USB_CTLR_SRC += USB_XHCI
endif
VSBL_USB_CTLR_SRC += USB_CTLR
USB_CTLR_FASTBUILD = YES
VSBL_USB_CTLR_PATH = $(WIND_BASE)/os/connectivity/usb/ctlr
VSBL_USB_CTLR_VERSION = USB_2_0_8_0_CTLR_2_0_8_0
endif
endif

