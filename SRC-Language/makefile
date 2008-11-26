OUT_TARGET := a.out
LIB_TARGET := libsrc.a
SO_TARGET :=  libsrc.so

CC := g++
YFLAGS := -d
INCLUDE := -I./
CXXFLAGS := -g $(INCLUDE)
CFLAGS := $(CXXFLAGS)
ARFLAGS := cr

LEX_SRC := $(wildcard *.l)
YACC_SRC := $(wildcard *.y)
CPP_SRC := $(wildcard *.cpp) $(wildcard common/*.cpp)

RM_SRC := y.tab.h $(YACC_SRC:.y=.c) $(LEX_SRC:.l=.c)

OBJS := $(YACC_SRC:.y=.o) $(LEX_SRC:.l=.o) $(CPP_SRC:.cpp=.o)

DEPS := $(OBJS:.o=.d)

all : out lib so

out : $(OUT_TARGET)

lib : $(LIB_TARGET)

so : $(SO_TARGET)

$(OUT_TARGET) : $(OBJS)
	$(CXX) -o $@ $^

$(LIB_TARGET) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(SO_TARGET) : $(OBJS)
	$(CXX) -shared -fPIC -o $@ $^

cleandist : 
	$(RM) *.o common/*.o $(RM_SRC)

clean : cleandist
	$(RM) $(OUT_TARGET) $(LIB_TARGET) $(SO_TARGET)

love : clean all

sinclude $(DEPS)

.PHONEY : all out lib so cleandist clean love