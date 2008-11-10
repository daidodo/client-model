TARGET := a.out

CC := g++
YFLAGS := -d

LEX_SRC := $(wildcard *.l)
YACC_SRC := $(wildcard *.y)

LEX_OBJ := $(LEX_SRC:.l=.o)
YACC_OBJ := $(YACC_SRC:.y=.o)

all : $(TARGET)

$(TARGET) : $(YACC_OBJ) $(LEX_OBJ)
	$(CXX) -o $@ $^

clean :
	$(RM) *.o y.tab.h
	$(RM) $(TARGET)

love : clean all

.PHONEY : all clean love