/**
 * Anthony Stem
 * CS 124 - Section C
 */
#include "Exoplanet.h"
#include "Node.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Create vector of Exoplanets.
    vector<Exoplanet> exoplanets;

    // Read in data from file.
    readFile("../exoplanet_dataset.csv", exoplanets);

    // Do Queue class tests.
    // Do Queue class tests with integer type queue.
    cout << "-------------------- Integer Queue Tests --------------------" << endl;
    Queue<int> intQueue;

    // Fill with ints and test getBack() and push() methods.
    cout << intQueue.getBack() << endl; // 0
    for(int i = -2; i <= 2; ++i) {
        intQueue.push(i);
        cout << intQueue.getBack() << endl; // -2, -1, 0, 1, 2
    }
    cout << endl;

    // Test Methods.
    // Test printQueue() method.
    intQueue.printQueue();
    cout << endl;
    // Test getFront() and getBack() method.
    cout << "First Item in Queue: " << intQueue.getFront() << endl;
    cout << "Last Item in Queue: " << intQueue.getBack() << endl;
    cout << endl;
    // Test search() method.
    cout << "Is -1 in the Queue? " << boolalpha << intQueue.search(-1) << endl; // true
    cout << "Is 3 in the Queue? " << boolalpha << intQueue.search(3) << endl; // false
    cout << endl;

    // Pop items from Queue and add to Stack.
    Stack<int> intStack;
    // Store each popped item from queue, so we can print it to console.
    int currInt;
    for(int i = 0; i < 5; ++i) {
        currInt = intQueue.pop();
        cout << "Popped: " << currInt << endl; // Print out popped items.
        // Push to stack.
        intStack.push(currInt);
    }
    // Show that front and back are nullptr and we get default int of 0.
    cout << endl;
    cout << "First Item in Queue: " << intQueue.getFront() << endl;
    cout << "Last Item in Queue: " << intQueue.getBack() << endl;
    cout << endl;
    // Show queue is now empty.
    intQueue.printQueue();
    cout << endl;
    // Print stack.
    intStack.printStack();

    // Do Queue class tests with string type queue.
    cout << "\n-------------------- String Queue Tests --------------------" << endl;
    // Create and Test Queue of Strings.
    Queue<string> stringQueue;

    // Fill with strings and test getBack() and push() methods.
    if(stringQueue.getBack() == "") { // Should be empty string "". For verification purposes, display "EMPTY STRING".
        cout << "EMPTY STRING" << endl;
    }
    stringQueue.push("Hello");
    cout << stringQueue.getBack() << endl; // Hello
    stringQueue.push("World!");
    cout << stringQueue.getBack() << endl; // World!
    stringQueue.push("Apple");
    cout << stringQueue.getBack() << endl; // Apple
    stringQueue.push("Pie");
    cout << stringQueue.getBack() << endl; // Pie
    stringQueue.push("\"Exoplanets are Cool!\"");
    cout << stringQueue.getBack() << endl; // "Exoplanets are Cool!"
    cout << endl;

    // Test Methods.
    // Test printQueue() method.
    stringQueue.printQueue();
    cout << endl;
    // Test getFront() and getBack() methods.
    cout << "First Item in Queue: \n" << stringQueue.getFront() << endl; // Hello
    cout << "Last Item in Queue: \n" << stringQueue.getBack() << endl; // "Exoplanets are Cool!"
    cout << endl;
    // Test search() method.
    cout << "Is \"Hello\" in the Queue? " << boolalpha << stringQueue.search("Hello") << endl; // true
    cout << "Is \"Blueberry\" in the Queue? " << boolalpha << stringQueue.search("BlueBerry") << endl; // false
    cout << endl;

    // Pop items from Queue and add to Stack.
    Stack<string> stringStack;
    // Store each popped item from queue, so we can print it to console.
    string currString;
    for(int i = 0; i < 5; ++i) {
        currString = stringQueue.pop();
        cout << "Popped: " << currString << endl; // Print out popped items.
        // Push to stack.
        stringStack.push(currString);
    }

    // Show that front and back are nullptr and we get default string.
    cout << endl;
    cout << "First Item in Queue: " << stringQueue.getFront() << endl;
    cout << "Last Item in Queue: " << stringQueue.getBack() << endl;
    cout << endl;
    // Show queue is now empty.
    stringQueue.printQueue();
    cout << endl;
    // Print Stack.
    stringStack.printStack();
    cout << endl;

    // Do Queue class tests with Exoplanet type queue
    cout << "\n-------------------- Exoplanet Queue Tests --------------------" << endl;
    Queue<Exoplanet> exoQueue;

    // Fill with Exoplanet objects and test getBack() and push() methods.
    cout << exoQueue.getBack() << endl; // -1 NO ENTRY -1 -1 -1 -1
    for(int i = 0; i < 10; ++i) {
        exoQueue.push(exoplanets[i]);
        cout << exoQueue.getBack() << endl; // Should be objects with rows 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 (in this order).
    }
    cout << endl;

    // Test Methods.
    exoQueue.printQueue();
    cout << endl;
    // Test getFront() and getBack() methods.
    cout << "First Item in Queue:\n" << exoQueue.getFront() << endl; // 1 OGLE-2016-BLG-1469L b  13.6 -1 -1 2017
    cout << "Last Item in Queue:\n" << exoQueue.getBack() << endl; // 10 1RXS 1609 b  14 1.7 -1 2008
    cout << endl;
    // Test search() method.
    cout << "Is planet \"11 Com b\" at row 2 in the Queue? " << boolalpha << exoQueue.search(Exoplanet(2, "11 Com b", 19.4, -1, 326.03, 2008)) << endl; // true
    cout << "Is planet \"I NoExist b\" at row 1 in the Queue? " << boolalpha << exoQueue.search(Exoplanet(1, "I NoExist b", 10, 10, 10, 2000)) << endl; // false
    cout << endl;

    // Pop items from Queue and add to Stack.
    Stack<Exoplanet> exoStack;
    // Store each popped item from queue, so we can print it to console.
    Exoplanet currExo;
    for(int i = 0; i < 10; ++i) {
        currExo = exoQueue.pop();
        cout << "Popped: " << currExo << endl; // Print out items popped.
        // Push to stack.
        exoStack.push(currExo);
    }
    // Show that front and back are nullptr and we get default Exoplanet.
    cout << endl;
    cout << "First Item in Queue:\n" << exoQueue.getFront() << endl;
    cout << "Last Item in Queue:\n" << exoQueue.getBack() << endl;
    cout << endl;
    // Show queue is now empty.
    exoQueue.printQueue();
    cout << endl;
    // Print stack.
    exoStack.printStack();

    cout << endl;

    return 0;
}



