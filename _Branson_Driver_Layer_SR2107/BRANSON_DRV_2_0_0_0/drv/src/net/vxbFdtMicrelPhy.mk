# Makefile - makefile for vxbFdtMicrelPhy.c

# Copyright (c) 2014 Wind River Systems, Inc.
#
# The right to copy, distribute, modify or otherwise make use
# of this software may be licensed only pursuant to the terms
# of an applicable Wind River license agreement.
#
# modification history
# --------------------
# 08oct14,m_w  only build this driver when FDT was used. (V7PRO-1297)
# 15aug14,m_w  created. (V7PRO-1195)

ifdef _WRS_CONFIG_FDT
OBJS_COMMON     += vxbFdtMicrelPhy.o
DOC_FILES       += vxbFdtMicrelPhy.c
endif

