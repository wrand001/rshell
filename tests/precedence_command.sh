#!/bin/sh

#testing for normal commands

echo test1

(echo A && echo B) || (echo C && echo D)

echo test2

echo 1 ; (echo 2); echo 3; (echo 4); echo 5

echo test3

echo 1 ; (echo 2; echo 3); echo 4; (echo 5)

echo test4

(echo 1 && echo 2) && echo 3 && (echo 4 && echo 5)

echo test5

echo 1 || (echo 2 || echo 3) || echo 4 || echo 5

echo test6

echo 1 || (echo 2 || echo 3) || (echo 4) || echo 5

echo test7

echo 1 || (echo 2 || echo 3) || echo 4 || (echo 5)

echo test8

echo 1 || (echo 2 && echo 3) || echo 4 && echo 5

echo test9

(echo 1 && echo 2 || echo 3 && echo 4 || echo 5)

echo test10

echo 1 || (echo 2 && echo 3) ; (echo 4 && echo 5) || echo 1 || (echo 2) ; echo 3 || (echo 4 && echo 5)

echo bugs

#bug exploration
((echo 1))

echo 1 ; (echo 2

)))))echo 1  && (((((((echo 2

(echo 1 && (echo 2) && echo 3)

(echo 1 || (echo 2) || echo 3)


