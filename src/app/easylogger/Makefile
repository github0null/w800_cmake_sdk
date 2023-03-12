TOP_DIR = ../../..
sinclude $(TOP_DIR)/tools/w800/conf.mk

ifndef PDIR
GEN_LIBS = libeasylogger$(LIB_EXT)
endif

INCLUDES += -I./easylogger/inc \
			-I./easylogger/port

CSRCS += ./easylogger/src/elog_buf.c \
		 ./easylogger/src/elog_utils.c \
		 ./easylogger/src/elog.c \
		 ./easylogger/port/elog_port.c

#DEFINES +=

sinclude $(TOP_DIR)/tools/w800/rules.mk
INCLUDES := $(INCLUDES) -I $(PDIR)include
PDIR := ../$(PDIR)
sinclude $(PDIR)Makefile
