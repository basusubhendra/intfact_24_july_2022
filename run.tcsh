#!/usr/bin/tcsh

./factorize $argv[1]
./synthesis.py $argv[1]
