#!/bin/sh

lex -t scanner.l > scanner.cpp
yacc -d grammar.y
mv -f y.tab.c grammar.cpp