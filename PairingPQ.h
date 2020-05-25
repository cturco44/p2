// Project identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>

// A specialized version of the 'priority_queue' ADT implemented as a pairing heap.
template<typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR> {
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node {
        public:
            // TODO: After you add add one extra pointer (see below), be sure to
            // initialize it here.
            explicit Node(const TYPE &val)
            : elt{ val }, child{ nullptr }, sibling{ nullptr }, prev{nullptr}
            {}

            // Description: Allows access to the element at that Node's position.
			// There are two versions, getElt() and a dereference operator, use
			// whichever one seems more natural to you.
            // Runtime: O(1) - this has been provided for you.
            const TYPE &getElt() const { return elt; }
            const TYPE &operator*() const { return elt; }

            // The following line allows you to access any private data members of this
            // Node class from within the PairingPQ class. (ie: myNode.elt is a legal
            // statement in PairingPQ's add_node() function).
            friend PairingPQ;

        private:
            TYPE elt;
            Node *child;
            Node *sibling;
        
            Node *prev;
            // TODO: Add one extra pointer (parent or previous) as desired.
    }; // Node


    // Description: Construct an empty priority_queue with an optional comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, root {nullptr}, tree_size{0} {
        // TODO: Implement this function.
    } // PairingPQ()


    // Description: Construct a priority_queue out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    // TODO: when you implement this function, uncomment the parameter names.
    template<typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) :
        BaseClass{ comp }, root {nullptr}, tree_size{0} {
            for(auto it = start; it != end; ++it) {
                push(*it);
            }
        // TODO: Implement this function.
    } // PairingPQ()


    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ& other) :
        BaseClass{ other.compare }, root{nullptr}, tree_size{0} {
            copy_helper(other.root);
        // TODO: Implement this function.
    } // PairingPQ()


    // Description: Copy assignment operator.
    // Runtime: O(n)
    // TODO: when you implement this function, uncomment the parameter names.
    PairingPQ& operator=(const PairingPQ& rhs) {
        if(this == &rhs) {
            return *this;
        }
        if(tree_size > 0) {
            delete_helper();
        }
        
        tree_size = 0;
        copy_helper(rhs.root);
        
        
        // TODO: Implement this function.

        return *this;
    } // operator=()


    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ() {
        if(tree_size > 0) {
            delete_helper();
        }
        
        // TODO: Implement this function.
    } // ~PairingPQ()


    // Description: Assumes that all elements inside the priority_queue are out of order and
    //              'rebuilds' the priority_queue by fixing the priority_queue invariant.
    // Runtime: O(n)
    virtual void updatePriorities() {
        std::deque<Node*> holder;
        tree_size = 0;

        if(root) {
            holder.push_back(root);
        }
        root = nullptr;
        while(!holder.empty()) {
            Node* investigating = holder.back();
            Node* roots_child = holder.back()->child;
            Node* roots_sibling = holder.back()->sibling;
            if(roots_sibling) {
                holder.push_front(roots_sibling);
                
            }
            if(roots_child) {
                holder.push_front(roots_child);
            }
            if(investigating) {
                ++tree_size;
                investigating->child = nullptr;
                investigating->prev = nullptr;
                investigating->sibling = nullptr;
                if(root == nullptr) {
                    root = investigating;
                }
                else {
                    root = meld(root, investigating);
                }
                
                holder.pop_back();
            }
        }
        
        
        
        // TODO: Implement this function.
    } // updatePriorities()


    // Description: Add a new element to the priority_queue. This is almost done,
    //              in that you should implement push functionality in the addNode()
    //              function, and this function should call addNode().
    // Runtime: O(1)
    // TODO: when you implement this function, uncomment the parameter names.
    virtual void push(const TYPE &val) {
        addNode(val);

        // TODO: Implement this function.
    } // push()


    // Description: Remove the most extreme (defined by 'compare') element from
    //              the priority_queue.
    // Note: We will not run tests on your code that would require it to pop an
    // element when the priority_queue is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: Amortized O(log(n))
    virtual void pop() {
        Node* son = root->child;
        delete root;
        root = nullptr;
        
        std::deque<Node*> holder;
        while(son) {
            holder.push_back(son);
            son = son->sibling;
        }
        --tree_size;
        if(!holder.empty()) {
            root = passover(holder);
        }
        
        
        // TODO: Implement this function.
    } // pop()


    // Description: Return the most extreme (defined by 'compare') element of
    //              the heap.  This should be a reference for speed.  It MUST be
    //              const because we cannot allow it to be modified, as that
    //              might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE & top() const {
        return root->elt;

    } // top()


    // Description: Get the number of elements in the priority_queue.
    // Runtime: O(1)
    virtual std::size_t size() const {
        // TODO: Implement this function
        return tree_size; // TODO: Delete or change this line
    } // size()

    // Description: Return true if the priority_queue is empty.
    // Runtime: O(1)
    virtual bool empty() const {
        if(tree_size == 0) {
            return true;
        }
        else {
            return false;
        }
        // TODO: Implement this function
        return true; // TODO: Delete or change this line
    } // empty()


    // Description: Updates the priority of an element already in the priority_queue by
    //              replacing the element refered to by the Node with new_value.
    //              Must maintain priority_queue invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more extreme
    //               (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    // TODO: when you implement this function, uncomment the parameter names.
    void updateElt(Node* node, const TYPE & new_value) {
        node->elt = new_value;
        //If node is root
        if(node == root) {
            return;
        }
        //is the previous node a parent or sibling node?
        bool prev_parent = false;
        
        if((node->prev)->child) {
            if((node->prev)->child == node) {
                prev_parent = true;
            }
        }
        if(prev_parent) {
            (node->prev)->child = node->sibling;
        }
        else {
            (node->prev)->sibling = node->sibling;
            (node->sibling)->prev = node->prev;
        }
        node->sibling = nullptr;
        node->child = nullptr;
        node->prev = nullptr;
        
        root = meld(root, node);
        
        // TODO: Implement this function
    } // updateElt()


    // Description: Add a new element to the priority_queue. Returns a Node* corresponding
    //              to the newly added element.
    // Runtime: O(1)
    // TODO: when you implement this function, uncomment the parameter names.
    // NOTE: Whenever you create a node, and thus return a Node *, you must be sure to
    //       never move or copy/delete that node in the future, until it is eliminated
    //       by the user calling pop().  Remember this when you implement updateElt() and
    //       updatePriorities().
    Node* addNode(const TYPE &val) {
        Node* added_node = new Node(val);
        ++tree_size;
        if(!root) {
            root = added_node;
            return added_node;
        }
        root = meld(root, added_node);
        return added_node;
        // TODO: Implement this function
    } // addNode()


private:
    Node* root;
    size_t tree_size;
    //REQUIRES: lhs and rhs have no siblings
    Node* meld(Node* lhs, Node* rhs) {
        //whatever should be on top set to alpha
        Node* alpha;
        Node* beta;
        if(this->compare(lhs->elt, rhs->elt)) {
            alpha = rhs;
            beta = lhs;
        }
        else {
            alpha = lhs;
            beta = rhs;
        }
        alpha->prev = nullptr;
        Node* alphas_kid = alpha->child;
        alpha->sibling = nullptr;
        
        //Beta should only have children
        beta->sibling = nullptr;
        beta->prev = nullptr;
        
        //set beta to kid
        alpha->child = beta;
        beta->prev = alpha;
        
        //set alpha's kid to beta's sibling
        beta->sibling = alphas_kid;
        if(alphas_kid) {
            alphas_kid->prev = beta;
        }
        
        
        return alpha;
        
    }
    //doesn't handle comparator,
    void copy_helper(Node* root_in) {
        std::deque<Node*> holder;
        
        if(root_in) {
            holder.push_back(root_in);
        }
        while(!holder.empty()) {
            Node* investigating = holder.back();
            Node* roots_child = holder.back()->child;
            Node* roots_sibling = holder.back()->sibling;
            if(roots_sibling) {
                holder.push_front(roots_sibling);
                
            }
            if(roots_child) {
                holder.push_front(roots_child);
            }
            push(investigating->elt);
            holder.pop_back();
        }
        
    }
    void delete_helper() {
        std::deque<Node*> holder;

        if(root) {
            holder.push_back(root);
        }
        while(!holder.empty()) {
            Node* investigating = holder.back();
            Node* roots_child = holder.back()->child;
            Node* roots_sibling = holder.back()->sibling;
            if(roots_sibling) {
                holder.push_front(roots_sibling);
                
            }
            if(roots_child) {
                holder.push_front(roots_child);
            }
            delete investigating;
            holder.pop_back();
        }
        root = nullptr;
    }
    Node* passover(std::deque<Node*> &family) {
        while(family.size() > 1) {
            Node* first = family.front();
            family.pop_front();
            Node* second = family.front();
            family.pop_front();
            
            first->sibling = nullptr;
            first->prev = nullptr;
            second->sibling = nullptr;
            second->prev = nullptr;
            
            Node* temp = meld(first, second);
            family.push_back(temp);
        }
        return family.front();
    }

        
    
    // TODO: Add any additional member functions or data you require here.
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap papers).

};


#endif // PAIRINGPQ_H
