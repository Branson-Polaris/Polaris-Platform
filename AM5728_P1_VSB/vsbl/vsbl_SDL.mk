# Automatically generated file: do not edit

##########################
# SDL Section
##########################


ifdef _WRS_CONFIG_SDL
VSBL_SDL_SRC = 
VSBL_SDL_DEPEND = 

ifdef _WRS_CONFIG_SDL_2_0_5_17
VSBL_SDL_SRC += SDL
ifdef _WRS_CONFIG_ARCH_i86
VSBL_SDL_DEPEND += MESA
endif
VSBL_SDL_DEPEND += FBDEV
VSBL_SDL_DEPEND += KHRONOS
VSBL_SDL_DEPEND += RASTER_VG
SDL_FASTBUILD = YES
VSBL_SDL_PATH = $(WIND_BASE)/contrib/sdl-2.0.5
VSBL_SDL_VERSION = SDL_2_0_5_17
endif
endif

