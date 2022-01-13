#include "AVLTree.h"
#include "BinarySearchTree.h"
#include "Exoplanet.h"
#include "SplayTree.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {

    // Create vector of Exoplanets.
    vector<Exoplanet> exoplanets;

    // Read in data from file.
    readFile("../exoplanet_dataset.csv", exoplanets);

    // Create output file stream.
    ofstream outputFile;

    //####################################################################################################//

    // Create Binary Search Trees.
    BinarySearchTree<int> bstOrdered;
    BinarySearchTree<int> bstRandom;
    BinarySearchTree<Exoplanet> bstExoplanet;

    // *** Ordered BST *** //
    outputFile.open("../Data/Ordered_BST_Depths.txt");
    if(outputFile) {
        outputFile << "Node,Depth" << endl;
    }

    // Fill BST.
    for(int i = 1; i <= 100; ++i) {
        bstOrdered.add(i);
    }

    // Set depth counting variable;
    int depthBSTOrdered = 0;
    // Search for each item in BST.
    for(int i = 1; i <= 100; ++i) {
        bstOrdered.find(i, depthBSTOrdered);
        outputFile << i << "," << depthBSTOrdered << endl;

        // Reset depth.
        depthBSTOrdered = 0;
    }

    // Close current file.
    outputFile.close();

    // Search for 0, 101, and 102, which are all NOT found in the BST.
    cout << boolalpha << bstOrdered.find(0, depthBSTOrdered) << ", Depth: " << depthBSTOrdered << endl;
    depthBSTOrdered = 0;
    cout << boolalpha << bstOrdered.find(101, depthBSTOrdered) << ", Depth: " << depthBSTOrdered << endl;;
    depthBSTOrdered = 0;
    cout << boolalpha << bstOrdered.find(102, depthBSTOrdered) << ", Depth: " << depthBSTOrdered << endl;;
    depthBSTOrdered = 0;


    // *** Random BST *** //
    outputFile.open("../Data/Random_BST_Depths.txt");
    if(outputFile) {
        outputFile << "Node,Depth" << endl;
    }

    // Create vector of integers from 1-100 and shuffle it to have random ordering.
    vector<int> randomBSTIntegers;
    for(int i = 1; i <= 100; ++i) {
        randomBSTIntegers.push_back(i);
    }

    // Shuffle vector.
    random_shuffle(randomBSTIntegers.begin(), randomBSTIntegers.end());

    // Fill BST.
    for(int i = 0; i < 100; ++i) {
        bstRandom.add(randomBSTIntegers[i]);
    }

    // Set depth counting variable;
    int depthBSTRandom = 0;
    // Search for each item in BST.
    for(int i = 1; i <= 100; ++i) {
        bstRandom.find(i, depthBSTRandom);
        outputFile << i << "," << depthBSTRandom << endl;

        // Reset depth.
        depthBSTRandom = 0;
    }

    // Close current file.
    outputFile.close();


    // *** Exoplanet BST *** //
    outputFile.open("../Data/Exoplanet_BST_Depths.txt");
    if(outputFile) {
        outputFile << "Exoplanet Row ID,Depth" << endl;
    }

    // Fill BST with Exoplanets.
    for(Exoplanet ex : exoplanets) {
        bstExoplanet.add(ex);
    }

    // Set depth counting variable;
    int depthBSTExoplanet = 0;
    // Search for each item in BST.
    for(Exoplanet ex : exoplanets) {
        bstExoplanet.find(ex,depthBSTExoplanet);
        outputFile << ex.getRow() << "," << depthBSTExoplanet << endl;

        // Reset depth.
        depthBSTExoplanet = 0;
    }

    // Close current file.
    outputFile.close();

    //####################################################################################################//

    // Create AVL Trees.
    AVLTree<int> avlOrdered;
    AVLTree<int> avlRandom;
    AVLTree<Exoplanet> avlExoplanet;

    // *** Ordered AVL Tree *** //
    outputFile.open("../Data/Ordered_AVL_Depths.txt");
    if(outputFile) {
        outputFile << "Node,Depth" << endl;
    }

    // Fill AVL tree.
    for(int i = 1; i <= 100; ++i) {
        avlOrdered.add(i);
    }
    // Set depth counting variable;
    int depthAVLOrdered = 0;
    // Search for each item.
    for(int i = 1; i <= 100; ++i) {
        avlOrdered.find(i, depthAVLOrdered);
        outputFile << i << "," << depthAVLOrdered << endl;

        // Reset depth.
        depthAVLOrdered = 0;
    }

    // Close current file.
    outputFile.close();


    // *** Random AVL Tree *** //
    outputFile.open("../Data/Random_AVL_Depths.txt");
    if(outputFile) {
        outputFile << "Node,Depth" << endl;
    }

    // Create vector of integers from 1-100 and shuffle it to have random ordering.
    vector<int> randomAVLIntegers;
    for(int i = 1; i <= 100; ++i) {
        randomAVLIntegers.push_back(i);
    }

    // Shuffle vector.
    random_shuffle(randomAVLIntegers.begin(), randomAVLIntegers.end());

    // Fill AVL tree.
    for(int i = 0; i < 100; ++i) {
        avlRandom.add(randomAVLIntegers[i]);
    }

    // Set depth counting variable.
    int depthAVLRandom = 0;
    // Search for each item in AVL tree.
    for(int i = 1; i <= 100; ++i) {
        avlRandom.find(i, depthAVLRandom);
        outputFile << i << "," << depthAVLRandom << endl;

        // Reset depth.
        depthAVLRandom = 0;
    }

    // Close current file.
    outputFile.close();


    // *** Exoplanet AVL *** //
    outputFile.open("../Data/Exoplanet_AVL_Depths.txt");
    if(outputFile) {
        outputFile << "Node,Depth" << endl;
    }

    // Fill AVL tree with Exoplanets.
    for(Exoplanet ex : exoplanets) {
        avlExoplanet.add(ex);
    }

    // Set depth counting variable.
    int depthAVLExoplanet = 0;
    // Search for each item in AVL tree.
    for(Exoplanet ex : exoplanets) {
        avlExoplanet.find(ex,depthAVLExoplanet);
        outputFile << ex.getRow() << "," << depthAVLExoplanet << endl;

        // Reset depth.
        depthAVLExoplanet = 0;
    }

    // Close current file.
    outputFile.close();

    //####################################################################################################//

    // Create Splay trees.
    SplayTree<int> splayOrdered;
    SplayTree<int> splayRandom;

    // *** Ordered Splay Tree *** //
    outputFile.open("../Data/Ordered_Splay_Depths.txt");
    if(outputFile) {
        outputFile << "Node,Depth" << endl;
    }

    // Fill splay tree.
    for(int i = 1; i <= 100; ++i) {
        splayOrdered.add(i);
    }

    // Set depth counting variable;
    int depthSplayOrdered = 0;
    // Search for each item in splay tree.
    for(int i = 1; i <= 100; ++i) {
        splayOrdered.find(i, depthSplayOrdered);
        outputFile << i << "," << depthSplayOrdered << endl;

        // Reset depth.
        depthSplayOrdered = 0;
    }

    // Close the file.
    outputFile.close();


    // *** Random Splay Tree *** //
    outputFile.open("../Data/Random_Splay_Depths.txt");
    if(outputFile) {
        outputFile << "Node,Depth" << endl;
    }

    // Create vector of integers from 1-100 and shuffle it to have random ordering.
    vector<int> randomSplayIntegers;
    for(int i = 100; i >= 1; --i) {
        randomSplayIntegers.push_back(i);
    }

    // Shuffle vector.
    random_shuffle(randomSplayIntegers.begin(), randomSplayIntegers.end());

    // Add integers to splay tree.
    for(int i = 0; i < 100; ++i) {
        splayRandom.add(randomSplayIntegers[i]);
    }

    // Set depth counting variable;
    int depthSplayRandom = 0;
    // Search for each item in splay tree.
    for(int i = 1; i <= 100; ++i) {
        splayRandom.find(i, depthSplayRandom);
        outputFile << i << "," << depthSplayRandom << endl;

        // Reset depth.
        depthSplayRandom = 0;
    }

    // Close current file.
    outputFile.close();


    // *** Exoplanet Splay Tree *** //
    SplayTree<Exoplanet> splayOrderExoplanet;
    SplayTree<Exoplanet> splayRepeatExoplanet;

    // Fill Exoplanet splay trees.
    for(Exoplanet ex : exoplanets) {
        splayOrderExoplanet.add(ex);
        splayRepeatExoplanet.add(ex);
    }

    // In-Order Search:
    outputFile.open("../Data/Ordered_Exoplanet_Splay_Depths.txt");
    if(outputFile) {
        outputFile << "Node,Depth" << endl;
    }

    // Set depth counting variable.
    int splayOrderedExoplanetDepth = 0;
    // Search for each item in splay tree.
    for(Exoplanet ex : exoplanets) {
        splayOrderExoplanet.find(ex, splayOrderedExoplanetDepth);
        outputFile << ex.getRow() << "," << splayOrderedExoplanetDepth << endl;

        // Reset depth.
        splayOrderedExoplanetDepth = 0;
    }

    // Close file.
    outputFile.close();


    // Random-Order Search:
    outputFile.open("../Data/Random_Repeated_Exoplanet_Splay_Depths.txt");
    if(outputFile) {
        outputFile << "Node,Depth" << endl;
    }

    // Create vector for scrambled exoplanets.
    vector<Exoplanet> scrambledExoplanets = exoplanets;

    // Shuffle vector.
    random_shuffle(scrambledExoplanets.begin(), scrambledExoplanets.end());

    // Set depth counting variable.
    int splayRandomRepeatedExoplanetDepth = 0;
    // Search for each item in splay tree.
    for(Exoplanet ex : scrambledExoplanets) {
        for(int i = 0; i < 5; ++i) {
            splayRepeatExoplanet.find(ex, splayRandomRepeatedExoplanetDepth);
            outputFile << ex.getRow() << "," << splayRandomRepeatedExoplanetDepth << endl;

            // Reset depth.
            splayRandomRepeatedExoplanetDepth = 0;
        }
    }

    return 0;
}