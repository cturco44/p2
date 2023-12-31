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
#include "PairingPQ.h"

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
struct PtrComp {
    bool operator()(const int* a, const int* b) const {
        return *a < *b;
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
        return *(a.the_ptr) < *(b.the_ptr);
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
    assert(test.size() == 0);
    assert(test.empty());
    assert(correct.empty());
        
}
void test_paired_push_pop() {
        vector<int> v = {25, 18, 77, 16};
        PairingPQ<int> sorted;
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
void test_paired_iterators() {
    vector<int> v = {25, 18, 77, 16};
    PairingPQ<int> sorted(v.begin(), v.end());
    UnorderedFastPQ<int> correct(v.begin(), v.end());
    for(size_t i = 0; i < v.size(); ++i) {
        assert(sorted.top() == correct.top());
        sorted.pop();
        correct.pop();
    }
}
void test_paired_copy_constructor() {
    vector<int> v = {25, 18, 77, 16};
    PairingPQ<int> sorted(v.begin(), v.end());
    
    
    PairingPQ<int> tester(sorted);
    assert(tester.size() == sorted.size());
    for(size_t i = 0; i < v.size(); ++i) {
        assert(sorted.top() == tester.top());
        sorted.pop();
        tester.pop();
    }
}
void test_assignment_operator() {
    vector<int> v = {25, 18, 77, 16};
    PairingPQ<int> sorted(v.begin(), v.end());
    
    vector<int> t = {33,17};
    
    PairingPQ<int> tester(t.begin(), t.end());
    tester = sorted;
    assert(tester.size() == sorted.size());
    for(size_t i = 0; i < v.size(); ++i) {
        assert(sorted.top() == tester.top());
        sorted.pop();
        tester.pop();
    }
}
void test_assignment_operator2() {
    vector<int> v = {25, 18, 77, 16};
    PairingPQ<int> sorted(v.begin(), v.end());
    
    
    
    PairingPQ<int> tester;
    PairingPQ<int> empty2;
    tester = sorted;
    sorted = empty2;
    
    assert(tester.size() == 4);
    assert(sorted.size() == 0);
    assert(sorted.empty());

}
void test_destructor() {
    vector<int> v = {25, 18, 77, 16};
    PairingPQ<int> sorted(v.begin(), v.end());
    
    PairingPQ<int> tester;
    
}

void test_custom_functor_paired() {
    PairingPQ<IntPtrs, IntPtrsComp> test;
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
void test_update_elt() {
    PairingPQ<int> pq;
    pq.addNode(10);
    pq.addNode(9);
    auto mid = pq.addNode(8);
    pq.addNode(7);
    pq.updateElt(mid, 20);
    assert(pq.top() == 20);
    
    pq.pop();
    assert(pq.top() == 10);
    pq.pop();
    assert(pq.top() == 9);
    pq.pop();
    assert(pq.top() == 7);
    pq.pop();
    assert(pq.size() == 0);

}
void test_update_elt_child() {
    PairingPQ<int> pq;
    pq.addNode(10);
    pq.addNode(9);
    pq.addNode(8);
    auto mid = pq.addNode(7);
    pq.updateElt(mid, 20);
    
    assert(pq.top() == 20);
    pq.pop();
    assert(pq.top() == 10);
    pq.pop();
    assert(pq.top() == 9);
    pq.pop();
    assert(pq.top() == 8);
    pq.pop();
    assert(pq.size() == 0);
}
void infinite_loop_check() {
    PairingPQ<int> pq;
    auto topper = pq.addNode(200);
    pq.addNode(7);
    assert(pq.top() == 200);
    pq.updateElt(topper, 300);
}
void update1() {
    PairingPQ<int> pq;
    pq.updatePriorities();
}
void update_element_child() {
    vector<int> v = {47, 68, 92, 33, 37};
    PairingPQ<int> pq;
    pq.addNode(68);
    pq.addNode(92);
    auto mid = pq.addNode(47);
    pq.addNode(33);
    pq.addNode(37);
    pq.updateElt(mid, 69);
    
    assert(pq.top() == 92);
    
    pq.pop();
    assert(pq.top() == 69);
    pq.pop();
    assert(pq.top() == 68);
    pq.pop();
    assert(pq.top() == 37);
    pq.pop();
    assert(pq.top() == 33);
    pq.pop();
    assert(pq.size() == 0);
}
void update_element_sibling() {
    vector<int> v = {47, 68, 92, 33, 37};
    PairingPQ<int> pq;
    pq.addNode(47);
    pq.addNode(92);
    auto mid = pq.addNode(68);
    pq.addNode(33);
    pq.addNode(37);
    pq.updateElt(mid, 72);
    
    assert(pq.top() == 92);
    
    pq.pop();
    assert(pq.top() == 72);
    pq.pop();
    assert(pq.top() == 47);
    pq.pop();
    assert(pq.top() == 37);
    pq.pop();
    assert(pq.top() == 33);
    pq.pop();
    assert(pq.size() == 0);
}
void update_element_child2() {
    vector<int> v = {47, 68, 92, 33, 37};
    PairingPQ<int> pq;
    pq.addNode(47);
    pq.addNode(92);
    auto mid = pq.addNode(37);
    pq.addNode(33);
    pq.addNode(68);
    pq.updateElt(mid, 69);
    
    assert(pq.top() == 92);
    
    pq.pop();
    assert(pq.top() == 69);
    pq.pop();
    assert(pq.top() == 68);
    pq.pop();
    assert(pq.top() == 47);
    pq.pop();
    assert(pq.top() == 33);
    pq.pop();
    assert(pq.size() == 0);
}
void update_element_child3() {
    vector<int> v = {47, 68, 92, 33, 37};
    PairingPQ<int> pq;
    pq.addNode(47);
    pq.addNode(92);
    auto mid = pq.addNode(37);
    pq.addNode(33);
    pq.addNode(68);
    pq.updateElt(mid, 105);
    
    assert(pq.top() == 105);
    
    pq.pop();
    assert(pq.top() == 92);
    pq.pop();
    assert(pq.top() == 68);
    pq.pop();
    assert(pq.top() == 47);
    pq.pop();
    assert(pq.top() == 33);
    pq.pop();
    assert(pq.size() == 0);
}
void test_update_again() {
    vector<int> v = {13, 77, 89, 90, -5, -22, 40, 14, 9, 7, 13};
    vector<int*> ptr;
    for(int i = 0; i < (int)v.size(); ++i) {
        ptr.push_back(&v[i]);
    }
    PairingPQ<int*, PtrComp> pq(ptr.begin(), ptr.end());
    UnorderedFastPQ<int*, PtrComp> correct(ptr.begin(), ptr.end());
    int pq_top= *(pq.top());
    int correct_top = *(correct.top());
    assert(pq_top = correct_top);
    v[2] = 107;
    pq.updatePriorities();
    correct.updatePriorities();
    assert(pq.top() == correct.top());
    assert(*(pq.top()) == 107);
    
    v[3] = 257;
    v[6] = -700;
    pq.updatePriorities();
    correct.updatePriorities();
    
    assert(pq.size() == correct.size());
    while(!pq.empty()) {
        int* pq_top2 = pq.top();
        int* correct_top2 = correct.top();
        assert(*pq_top2 == *correct_top2);
        pq.pop();
        correct.pop();
    }
    
}
void update_dynamic() {
    vector<int> v = {13, 77, 89, 90, -5, -22, 40, 14, 9, 7, 13};
    vector<int*> ptr;
    for(int i = 0; i < (int)v.size(); ++i) {
        ptr.push_back(&v[i]);
    }
    PairingPQ<int*, PtrComp> *pq = new PairingPQ<int*, PtrComp> (ptr.begin(), ptr.end());
    UnorderedFastPQ<int*, PtrComp> correct(ptr.begin(), ptr.end());
    int pq_top= *(pq->top());
    int correct_top = *(correct.top());
    assert(pq_top = correct_top);
    v[2] = 107;
    pq->updatePriorities();
    correct.updatePriorities();
    assert(pq->top() == correct.top());
    assert(*(pq->top()) == 107);
    
    v[3] = 257;
    v[6] = -700;
    pq->updatePriorities();
    correct.updatePriorities();
    
    assert(pq->size() == correct.size());
    while(!pq->empty()) {
        int* pq_top2 = pq->top();
        int* correct_top2 = correct.top();
        assert(*pq_top2 == *correct_top2);
        pq->pop();
        correct.pop();
    }
    delete pq;
}
void test_update_ints() {
    vector<int> v = {13, 77, 89, 90, -5, -22, 40, 14, 9, 7, 13, 77, 89, 16, 42, 101, 15};

    PairingPQ<int> pq(v.begin(), v.end());
    UnorderedFastPQ<int> correct(v.begin(), v.end());
    int pq_top= pq.top();
    int correct_top = correct.top();
    assert(pq_top = correct_top);
   
    pq.updatePriorities();
    correct.updatePriorities();
    
    assert(pq.size() == correct.size());
    while(!pq.empty()) {
        int pq_top2 = pq.top();
        int correct_top2 = correct.top();
        assert(pq_top2 == correct_top2);
        pq.pop();
        correct.pop();
    }
}
void test_update_elt_complicated() {
    
    PairingPQ<int> pq;
    pq.addNode(13);
    auto mid = pq.addNode(89);
    pq.addNode(240);
    pq.addNode(68);
    pq.addNode(77);
    pq.updateElt(mid, 105);
    
    assert(pq.top() == 240);
    
    pq.pop();
    assert(pq.top() == 105);
    pq.pop();
    assert(pq.top() == 77);
    pq.pop();
    assert(pq.top() == 68);
    pq.pop();
    assert(pq.top() == 13);
    pq.pop();
    assert(pq.size() == 0);

}
void test_update_elt_complicated2() {
    
    PairingPQ<int> pq;
    pq.addNode(13);
    auto mid = pq.addNode(89);
    pq.addNode(240);
    pq.addNode(68);
    pq.addNode(77);
    pq.updateElt(mid, 300);
    
    assert(pq.top() == 300);
    
    pq.pop();
    assert(pq.top() == 240);
    pq.pop();
    assert(pq.top() == 77);
    pq.pop();
    assert(pq.top() == 68);
    pq.pop();
    assert(pq.top() == 13);
    pq.pop();
    assert(pq.size() == 0);

}
int main() {
    test_sorted_constructor();
    test_sorted_push();
    test_with_struct();
    fix_up_test();
    test_update_priorities();
        test_custom_functor();
        test_mess_up_queue();
    test_paired_push_pop();
    test_paired_iterators();
    test_paired_copy_constructor();
    test_assignment_operator();
    test_assignment_operator2();
    test_custom_functor_paired();
    test_update_elt();
    update1();
    infinite_loop_check();
    update_element_child();
    update_element_sibling();
    update_element_child2();
    update_element_child3();
    test_update_again();
    update_dynamic();
    test_update_ints();
    test_update_elt_child();
    test_update_elt_complicated();
    test_update_elt_complicated2();
    cout << "Tests Successful" << endl;
}

