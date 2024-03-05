# Automatically generated file: do not edit

##########################
# USB_STORAGE Section
##########################


ifdef _WRS_CONFIG_USB_STORAGE
VSBL_USB_STORAGE_SRC = 
VSBL_USB_STORAGE_DEPEND = 

ifdef _WRS_CONFIG_USB_2_0_8_0_HOST_2_0_8_0_STORAGE_2_0_8_0
VSBL_USB_STORAGE_SRC += USB_STORAGE
VSBL_USB_STORAGE_DEPEND += FS
USB_STORAGE_FASTBUILD = YES
VSBL_USB_STORAGE_PATH = $(WIND_BASE)/os/connectivity/usb/host/class/storage
VSBL_USB_STORAGE_VERSION = USB_2_0_8_0_HOST_2_0_8_0_STORAGE_2_0_8_0
endif
endif

