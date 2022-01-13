/**
 * Anthony Stem
 * CS 124 - Section C
 */
#include "Exoplanet.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Create vector of Exoplanets.
    vector<Exoplanet> exoplanets;

    // Read in data from file.
    readFile("../exoplanet_dataset.csv", exoplanets);

    // Print out the exoplanets vector and headers with nice formatting.
    cout << left << setw(9) << "Row #" << setw(30) << "Name";
    cout << right << setw(10) << "Mass (Jm)" << setw(15) << "Radius (Jr)" << setw(25) << "Orbital Period (Days)" << setw(20) << "Discovery Year" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    for(int i = 0; i < exoplanets.size(); ++i) {
        cout << exoplanets[i] << endl;
    }
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;

    // Perform calculation and display the estimated surface gravity of each planet.
    showEstimatedSurfaceGravityValues(exoplanets);
    cout << endl;

    // Verify Exoplanet data was read properly.
    verifyFileInput(exoplanets);
    cout << endl;

    // Verify Exoplanet class is functioning properly.
    testExoplanetClass();
    cout << endl;

    return 0;
}



