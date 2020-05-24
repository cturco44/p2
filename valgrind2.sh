#!/bin/bash

#  valgrind2.sh
#  p2
#
#  Created by Connor Turco on 5/24/20.
#  Copyright © 2020 Connor Turco. All rights reserved.

g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic  -g3 -DDEBUG tests.cpp -o tests_queue
