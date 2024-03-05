# Automatically generated file: do not edit

##########################
# USB_NET Section
##########################


ifdef _WRS_CONFIG_USB_NET
VSBL_USB_NET_SRC = 
VSBL_USB_NET_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_TARGET_2_0_8_0_NET_2_0_8_0
VSBL_USB_NET_SRC += USB_NET
VSBL_USB_NET_DEPEND += END
VSBL_USB_NET_DEPEND += IPNET_COREIP
VSBL_USB_NET_DEPEND += SERVICE_ERF
VSBL_USB_NET_DEPEND += SERVICE_SOCKET
USB_NET_FASTBUILD = YES
VSBL_USB_NET_PATH = $(WIND_BASE)/os/connectivity/usb/target/function/net
VSBL_USB_NET_VERSION = USB_2_0_8_0_TARGET_2_0_8_0_NET_2_0_8_0
endif
endif

