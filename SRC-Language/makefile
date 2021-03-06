BIN_DIR := bin
OUT_TARGET := $(BIN_DIR)/srcc
LIB_TARGET := $(BIN_DIR)/libsrc.a
SO_TARGET :=  $(BIN_DIR)/libsrc.so
INC_TARGET := SRC_language.h

INSTALL_OUT_DIR := /usr/local/bin
INSTALL_LIB_DIR := /usr/lib
INSTALL_INC_DIR := /usr/include

DEBUG := -g
#RELEASE := -O3 -DNDEBUG

CC := g++
INCLUDE := -I./
CXXFLAGS := -Wall -fPIC $(INCLUDE) $(DEBUG) $(RELEASE)
CFLAGS := $(CXXFLAGS)
ARFLAGS := cr
CP := cp -f

CPP_SRC := $(wildcard *.cpp) $(wildcard common/*.cpp)

RM_SRC := y.tab.h grammar_src.cpp scanner_src.cpp
OBJS := $(CPP_SRC:.cpp=.o)
DEPS := $(CPP_SRC:.cpp=.d)

CXXFLAGS += -MD
CFLAGS += -MD

all : out lib so
	@$(CP) $(INC_TARGET) $(BIN_DIR)

install :
	$(CP) $(OUT_TARGET) $(INSTALL_OUT_DIR)
	$(CP) $(LIB_TARGET) $(SO_TARGET) $(INSTALL_LIB_DIR)
	$(CP) $(INC_TARGET) $(INSTALL_INC_DIR)

uninstall :
	$(RM) $(INSTALL_OUT_DIR)/$(notdir $(OUT_TARGET))
	$(RM) $(INSTALL_LIB_DIR)/$(notdir $(LIB_TARGET))
	$(RM) $(INSTALL_LIB_DIR)/$(notdir $(SO_TARGET))
	$(RM) $(INSTALL_INC_DIR)/$(INC_TARGET)

gen :
	./gen_gram.sh

out : $(OUT_TARGET)

lib : $(LIB_TARGET)

so : $(SO_TARGET)

deps : $(DEPS)

$(OUT_TARGET) : $(OBJS)
	$(CXX) -o $@ $^

$(LIB_TARGET) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(SO_TARGET) : $(OBJS)
	$(CXX) -shared -fPIC -o $@ $^

cleandist : 
	$(RM) *.o common/*.o

clean : cleandist
	$(RM) *.d common/*.d
	$(RM) $(BIN_DIR)/$(INC_TARGET) $(OUT_TARGET) $(LIB_TARGET) $(SO_TARGET)

cleanall : clean
	$(RM) $(RM_SRC)

love : cleandist all

.PHONY : all install uninstall gen out lib so deps cleandist clean cleanall love

ifneq (${MAKECMDGOALS},install)
ifneq (${MAKECMDGOALS},uninstall)
ifneq (${MAKECMDGOALS},clean)
ifneq (${MAKECMDGOALS},cleandist)
ifneq (${MAKECMDGOALS},cleanall)
ifneq (${MAKECMDGOALS},gen)
sinclude $(DEPS)
endif
endif
endif
endif
endif
endif

