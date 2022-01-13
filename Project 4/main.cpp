/**
 * Anthony Stem
 * CS 124 - Section C
 */

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Exoplanet.h"
#include <chrono>
#include <unistd.h>

using namespace std;

// **************************************************************************************************** //
template<typename Comparable>
void printVec(const vector<Comparable> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i != 0) {
            cout << ", ";
        }
        cout << v[i];
    }
    cout << endl;
}


// ************************************************** HEAP SORT ************************************************** //
// Helper function for heapSort
inline int leftChild(int i) {
    return 2 * i + 1;
}

// Helper function for heapSort
// i is the index of the value being percolated down
// n is the number of items in the heap
template <typename Comparable>
void percolateDown(vector<Comparable> &items, int i, int n, int child, Comparable tmp, int &reads, int &writes) {
    for(tmp = items[i]; leftChild(i) < n; i = child) { // 1 read, 1 write (each iteration)

        reads++;
        writes++;

        child = leftChild(i);
        // choose the child with the larger value
        reads += 2;
        if (child != n - 1 && items[child] < items[child + 1]) { // 2 reads
            ++child;
        }

        // if the parent is less than the child, swap them
        reads += 2;
        if (tmp < items[child]) { // 2 reads
            items[i] = items[child]; // 1 read, 1 write
            reads++;
            writes++;
        } else {
            // parent is >= both children. nothing more to do.
            break;
        }
    }
    items[i] = tmp; // 1 read, 1 write
    reads++;
    writes++;
}

template <typename Comparable>
vector<Comparable> heapSort(vector<Comparable> items, int &reads, int &writes) {
    int i, j, child;
    Comparable temp, tmp;
    // build the heap (with max value at root)
    for (i = items.size() / 2 - 1; i >= 0; --i) {
        percolateDown(items, i, items.size(), child, tmp, reads, writes);
    }

    // keep deleting the max
    for (j = items.size() - 1; j > 0; --j) {
        // swap the maximum out
        temp = items[0]; // 1 read, 1 write
        items[0] = items[j]; // 1 read, 1 write
        items[j] = temp; // 1 read, 1 write

        reads += 3;
        writes += 3;

        // make it into a heap again
        percolateDown(items, 0, j, child, tmp, reads, writes);

    }
    return items;
}

// ************************************************** BUBBLE SORT ************************************************** //
template<typename Comparable>
void bubbleSort(vector<Comparable> vec, int &reads, int &writes) {
    bool haveSwapped = true;
    int maxIndex = vec.size(), i;
    Comparable temp;
    while (haveSwapped) {
        haveSwapped = false;
        for (i = 0; i + 1 < maxIndex; ++i) {
            reads += 2;
            // Compare items at indices i and i+1 and swap if necessary
            if (vec[i] > vec[i+1]) { // 2 reads

                temp = vec[i]; // 1 read, 1 write
                vec[i] = vec[i+1]; // 1 read, 1 write
                vec[i+1] = temp; // 1 read, 1 write

                reads += 3;
                writes += 3;

                // Update haveSwapped
                haveSwapped = true;
            }
        }
        // Update maxIndex
        --maxIndex;
    }
}

// ************************************************** INSERTION SORT ************************************************** //
template<typename Comparable>
void insertionSort(vector<Comparable> vec, int &reads, int &writes) {
    int unsortedStartIndex, insertIndex;
    Comparable toBeInserted;
    for (unsortedStartIndex = 1; unsortedStartIndex < vec.size(); ++unsortedStartIndex) {
        toBeInserted = vec[unsortedStartIndex]; // 1 read, 1 write
        reads++;
        writes++;

        // Loop to shift over the larger elements
        insertIndex = unsortedStartIndex - 1;


        while (insertIndex >= 0 && vec[insertIndex] > toBeInserted) { // 2 reads (each iteration)
            reads += 2;
            vec[insertIndex + 1] = vec[insertIndex]; // 1 read, 1 write
            reads++;
            writes++;
            --insertIndex;
        }
        // Put toBeInserted back into vec
        vec[insertIndex + 1] = toBeInserted; // 1 read, 1 write
        reads++;
        writes++;
    }
}

// ************************************************** MERGE SORT ************************************************** //
template<typename Comparable>
void mergeSortRec(vector<Comparable> &vec, int startIndex, int endIndex, int &reads, int &writes) {
    // Recursive base case
    if (startIndex == endIndex) {
        // We have one item. There is nothing to split or sort.
        return;
    }

    // Recursive calls
    int centerIndex = (startIndex + endIndex) / 2;
    mergeSortRec(vec, startIndex, centerIndex, reads, writes);
    mergeSortRec(vec, centerIndex + 1, endIndex, reads, writes);

    // Merge
    vector<Comparable> temp;
    int leftIndex = startIndex;
    int rightIndex = centerIndex + 1;
    while (leftIndex <= centerIndex && rightIndex <= endIndex) {
        reads += 2;
        if (vec[leftIndex] <= vec[rightIndex]) { // 2 reads
            temp.push_back(vec[leftIndex]); // 1 read, 1 write
            reads++;
            writes++;
            ++leftIndex;
        } else {
            temp.push_back(vec[rightIndex]); // 1 read, 1 write
            reads++;
            writes++;
            ++rightIndex;
        }
    }
    // At this point, one of the halves has been completely copied into temp but the other hasn't
    // We need to finish copying everything into temp, so we make loops for each half
    while (leftIndex <= centerIndex) {
        temp.push_back(vec[leftIndex]); // 1 read, 1 write
        reads++;
        writes++;
        ++leftIndex;
    }
    while (rightIndex <= endIndex) {
        temp.push_back(vec[rightIndex]); // 1 read, 1 write
        reads++;
        writes++;
        ++rightIndex;
    }
    // At this point, all of the items from startIndex to endIndex have been copied into temp
    // Copy everything from temp back into vec
    for (int i = 0; i < temp.size(); ++i) {
        vec[i + startIndex] = temp[i]; // 1 read, 1 write
        reads++;
        writes++;
    }
}

template<typename Comparable>
void mergeSort(vector<Comparable> vec, int &reads, int &writes) {
    mergeSortRec(vec, 0, vec.size() - 1, reads, writes);
}


// ************************************************** SELECTION SORT (EXTRA CREDIT) ************************************************** //
template<typename Comparable>
void selectionSort(vector<Comparable> vec, int &reads, int &writes) {
    int swapIndex, i, minIndex;
    Comparable temp;
    for (swapIndex = 0; swapIndex < vec.size() - 1; ++swapIndex) {
        // Loop through vector starting at swapIndex and keep track of min
        minIndex = swapIndex;
        for (i = swapIndex + 1; i < vec.size(); ++i) {
            reads += 2;
            if (vec[i] < vec[minIndex]) { // 2 reads
                minIndex = i;
            }
        }
        // Swap min value into swapIndex spot in vector
        temp = vec[swapIndex]; // 1 read, 1 write
        vec[swapIndex] = vec[minIndex]; // 1 read, 1 write
        vec[minIndex] = temp; // 1 read, 1 write

        reads += 3;
        writes += 3;

    }
}

// ************************************************** TWO-SORT AND MODIFIED ALGORITHMS ************************************************** //
// ************************************************** MODIFIED INSERTION SORT ************************************************** //
template<typename Comparable>
void insertionSortModified(vector<Comparable> &vec, int &reads, int &writes) {
    int unsortedStartIndex, insertIndex;
    Comparable toBeInserted;
    for (unsortedStartIndex = 1; unsortedStartIndex < vec.size(); ++unsortedStartIndex) {
        toBeInserted = vec[unsortedStartIndex]; // 1 read, 1 write
        reads++;
        writes++;

        // Loop to shift over the larger elements
        insertIndex = unsortedStartIndex - 1;


        while (insertIndex >= 0 && vec[insertIndex] > toBeInserted) { // 2 reads (each iteration)
            reads += 2;
            vec[insertIndex + 1] = vec[insertIndex]; // 1 read, 1 write
            reads++;
            writes++;
            --insertIndex;
        }
        // Put toBeInserted back into vec
        vec[insertIndex + 1] = toBeInserted; // 1 read, 1 write
        reads++;
        writes++;
    }
}

// ************************************************** MODIFIED BUBBLE SORT ************************************************** //
// Compares Row IDs.
template<typename Comparable>
void bubbleSortModified(vector<Comparable> &vec, int &reads, int &writes) {
    bool haveSwapped = true;
    int maxIndex = vec.size(), i;
    Comparable temp;
    while (haveSwapped) {
        haveSwapped = false;
        for (i = 0; i + 1 < maxIndex; ++i) {
            reads += 2;
            // Compare discovery years at indices i and i+1 and swap if necessary
            if (vec[i].getDiscoveryYear() > vec[i+1].getDiscoveryYear()) { // 2 reads

                temp = vec[i]; // 1 read, 1 write
                vec[i] = vec[i+1]; // 1 read, 1 write
                vec[i+1] = temp; // 1 read, 1 write

                reads += 3;
                writes += 3;

                // Update haveSwapped
                haveSwapped = true;
            }
        }
        // Update maxIndex
        --maxIndex;
    }
}

// ************************************************** TWO SORT ************************************************** //
template<typename Comparable>
void twoSort(vector<Comparable> vec, int &reads, int &writes) {
    // Perform Selection Sort (unstable) on Row ID
    insertionSortModified(vec, reads, writes);

    // Perform Bubble Sort on Discovery Year
    bubbleSortModified(vec, reads, writes);
}


// **************************************************************************************************** //

int main() {
    // ***** Setup ***** //
    // Create vector of Exoplanets and randomize the ordering.
    vector<Exoplanet> exoplanets;
    readFile("../exoplanet_dataset.csv", exoplanets);
    random_shuffle(exoplanets.begin(), exoplanets.end());

    // Default number of reads and writes.
    int reads = 0;
    int writes = 0;
    int numValues = 100;

    // Create vector that will be updated routinely to be sorted.
    vector<Exoplanet> sortVector;

    // Open output file stream.
    ofstream outputFile;


     // ***** Bubble Sort ***** //
     outputFile.open("../Data/BubbleSort.txt");
     if(outputFile) {
         outputFile << "Values,Reads,Writes,Time" << endl;
     }

     // Loop for all vector sizes (in increments of 100).
     while(numValues <= 1000) {
         int start = numValues - 100;
         // Update length of vector to be sorted;
         for(int i = start; i < numValues; ++i) {
             sortVector.push_back(exoplanets[i]);
         }

         // Call Bubble Sort
         auto startTime = chrono::steady_clock::now(); // Start timer.
         bubbleSort(sortVector, reads, writes);
         auto endTime = chrono::steady_clock::now(); // End timer.

         // Output data to file.
         outputFile << numValues << "," << reads << "," << writes << "," << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << endl;

         // Reset reads and writes, and increase vector size.
         reads = 0;
         writes = 0;
         numValues += 100;
     }
     outputFile.close();

    // Clear the sort vector.
    for(int i = 0; i < 1000; ++i) {
        sortVector.pop_back();
    }


    // ***** Insertion Sort ***** //
    outputFile.open("../Data/InsertionSort.txt");
    if(outputFile) {
        outputFile << "Values,Reads,Writes,Time" << endl;
    }

    // Loop for all vector sizes (in increments of 100).
    numValues = 100;
    while(numValues <= 1000) {
        int start = numValues - 100;
        // Update length of vector to be sorted;
        for(int i = start; i < numValues; ++i) {
            sortVector.push_back(exoplanets[i]);
        }

        // Call Insertion Sort
        auto startTime = chrono::steady_clock::now(); // Start timer.
        insertionSort(sortVector, reads, writes);
        auto endTime = chrono::steady_clock::now(); // End timer.

        // Output to file.
        outputFile << numValues << "," << reads << "," << writes << "," << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << endl;

        // Reset reads and writes, and increase vector size.
        reads = 0;
        writes = 0;
        numValues += 100;
    }
    outputFile.close();

    // Clear the sort vector.
    for(int i = 0; i < 1000; ++i) {
        sortVector.pop_back();
    }


    // ***** Merge Sort ***** //
    outputFile.open("../Data/MergeSort.txt");
    if(outputFile) {
        outputFile << "Values,Reads,Writes,Time" << endl;
    }

    // Loop for all vector sizes (in increments of 100).
    numValues = 100;
    while(numValues <= 1000) {
        int start = numValues - 100;
        // Update length of vector to be sorted;
        for(int i = start; i < numValues; ++i) {
            sortVector.push_back(exoplanets[i]);
        }

        // Call Merge Sort
        auto startTime = chrono::steady_clock::now(); // Start timer.
        mergeSort(sortVector, reads, writes);
        auto endTime = chrono::steady_clock::now(); // End timer.

        // Output to file.
        outputFile << numValues << "," << reads << "," << writes << "," << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << endl;

        // Reset reads and writes, and increase vector size.
        reads = 0;
        writes = 0;
        numValues += 100;
    }
    outputFile.close();

    // Clear the sort vector.
    for(int i = 0; i < 1000; ++i) {
        sortVector.pop_back();
    }


    // ***** Heap Sort ***** //
    outputFile.open("../Data/HeapSort.txt");
    if(outputFile) {
        outputFile << "Values,Reads,Writes,Time" << endl;
    }

    // Loop for all vector sizes (in increments of 100).
    numValues = 100;
    while(numValues <= 1000) {
        int start = numValues - 100;
        // Update length of vector to be sorted;
        for(int i = start; i < numValues; ++i) {
            sortVector.push_back(exoplanets[i]);
        }

        // Call Heap Sort
        auto startTime = chrono::steady_clock::now(); // Start timer.
        heapSort(sortVector, reads, writes);
        auto endTime = chrono::steady_clock::now(); // End timer.

        // Output to file.
        outputFile << numValues << "," << reads << "," << writes << "," << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << endl;

        // Reset reads and writes, and increase vector size.
        reads = 0;
        writes = 0;
        numValues += 100;
    }
    outputFile.close();

    // Clear the sort vector.
    for(int i = 0; i < 1000; ++i) {
        sortVector.pop_back();
    }


    // ***** Selection Sort ***** //
    outputFile.open("../Data/SelectionSort.txt");
    if(outputFile) {
        outputFile << "Values,Reads,Writes,Time" << endl;
    }

    // Loop for all vector sizes (in increments of 100).
    numValues = 100;
    while(numValues <= 1000) {
        int start = numValues - 100;
        // Update length of vector to be sorted;
        for(int i = start; i < numValues; ++i) {
            sortVector.push_back(exoplanets[i]);
        }

        // Call Heap Sort
        auto startTime = chrono::steady_clock::now(); // Start timer.
        selectionSort(sortVector, reads, writes);
        auto endTime = chrono::steady_clock::now(); // End timer.

        // Output to file.
        outputFile << numValues << "," << reads << "," << writes << "," << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << endl;

        // Reset reads and writes, and increase vector size.
        reads = 0;
        writes = 0;
        numValues += 100;
    }
    outputFile.close();

    // Clear the sort vector.
    for(int i = 0; i < 1000; ++i) {
        sortVector.pop_back();
    }


    // ***** Two-Sort ***** //
    outputFile.open("../Data/TwoSort.txt");
    if(outputFile) {
        outputFile << "Values,Reads,Writes,Time" << endl;
    }

    // Loop for all vector sizes (in increments of 100).
    numValues = 100;
    while(numValues <= 1000) {
        int start = numValues - 100;
        // Update length of vector to be sorted;
        for(int i = start; i < numValues; ++i) {
            sortVector.push_back(exoplanets[i]);
        }

        // Call Two Sort
        auto startTime = chrono::steady_clock::now(); // Start timer.
        twoSort(sortVector, reads, writes);
        auto endTime = chrono::steady_clock::now(); // End timers.

        // Output to file.
        outputFile << numValues << "," << reads << "," << writes << "," << chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() << endl;

        // Reset reads and writes, and increase vector size.
        reads = 0;
        writes = 0;
        numValues += 100;
    }
    outputFile.close();

    return 0;
}