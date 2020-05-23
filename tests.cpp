// PROJECT IDENTIFIER: 9504853406CBAC39EE89AA3AD238AA12CA198043
//  tests.cpp
//  p2
//
//  Created by Connor Turco on 5/22/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//


#include "SortedPQ.h"
#include "UnorderedFastPQ.h"
#include <vector>
#include "Eecs281PQ.h"
#include <iostream>
#include <cassert>
#include <string>
#include "BinaryPQ.h"

using namespace std;
struct HiddenData {
    string data;
};

struct HiddenDataComp {
    bool operator()(const HiddenData &a, const HiddenData &b) const {
        return a.data < b.data;
        // TODO: Finish this functor; when you do, uncomment the
        // parameters in the line above
    }
};
        
void test_sorted_constructor() {
    vector<int> v = {25, 18, 77, 16};
    SortedPQ<int> sorted(v.begin(), v.end());
    UnorderedFastPQ<int> correct(v.begin(), v.end());
    
    for(size_t i = 0; i < v.size(); ++i) {
        assert(sorted.top() == correct.top());
        sorted.pop();
        correct.pop();
    }
    assert(sorted.empty());
    
}
void test_sorted_push() {
    vector<int> v = {25, 18, 77, 16};
    SortedPQ<int> sorted;
    sorted.push(v[0]);
    sorted.push(v[1]);
    sorted.push(v[2]);
    sorted.push(v[3]);
    UnorderedFastPQ<int> correct(v.begin(), v.end());
    for(size_t i = 0; i < v.size(); ++i) {
        assert(sorted.top() == correct.top());
        sorted.pop();
        correct.pop();
    }
    
}
void test_with_struct() {
    HiddenData a;
    a.data = "apple";
    HiddenData b;
    a.data = "banana";
    HiddenData c;
    a.data = "cat";
    SortedPQ<HiddenData, HiddenDataComp> sorted;
    UnorderedFastPQ<HiddenData, HiddenDataComp> correct;
    sorted.push(a);
    sorted.push(b);
    sorted.push(c);
    correct.push(a);
    correct.push(b);
    correct.push(c);
    
    for(size_t i = 0; i < 3; ++i) {
        HiddenData first = correct.top();
        HiddenData second = sorted.top();
        assert(first.data == second.data);
        sorted.pop();
        correct.pop();
    }
    
}
void fix_up_test() {
    vector<int> v = {25, 18, 77, 16};
    BinaryPQ<int> sorted(v.begin(), v.end());
    UnorderedFastPQ<int> correct(v.begin(), v.end());
    
    assert(sorted.size() == 4);
    for(size_t i = 0; i < v.size(); ++i) {
        assert(sorted.top() == correct.top());
        sorted.pop();
        correct.pop();
    }
    assert(sorted.empty());
    
}
int main() {
    test_sorted_constructor();
    test_sorted_push();
    test_with_struct();
    fix_up_test();
    cout << "Tests Successful" << endl;
}

