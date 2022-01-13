//
// Created by Lisa Dion on 9/10/21.
//

#ifndef LINKEDLISTC_NODE_H
#define LINKEDLISTC_NODE_H

/** Represents one node to be used in a linked list
    Contains data (object) and reference to next in list
*/
template<typename Object>
class Node {
private:
    Object item;
    // Declare a pointer using an asterisk (*)
    // A pointer is a data type that stores a reference (or memory address)
    Node* next;

public:
    /** Create new node with specified data
        Have it reference null
        @param newItem is data to added to new node
    */
    Node(Object newItem) {
        item = newItem;
        next = nullptr;
    }

    /** Create new node with specified data
        Have it reference nextNode
        @param newItem is data to added to new node
        @param nextNode is a pointer to the Node whose address next will hold
    */
    Node(Object newItem, Node* nextNode) {
        item = newItem;
        next = nextNode;
    }

    /** set data field (item) of Node
        @param newItem, to set item field to
    */
    void setItem(Object newItem) {
        item = newItem;
    }

    /** get data field (item) of Node
        @return item field
    */
    Object getItem() {
        return item;
    }

    /** set next field  of Node
        @param nextNode, to set next field to
    */
    void setNext(Node* nextNode) {
        next = nextNode;
    }

    /** get next field  Node
        @return next field
    */
    Node* getNext() {
        return next;
    }
};


#endif //LINKEDLISTC_NODE_H