// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef BINARYPQ_H
#define BINARYPQ_H


#include <algorithm>
#include "Eecs281PQ.h"

// A specialized version of the 'heap' ADT implemented as a binary heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty heap with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
        // TODO: Implement this function.
    } // BinaryPQ


    // Description: Construct a heap out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    // TODO: when you implement this function, uncomment the parameter names.
    template<typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp } {
            for(auto it = start; it != end; ++it) {
                push(*it);
            }
        // TODO: Implement this function.
    } // BinaryPQ


    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automaticslly.
    virtual ~BinaryPQ() {
    } // ~BinaryPQ()


    // Description: Assumes that all elements inside the heap are out of order and
    //              'rebuilds' the heap by fixing the heap invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        // TODO: Implement this function.
    } // updatePriorities()


    // Description: Add a new element to the heap.
    // Runtime: O(log(n))
    // TODO: when you implement this function, uncomment the parameter names.
    virtual void push(const TYPE & val) {
        data.push_back(val);
        fixUp();
        // TODO: Implement this function.
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element from
    //              the heap.
    // Note: We will not run tests on your code that would require it to pop an
    // element when the heap is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: O(log(n))
    virtual void pop() {
        data.erase(data.begin());
        fixDown();
        
        // TODO: Implement this function.
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the heap.  This should be a reference for speed.  It MUST be
    //              const because we cannot allow it to be modified, as that
    //              might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE & top() const {
        
        return getElement(1);
        // TODO: Implement this function.
    } // top()


    // Description: Get the number of elements in the heap.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function.  Might be very simple,
        // depending on your implementation.
        return data.size(); // TODO: Delete or change this line
    } // size()


    // Description: Return true if the heap is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        // TODO: Implement this function.  Might be very simple,
        // depending on your implementation.
        return data.empty(); // TODO: Delete or change this line
    } // empty()


private:
    // Note: This vector *must* be used your heap implementation.
    std::vector<TYPE> data;
    // Translate 1-based indexing into a 0-based vector
    TYPE &getElement(std::size_t i) {
        return data[i - 1];
    }   // getElement()
    
    const TYPE &getElement(std::size_t i) const {
        return data[i - 1];
    } // getElement()
    
    void fixUp() {
        int k = (int)this->size() - 1;
        while(k > 1 && this->compare(getElement(k/2), getElement(k))) {
            std::swap(getElement(k), getElement(k/2));
            k /= 2;
        }
    }
    void fixDown() {
        int heapsize = (int)this->size();
        int k = 1;
        
        while(2 * k <= heapsize) {
            int j = 2 * k; //left child
            if(j < heapsize && this->compare(getElement(j), getElement(j + 1))) {
                ++j;
            }
            if(getElement(k) >= getElement(j)) {
                break;
            }
            std::swap(getElement(k), getElement(j));
            k = j;
        }
    }

    // TODO: Add any additional member functions or data you require here.
    // For instance, you might add fixUp() and fixDown().

}; // BinaryPQ


#endif // BINARYPQ_H
