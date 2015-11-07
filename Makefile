all: rshell

rshell:
	g++ -Wall -Werror -ansi -pedantic -o rshell src/rshell.cpp
