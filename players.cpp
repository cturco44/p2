// PROJECT IDENTIFIER: 9504853406CBAC39EE89AA3AD238AA12CA198043
//  players.cpp
//  p2
//
//  Created by Connor Turco on 5/19/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include "players.h"
#include <vector>
#include <cmath>

void circular::reserve(unsigned int n) {
    firstn.reserve(n);
}
void circular::push(Zombie* z) {
    if(firstn.size() != firstn.capacity()) {
        firstn.push_back(z);
        //If this is the last element to be added
        if(firstn.size() == firstn.capacity()) {
            lastn = firstn;
            it = lastn.begin();
        }
        return;
    }
    *it = z;
    ++it;
    if(it == lastn.end()) {
        it = lastn.begin();
    }
    
}
void Median::push(unsigned int data) {
    //if both empty, push to smaller heap
    if(min_heap.empty() && max_heap.empty()) {
        max_heap.push(data);
    }
    //push to min heap if its greater than max heap
    if(data > max_heap.top()) {
        min_heap.push(data);
    }
    else {
        max_heap.push(data);
    }
    int max_heap_size = static_cast<int>(max_heap.size());
    int min_heap_size = static_cast<int>(min_heap.size());
    
    if (max_heap_size - min_heap_size > 1) {
        min_heap.push(max_heap.top());
        max_heap.pop();
    }
    if(min_heap_size - max_heap_size > 1) {
        max_heap.push(min_heap.top());
        min_heap.pop();
    }
    
}
unsigned int Median::get_median() {
    if(max_heap.size() > min_heap.size()) {
        return max_heap.top();
    }
    if(min_heap.size() > max_heap.size()) {
        return min_heap.top();
    }
    return max_heap.top() + min_heap.top() / 2;
}

