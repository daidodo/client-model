BIN_DIR := ../bin
OUT_TARGET := $(BIN_DIR)/srcc
LIB_TARGET := $(BIN_DIR)/libsrc.a
SO_TARGET :=  $(BIN_DIR)/libsrc.so
INC_TARGET := SRC_language.h

INSTALL_OUT_DIR := /usr/local/bin
INSTALL_LIB_DIR := /usr/lib
INSTALL_INC_DIR := /usr/include

CC := g++
YFLAGS := -d
INCLUDE := -I./
CXXFLAGS := -g $(INCLUDE)
CFLAGS := $(CXXFLAGS)
ARFLAGS := cr
CP := cp -f

LEX_SRC := $(wildcard *.l)
YACC_SRC := $(wildcard *.y)
CPP_SRC := $(wildcard *.cpp) $(wildcard common/*.cpp)

RM_SRC := y.tab.h $(YACC_SRC:.y=.c) $(LEX_SRC:.l=.c)

OBJS := $(YACC_SRC:.y=.o) $(LEX_SRC:.l=.o) $(CPP_SRC:.cpp=.o)

DEPS := $(CPP_SRC:.cpp=.d)

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

out : $(OUT_TARGET)

lib : $(LIB_TARGET)

so : $(SO_TARGET)

deps : $(DEPS)

%.d : %.cpp
	@$(CXX) -MM $(CXXFLAGS) -o $*.d $<

$(OUT_TARGET) : $(OBJS)
	$(CXX) -o $@ $^

$(LIB_TARGET) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(SO_TARGET) : $(OBJS)
	$(CXX) -shared -fPIC -o $@ $^

cleandist : 
	$(RM) *.o common/*.o $(RM_SRC)
	$(RM) *.d common/*.d

clean : cleandist
	$(RM) $(BIN_DIR)/*

love : clean all

.PHONEY : all out lib so deps cleandist clean love

sinclude $(DEPS)
