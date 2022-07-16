#!/usr/bin/tcsh
./makecmd
./characterize $argv[1]
cp op.txt _op.txt
cp op2.txt _op2.txt
./factorize
