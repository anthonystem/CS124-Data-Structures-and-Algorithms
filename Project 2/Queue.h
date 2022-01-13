/**
 * Anthony Stem
 * CS 124 - Section C
 */

#ifndef FINAL_QUEUE_H
#define FINAL_QUEUE_H

#include "Node.h"
#include <iostream>
using std::cout, std::endl;

/**
 * Represents a Queue data structure. Items are added/pushed to the back of the queue, and items are
 * removed/popped from the front of the queue.
 */
template<typename Object>
class Queue {
private:
    // Store the location of the front and back of the nodes as fields.
    Node<Object> *front, *back;

public:
    /**
     * Constructor.
     *
     * Complexity: O(1).
     */
    Queue() {
        // Have front and back point to nullptr.
        front = back = nullptr;
    }

    /**
     * Destructor.
     *
     * Complexity: O(n)
     */
    ~Queue() {
        // Pop each item from queue.
        while(front != nullptr) {
            pop();
        }
        cout << "Queue Deconstructed." << endl;
    }

    /**
     * Adds (pushes) an item to the back of the queue.
     *
     * Complexity: O(1).
     */
    void push(Object item) {
        Node<Object>* newNode = new Node<Object>(item);
        if(front == nullptr) {
            // Have front and back point to new node.
            front = back = newNode;
        } else {
            // Have back point to new node.
            back->setNext(newNode);
            back = newNode;
        }
    }

    /**
     * Removes (pops) an item from the front of the queue, deallocates it from heap, and returns it.
     *
     * Complexity: O(1).
     */
    Object pop() {
        // Return default object if queue is empty since there is nothing to pop.
        if(front == nullptr) {
            return Object();
        }

        // Store copy of front.
        Node<Object>* frontCopy = front;

        // Store copy of item stored at front.
        Object returnValue = front->getItem();

        // Update the front to point to the new node.
        front = front->getNext();

        // Have back also point to nullptr if queue becomes empty (front becomes nullptr).
        if(front == nullptr) {
            back = nullptr;
        }

        // Delete node from heap memory.
        delete frontCopy;

        return returnValue;
    }

    /**
     * Gets the item at the front of the queue.
     *
     * Complexity: O(1).
     */
    Object getFront() {
        // Return default object if front is nullptr.
        if(front == nullptr) {
            return Object();
        }
        return front->getItem();
    }

    /**
     * Gets the item at the back of the queue.
     *
     * Complexity: O(1).
     */
    Object getBack() {
        // Return default object if back is nullptr.
        if(back == nullptr) {
            return Object();
        }
        return back->getItem();
    }


    /**
     * Searches for an item in the queue; returns true if it's in the queue, and returns
     * false if it's NOT in the queue.
     *
     * Complexity: O(n).
     */
    bool search(Object item) {
        Node<Object>* curr = front;
        // Loop through queue to find matching object.
        while (curr != nullptr) {
            if (item == curr->getItem()) {
                return true;
            }
            curr = curr->getNext();
        }
        return false;
    }


    /**
     * Prints the entire contents of the queue, nicely formatted.
     *
     * Complexity: O(n).
     */
    void printQueue() {
        Node<Object>* curr = front;
        cout << "Front of Queue {" << endl;
        while (curr != nullptr) {
            cout << curr->getItem() << endl;
            curr = curr->getNext();
        }
        cout << "} End of Queue" << endl;
    }
};

#endif //FINAL_QUEUE_H
