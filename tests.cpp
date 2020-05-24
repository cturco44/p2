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
class IntPtrs {
    public:
        IntPtrs(int* ptr_in) {
        the_ptr = ptr_in;
        }
        int* the_ptr;
};
struct IntPtrsComp {
    bool operator()(const IntPtrs &a, const IntPtrs &b) const {
        return a.the_ptr < b.the_ptr;
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
        
void test_custom_functor() {
    vector<int> v = {25, 18, 77, 16, 88, 47, 89, 84, 272, 394, 98, 36, 2, -7};
    BinaryPQ<int> sorted(v.begin(), v.end());
    UnorderedFastPQ<int> correct(v.begin(), v.end());
    
        
    assert(sorted.size() == 14);
    for(size_t i = 0; i < v.size(); ++i) {
        int sorted_top = sorted.top();
        int correct_top = correct.top();
        
        assert(sorted_top == correct_top);
        sorted.pop();
        correct.pop();
    }
    assert(sorted.empty());
}
    void test_mess_up_queue() {
        BinaryPQ<IntPtrs, IntPtrsComp> test;
        UnorderedFastPQ<IntPtrs, IntPtrsComp> correct;
        vector<int> v = {25, 18, 77, 16, 88, 47, 89, 84, 272, 394, 98, 36, 2, -7};
        for(int i = 0; i < (int)v.size(); ++i) {
            int* ptr = &v[i];
            IntPtrs itptr(ptr);
            test.push(itptr);
        correct.push(itptr);
        
        }
        
        assert(test.size() == 14);
        for(int i = 0; i < 14; ++i) {
            IntPtrs ptrtest = test.top();
            IntPtrs ptrcorrect = correct.top();
            assert(*(ptrtest.the_ptr) == *(ptrcorrect.the_ptr));
            test.pop();
            correct.pop();
        
        }

    }
void test_update_priorities() {
        BinaryPQ<IntPtrs, IntPtrsComp> test;
        UnorderedFastPQ<IntPtrs, IntPtrsComp> correct;
        vector<int> v = {25, 18, 77, 16, 88, 47, 89, 84, 272, 394, 98, 36, 2, -7};
        for(int i = 0; i < (int)v.size(); ++i) {
            int* ptr = &v[i];
            IntPtrs itptr(ptr);
            test.push(itptr);
            correct.push(itptr);
            
            if(v[i] == 77) {
                *(itptr.the_ptr) = 400;
            }
            if(v[i] == 272) {
                *(itptr.the_ptr) = -3;
            }
        
        }
        test.updatePriorities();
        correct.updatePriorities();
        assert(test.size() == 14);
        
        for(int i = 0; i < 14; ++i) {
            IntPtrs ptrtest = test.top();
            IntPtrs ptrcorrect = correct.top();
            assert(*(ptrtest.the_ptr) == *(ptrcorrect.the_ptr));
            test.pop();
            correct.pop();
        
        }
        
}
int main() {
    test_sorted_constructor();
    test_sorted_push();
    test_with_struct();
    fix_up_test();
    test_update_priorities();
        test_custom_functor();
        test_mess_up_queue();
    cout << "Tests Successful" << endl;
}

