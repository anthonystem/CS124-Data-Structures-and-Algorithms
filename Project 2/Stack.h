//
// Created by Lisa Dion on 9/13/21.
//

#ifndef LINKEDLISTC_STACK_H
#define LINKEDLISTC_STACK_H

#include "Node.h"
#include <iostream>
using std::cout, std::endl;

template<typename Object>
class Stack {
private:
    // Store the location of the top Node as a field
    Node<Object>* top;

public:
    // Constructor
    Stack() {
        // Start with an empty Stack
        top = nullptr;
    }

    // Destructor
    ~Stack() {
        // This method is automatically called at the end of the lifetime of the Stack object
        // To ensure there are no memory leaks, pop all remaining Nodes from the Stack
        while (top != nullptr) {
            pop();
        }
        cout << "No memory leaks!" << endl;
    }

    // Push method to add a value to the Stack
    void push(Object item) {
        // Put the item in a Node and have the Node point to top
        Node<Object>* newNode = new Node<Object>(item, top);
        // Top should now point to newNode
        top = newNode;
    }

    // Pop method to remove a value from the Stack
    Object pop() {
        if (top == nullptr) {
            // The Stack is empty. There is nothing to pop. Return the default Object
            return Object();
        }
        // Store a copy of top
        Node<Object>* topCopy = top;
        // Store a copy of the return value
        Object returnVal = top->getItem();
        // Update top to point to the Node below the current top
        top = top->getNext();
        // Delete the Node from heap memory
        delete topCopy;
        // return the Object that is being popped
        return returnVal;
    }

    // Search the Stack for a given value
    bool search(Object item) {
        Node<Object>* curr = top;
        while (curr != nullptr) {
            if (item == curr->getItem()) {
                // The item is in the Stack
                return true;
            }
            curr = curr->getNext();
        }
        // The item is not in the Stack
        return false;
    }

    // Peek method to return the item at the top of the Stack
    Object peek() {
        // Check that the Stack is not empty
        if (top != nullptr) {
            return top->getItem();
        }
        // If the Stack is empty, return the default Object
        return Object();
    }

    // Print Stack method to print everything in the Stack
    void printStack() {
        cout << "Top of Stack" << endl;
        Node<Object>* curr = top;
        while (curr != nullptr) {
            cout << curr->getItem() << endl;
            curr = curr->getNext();
        }
        cout << "Bottom of Stack" << endl;
    }
};

#endif //LINKEDLISTC_STACK_H