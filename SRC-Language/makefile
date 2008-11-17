TARGET := a.out

CC := g++
YFLAGS := -d
INCLUDE := -I./
CXXFLAGS := -g $(INCLUDE)
CFLAGS := $(CXXFLAGS)


LEX_SRC := $(wildcard *.l)
YACC_SRC := $(wildcard *.y)
CPP_SRC := $(wildcard *.cpp) $(wildcard common/*.cpp)

RM_SRC := y.tab.h $(YACC_SRC:.y=.c) $(LEX_SRC:.l=.c)

OBJS := $(YACC_SRC:.y=.o) $(LEX_SRC:.l=.o) $(CPP_SRC:.cpp=.o)

DEPS := $(OBJS:.o=.d)

all : $(TARGET)

$(TARGET) : $(OBJS) #$(YACC_OBJ) $(LEX_OBJ) $(CPP_OBJ)
	$(CXX) -o $@ $^

clean :
	$(RM) *.o common/*.o $(RM_SRC)
	$(RM) $(TARGET)

love : clean all

sinclude $(DEPS)

.PHONEY : all clean love
