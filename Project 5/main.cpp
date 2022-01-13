/**
 * Anthony Stem | Project 5
 * CS 124 - Section C
 */

#include "QuadraticProbing.h"
#include "SeparateChaining.h"
#include "QuadraticProbingAlternative.h"
#include "SeparateChainingAlternative.h"
#include "Exoplanet.h"
#include <iostream>
#include <string>

using namespace std;

// Exoplanet getKey Function
string getKey(Exoplanet exoplanet) {
    return exoplanet.getName();
}

// Alternate Exoplanet getKey Function
string getKeyAlternate(Exoplanet exoplanet) {
    return exoplanet.getName() + to_string(exoplanet.getDiscoveryYear());
}

int main() {

    // ***** Setup ***** //
    vector<Exoplanet> exoplanets;
    readFile("../exoplanet_dataset.csv", exoplanets);

    int numSepReads = 0;     // Get number of separate chaining reads.
    int numQuadReads = 0;    // Get number of quadratic probing reads.
    unsigned long tableSize; // Declare table size variable.

    // Create output file stream.
    ofstream outputFile;

    // Open read data file.
    outputFile.open("../Data/Varying_Sizes_Data.csv");

    // Write headers to file.
    outputFile << "Size,Separate Chaining Reads, Quadratic Probing Reads" << endl;

    // ******************** 5 QUADRATIC PROBING & SEPARATE CHAINING TABLES ************************* //
    // ***** 5 Hash Tables w/ Varying Sizes ***** //
    // Hash Tables w/ tableSize=3733
    tableSize = 3733; // size=3733
    SeparateChaining<Exoplanet> hashSeparateChaining3733(tableSize, getKey);
    QuadraticProbing<Exoplanet> hashQuadratic3733(tableSize, getKey);
    for(Exoplanet &exo : exoplanets) {
        hashSeparateChaining3733.insert(exo, numSepReads);
        hashQuadratic3733.insert(exo, numQuadReads);
    }

    cout << "Final Table Size: " << hashQuadratic3733.getTableSize() << endl;

    // Output reads to file.
    outputFile << tableSize << "," << numSepReads << "," << numQuadReads << "," << hashQuadratic3733.getTableSize() << endl;

    // Reset reads.
    numSepReads = 0;
    numQuadReads = 0;

    //

    // Hash Tables w/ tableSize=6007
    tableSize = 6007;
    SeparateChaining<Exoplanet> hashSeparateChaining6007(tableSize, getKey);
    QuadraticProbing<Exoplanet> hashQuadratic6007(tableSize, getKey);
    for(Exoplanet &exo : exoplanets) {
        hashSeparateChaining6007.insert(exo, numSepReads);
        hashQuadratic6007.insert(exo, numQuadReads);
    }

    cout << "Final Table Size: " << hashQuadratic6007.getTableSize() << endl;

    // Output reads to file.
    outputFile << tableSize << "," << numSepReads << "," << numQuadReads << "," << hashQuadratic6007.getTableSize() << endl;

    // Reset reads.
    numSepReads = 0;
    numQuadReads = 0;

    //

    // Hash Table w/ tableSize=8009
    tableSize = 8009;
    SeparateChaining<Exoplanet> hashSeparateChaining8009(tableSize, getKey);
    QuadraticProbing<Exoplanet> hashQuadratic8009(tableSize, getKey);
    for(Exoplanet &exo : exoplanets) {
        hashSeparateChaining8009.insert(exo, numSepReads);
        hashQuadratic8009.insert(exo, numQuadReads);
    }

    cout << "Final Table Size: " << hashQuadratic8009.getTableSize() << endl;

    // Output reads to file.
    outputFile << tableSize << "," << numSepReads << "," << numQuadReads << "," << hashQuadratic8009.getTableSize() << endl;

    // Reset reads.
    numSepReads = 0;
    numQuadReads = 0;

    //

    // Hash Table w/ tableSize=10007
    tableSize = 10007;
    SeparateChaining<Exoplanet> hashSeparateChaining10007(tableSize, getKey);
    QuadraticProbing<Exoplanet> hashQuadratic10007(tableSize, getKey);
    for(Exoplanet &exo : exoplanets) {
        hashSeparateChaining10007.insert(exo, numSepReads);
        hashQuadratic10007.insert(exo, numQuadReads);
    }

    cout << "Final Table Size: " << hashQuadratic10007.getTableSize() << endl;

    // Output reads to file.
    outputFile << tableSize << "," << numSepReads << "," << numQuadReads << "," << hashQuadratic10007.getTableSize() << endl;

    // Reset reads.
    numSepReads = 0;
    numQuadReads = 0;

    //

    // Hash Table w/ tableSize=12007
    tableSize = 12007;
    SeparateChaining<Exoplanet> hashSeparateChaining12007(tableSize, getKey);
    QuadraticProbing<Exoplanet> hashQuadratic12007(tableSize, getKey);
    for(Exoplanet &exo : exoplanets) {
        hashSeparateChaining12007.insert(exo, numSepReads);
        hashQuadratic12007.insert(exo, numQuadReads);
    }

    cout << "Final Table Size: " << hashQuadratic12007.getTableSize() << endl;

    // Output reads to file.
    outputFile << tableSize << "," << numSepReads << "," << numQuadReads << "," << hashQuadratic12007.getTableSize() << endl;

    // Reset reads.
    numSepReads = 0;
    numQuadReads = 0;

    outputFile.close();

    // Open new data file.
    outputFile.open("../Data/Combination_Read_Data.csv");

    // ******************** GETKEY AND HASH FUNCTION COMBINATIONS ************************* //

    // Use best table size from previous tests.
    unsigned long chainingTableSize = 12007;
    unsigned long probingTableSize = 12007;

    // ***** Alternative getKey Function | Same Hash Function ***** //
    SeparateChaining<Exoplanet> hashSepAltKey(chainingTableSize, getKeyAlternate);
    QuadraticProbing<Exoplanet> hashQuadAltKey(probingTableSize, getKeyAlternate);
    for(Exoplanet &exo : exoplanets) {
        hashSepAltKey.insert(exo, numSepReads);
        hashQuadAltKey.insert(exo, numQuadReads);
    }
    cout << "Final Table Size: " << hashQuadAltKey.getTableSize() << endl;

    // Output reads to file.
    outputFile << chainingTableSize << "," << numSepReads << endl;
    outputFile << probingTableSize << "," << numQuadReads << endl;

    // Reset reads.
    numSepReads = 0;
    numQuadReads = 0;

    // ***** Same getKey Function | Alternative Hash Function ***** //
    SeparateChainingAlternative<Exoplanet> hashSepAltHash(chainingTableSize, getKey);
    QuadraticProbingAlternative<Exoplanet> hashQuadAltHash(probingTableSize, getKey);
    for(Exoplanet &exo : exoplanets) {
        hashSepAltHash.insert(exo, numSepReads);
        hashQuadAltHash.insert(exo, numQuadReads);
    }
    cout << "Final Table Size: " << hashQuadAltHash.getTableSize() << endl;

    // Output reads to file.
    outputFile << chainingTableSize << "," << numSepReads << endl;
    outputFile << probingTableSize << "," << numQuadReads << endl;

    // Reset reads.
    numSepReads = 0;
    numQuadReads = 0;

    // ***** Alternative getKey Function | Alternative Hash Function ***** //
    SeparateChainingAlternative<Exoplanet> hashSepAlt(chainingTableSize, getKeyAlternate);
    QuadraticProbingAlternative<Exoplanet> hashQuadAlt(probingTableSize, getKeyAlternate);
    for(Exoplanet &exo : exoplanets) {
        hashSepAlt.insert(exo, numSepReads);
        hashQuadAlt.insert(exo, numQuadReads);
    }
    cout << "Final Table Size: " << hashQuadAlt.getTableSize() << endl;

    // Output reads to file.
    outputFile << chainingTableSize << "," << numSepReads << endl;
    outputFile << probingTableSize << "," << numQuadReads << endl;

    return 0;
}
