all: rshell

rshell:
	 cp -r /bin/ .; g++ -Wall -Werror -ansi -pedantic -o bin/rshell src/rshell.cpp
