#!/bin/sh

echo hello ; ls
echo hello || echo goodbye
echo hello && echo goodbye
echo hello || ls -a && whatever || whatever -again ; echo goodbye

echo -e hello || ls -a -R what && ls

echohello||ls||&&;;;echo hello
