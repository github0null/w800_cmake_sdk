TOP_DIR = ../../..
sinclude $(TOP_DIR)/tools/w800/conf.mk

ifndef PDIR
GEN_LIBS = liblwrb$(LIB_EXT)
endif

INCLUDES += -I./lwrb/src/include
INCLUDES += -I./lwrb/src/include/lwrb

CSRCS += ./lwrb/src/lwrb/lwrb.c

#DEFINES +=

sinclude $(TOP_DIR)/tools/w800/rules.mk
INCLUDES := $(INCLUDES) -I $(PDIR)include
PDIR := ../$(PDIR)
sinclude $(PDIR)Makefile
