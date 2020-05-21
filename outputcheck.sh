#!/bin/bash

#  outputcheck.sh
#  p2
#
#  Created by Connor Turco on 5/21/20.
#  Copyright © 2020 Connor Turco. All rights reserved.

make debug
echo -----------------------------------------------------------------------
echo Spec Test
echo ........................................................................
echo
./zombbb_debug -v -m -s 10 < specin.txt > testy.txt
sdiff testy.txt speccorrect.txt

echo -----------------------------------------------------------------------
echo Test 0
echo ........................................................................
echo
./zombbb_debug v < test-0-v.txt > testy.txt
sdiff testy.txt test0correct.txt

echo -----------------------------------------------------------------------
echo Test 1
echo ........................................................................
echo
./zombbb_debug -s 10 < test-1-s.txt > testy.txt
sdiff testy.txt test1correct.txt

echo -----------------------------------------------------------------------
echo Test 2
echo ........................................................................
echo
./zombbb_debug -m < test-2-m.txt > testy.txt
sdiff testy.txt test2correct.txt

make clean








