//  PROJECT IDENTIFIER: 9504853406CBAC39EE89AA3AD238AA12CA198043
//  testMedian.cpp
//  p2
//
//  Created by Connor Turco on 5/23/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "players.h"
#include <vector>
#include <cassert>

int main() {
    Median med;
    med.push(0);
    assert(med.get_median() == 0);
    med.push(5);
    assert(med.get_median() == 2);
    med.push(7);
    assert(med.get_median() == 5);
    med.push(22);
    assert(med.get_median() == 6);
    med.push(2);
    assert(med.get_median() == 5);
    med.push(3);
    assert(med.get_median() == 4);
    med.push(99);
    assert(med.get_median() == 5);
    return 0;
}
