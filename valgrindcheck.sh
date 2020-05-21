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
valgrind ./zombbb_debug -v -m -s 10 < specin.txt

echo -----------------------------------------------------------------------
echo Test 0
echo ........................................................................
echo
valgrind ./zombbb_debug v < test-0-v.txt

echo -----------------------------------------------------------------------
echo Test 1
echo ........................................................................
echo
valgrind ./zombbb_debug -s 10 < test-1-s.txt

echo -----------------------------------------------------------------------
echo Test 2
echo ........................................................................
echo
valgrind ./zombbb_debug -m < test-2-m.txt

make clean

