#!/bin/sh

lex -t scanner.l > scanner_src.cpp
yacc -d grammar.y
mv -f y.tab.c grammar_src.cpp