#!/bin/sh

touch testingfile

mkdir testingdir

#testing files

test -e testingfile && echo good1

test -f testingfile && echo good2

test -d testingfile && echo good3

test testingfile && echo good4

[ -e testingfile ] && echo good5

[ -f testingfile ] && echo good6

[ -d testingfile ] && echo good7

[ testingfile ] && echo good8

#testing directories

test -e testingdir && echo good9

test -f testingdir && echo good10

test -d testingdir && echo good11

test testingdir && echo good12

[ -e testingdir ] && echo good13

[ -f testingdir ] && echo good14

[ -d testingdir ] && echo good15

[ testingdir ] && echo good16

#testing non-existing file/directory

test -e idontexist && echo good17

test -f idontexist && echo good18

test -d idontexist && echo good19

test idontexist && echo good20

[ -e idontexist ] && echo good21

[ -f idontexist ] && echo good22

[ -d idontexist ] && echo good23

[ idontexist ] && echo good24

#bug exploration

test -efd testingdir && echo good25
test - testingdir && echo good26
test -h testingfile && echo good27
[-efd testingdir] && echo good28
[- testingdir] && echo good29
[-h testingfile] && echo good30

[testingfile -f] && echo good31
[whatever && good32
whatever] && good33


