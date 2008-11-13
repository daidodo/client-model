TARGET := a.out

CC := g++
YFLAGS := -d

LEX_SRC := $(wildcard *.l)
YACC_SRC := $(wildcard *.y)
CPP_SRC := $(wildcard *.cpp) $(wildcard common/*.cpp)

OBJS := $(YACC_SRC:.y=.o) $(LEX_SRC:.l=.o) $(CPP_SRC:.cpp=.o)

DEPS := $(OBJS:.o=.d)

all : $(TARGET)

$(TARGET) : $(OBJS) #$(YACC_OBJ) $(LEX_OBJ) $(CPP_OBJ)
	$(CXX) -o $@ $^

clean :
	$(RM) *.o common/*.o y.tab.h
	$(RM) $(TARGET)

love : clean all

sinclude $(DEPS)

.PHONEY : all clean love
