#!/bin/sh

lex -t scanner.l | grep -v "#line" > scanner_src.cpp
yacc -d grammar.y
grep -v "#line" y.tab.c > grammar_src.cpp
rm -f y.tab.c 