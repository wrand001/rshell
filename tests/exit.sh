#!/bin/sh

exit

echo 1 || exit

false || exit

echo 1 && exit

false && exit

exit exit exit

echo 1 ; exit

echo 1 ; exit && echo 1

echo 1 ; exit || echo 2
