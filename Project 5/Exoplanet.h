/**
 * Anthony Stem
 * CS 124 - Section C
 */
#ifndef PROJECT5_EXOPLANET_H
#define PROJECT5_EXOPLANET_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
using std::string;
using namespace std;

/**
 * A class that represents entries from the exoplanet dataset maintained by the Extrasolar Planets Encyclopaedia.
 * Source: http://exoplanet.eu/
 *
 * name -            a string; the name of the exoplanet.
 * row -             a unique integer; indicates the row number of an object in the database.
 * mass -            a double; represents the mass of an exoplanet (in terms of Jovian mass Jm).
 * planetaryRadius - a double; represents the radius of an exoplanet (in terms of Jovian radii Jm).
 * orbitalPeriod -   a double; represents the orbital period (in Earth days) of an exoplanet around
 *                   its host star.
 * discoveryYear -   an integer; represents the year in which the exoplanet was discovered.
 */
class Exoplanet {
private:
    // Fields
    string name;
    int row, discoveryYear;
    double mass, planetaryRadius, orbitalPeriod;

public:
    // Default constructor. Defaults all numerical values to -1, and defaults the name to "NO ENTRY".
    Exoplanet() {
        this->row = -1;
        this->name = "NO ENTRY";
        this->mass = -1;
        this->planetaryRadius = -1;
        this->orbitalPeriod = -1;
        this->discoveryYear = -1;
    }

    // Alternate constructor.
    Exoplanet(int row, string name, double mass, double planetaryRadius, double orbitalPeriod, int discoveryYear) {
        this->row = row;
        this->name = name;
        this->mass = mass;
        this->planetaryRadius = planetaryRadius;
        this->orbitalPeriod = orbitalPeriod;
        this->discoveryYear = discoveryYear;
    }

    // Getters
    int getRow() {
        return row;
    }

    string getName() {
        return name;
    }

    double getMass() {
        return mass;
    }

    double getPlanetaryRadius() {
        return planetaryRadius;
    }

    double getOrbitalPeriod() {
        return orbitalPeriod;
    }

    int getDiscoveryYear() {
        return discoveryYear;
    }

    // Setters
    void setRow(int row) {
    this->row = row;
    }

    void setName(string name) {
        this->name = name;
    }

    void setMass(double mass) {
        this->mass = mass;
    }

    void setPlanetaryRadius(double planetaryRadius) {
        this->planetaryRadius = planetaryRadius;
    }

    void setOrbitalPeriod(double orbitalPeriod) {
        this->orbitalPeriod = orbitalPeriod;
    }

    void setDiscoveryYear(int discoveryYear) {
        this->discoveryYear = discoveryYear;
    }

    /**
     * Overloads the stream insertion operator '<<' to make the output nicely formatted
     * when printing out an Exoplanet vector.
     */
    friend ostream& operator << (ostream& out, const Exoplanet &exo) {
        out << left << setw(9) << exo.row;
        out << setw(30) << exo.name;
        out << right << setw(10) << exo.mass;
        out << setw(15) << exo.planetaryRadius;
        out << setw(15) << exo.orbitalPeriod;
        out << setw(25) << exo.discoveryYear;
        return out;
    }

    /**
     * Overloads the operator '==' to check equality between two Exoplanet objects.
     */
    friend bool operator == (const Exoplanet &ls, const Exoplanet &rs) {
        return ls.row == rs.row &&
               ls.name == rs.name &&
               ls.mass == rs.mass &&
               ls.planetaryRadius == rs.planetaryRadius &&
               ls.orbitalPeriod == rs.orbitalPeriod &&
               ls.discoveryYear == rs.discoveryYear;
    }

    /**
     * Overloads the operator '<' to check if the left Exoplanet row is less than the right Exoplanet row.
     */
    friend bool operator < (const Exoplanet &ls, const Exoplanet &rs) {
        return ls.row < rs.row;
    }

    /**
     * Overloads the operator '>' to check if the left Exoplanet row is greater than the right Exoplanet row.
     */
    friend bool operator > (const Exoplanet &ls, const Exoplanet &rs) {
        return ls.row > rs.row;
    }

    /**
     * Overloads the operator '<=' to check if the left Exoplanet row is less than or equal to than the right Exoplanet row.
     */
    friend bool operator <= (const Exoplanet &ls, const Exoplanet &rs) {
        return ls.row <= rs.row;
    }

    /**
     * Overloads the operator '>=' to check if the left Exoplanet row is greater than or equal to the right Exoplanet row.
     */
    friend bool operator >= (const Exoplanet &ls, const Exoplanet &rs) {
        return ls.row >= rs.row;
    }
};

/**
 * Reads data from a file into a vector of Exoplanets.
 */
void readFile(string fileName, vector<Exoplanet> &exoplanets) {

    ifstream fileInput;
    fileInput.open(fileName);

    // Check if file is bad.
    if(!fileInput) {
        // Exit with exit code 0 if file is bad.
        exit(0);
    }

    // Get the headers from the file.
    string headers;
    getline(fileInput, headers);

    // Declare variables that will be read in from the file.
    string name;
    double mass, planetaryRadius, orbitalPeriod;
    int row, discoveryYear;
    char comma;

    while(fileInput && fileInput.peek() != EOF) {
        // Read in the row number.
        fileInput >> row;
        fileInput >> comma;

        // Read in the planet name.
        getline(fileInput, name, ',');

        // Read in the planet mass.
        fileInput >> mass;
        if(!fileInput) {
            // Set to -1 if no value and clear stream.
            mass = -1;
            fileInput.clear();
        }
        fileInput >> comma;

        // Read in the planetary radius.
        fileInput >> planetaryRadius;
        if(!fileInput) {
            // Set to -1 if no value and clear stream.
            planetaryRadius = -1;
            fileInput.clear();
        }
        fileInput >> comma;

        // Read in orbital period.
        fileInput >> orbitalPeriod;
        if(!fileInput) {
            // Set to -1 if no value and clear stream.
            orbitalPeriod = -1;
            fileInput.clear();
        }
        fileInput >> comma;

        // Read in the discovery year.
        fileInput >> discoveryYear;

        // Create Exoplanet object and add it to the vector.
        exoplanets.push_back(Exoplanet(row, name, mass, planetaryRadius, orbitalPeriod, discoveryYear));
    }
    fileInput.close();
}

/**
 * Calculates the estimated surface gravity of each Exoplanet in a vector and displays
 * the values in terms of 'g' (acceleration due to gravity on Earth). This function uses the
 * formula F=Gm/r^2, which assumes a perfectly spherical planet, as well as other planetary attributes,
 * to make its calculations, so there may be deviations (error) in the calculated values
 * from the true values for some planets. This function uses the pow() function from <cmath> to make
 * its calculation.
 *
 * Source (<cmath> pow()): https://www.cplusplus.com/reference/cmath/
 */
void showEstimatedSurfaceGravityValues(vector<Exoplanet> &exoplanets) {
    // Constants needed to perform calculation.
    const double GRAVITATIONAL_CONSTANT = 6.6741e-11;
    const double JUPITER_MASS = 1.8981e27;
    const double JUPITER_RADIUS = 7.1492e7;
    const double EARTH_GRAVITY = 9.8067;

    double estimatedSurfaceGravity;

    int numSuccessful = 0; // Used to count the number of entries for which a calculation could be performed.
    int numUnsuccessful = 0; // Used to count the number of entries for which a calculation could NOT be performed.

    // Print headers.
    cout << left << setw(25) << "Name";
    cout << right << "Estimated Surface Gravity (g)" << endl;
    cout << "------------------------------------------------------" << endl;

    // Loop through all the exoplanets in the vector.
    for(int i = 0; i < exoplanets.size(); ++i) {
        // Check if there are valid entries for the mass and planetary radius (>0).
        if(exoplanets[i].getMass() > 0 && exoplanets[i].getPlanetaryRadius() > 0) {
            // Calculate the estimated surface gravity in terms of the acceleration due to gravity on Earth.
            estimatedSurfaceGravity = (GRAVITATIONAL_CONSTANT * JUPITER_MASS * exoplanets[i].getMass()) / (pow((JUPITER_RADIUS * exoplanets[i].getPlanetaryRadius()), 2) * EARTH_GRAVITY);

            // Display the result.
            cout << left << setw(30) << exoplanets[i].getName();
            cout << right << setw(10) << estimatedSurfaceGravity << " g" << endl;

            // Increase the number of successful entries.
            numSuccessful++;
        } else {
            // Increase the number of entries with insufficient data.
            numUnsuccessful++;
        }
    }

    // Report the number of entries for which a calculation could and could not be performed.
    cout << "------------------------------------------------------" << endl;
    cout << numSuccessful << " Entries Successful.";
    cout << "\n" << numUnsuccessful << " Entries Couldn't Not Be Computed.";
    cout << "\n" << numSuccessful + numUnsuccessful << " Total Entries." << endl;
    cout << "------------------------------------------------------" << endl;
}

/**
 * Checks to make sure that the row values are set correctly for every row. If there is an improperly set row,
 * the method prints out that row value in an error message. This method also displays the number of exoplanets stored
 * in the vector (this number should be 3732), as well as the row number of the first and last exoplanets
 * stored in the vector to make sure there is the correct number of entries.
 */
void verifyFileInput(vector<Exoplanet> exoplanets) {
    // Get number of records read in from the file.
    cout << exoplanets.size() << " entries read from the file." << endl;
    // Get the row of the first planet read from the file.
    cout << exoplanets.front().getRow() << " is the first row read from the file saved into the vector." << endl;
    // Get the row of the last planet read from the file.
    cout << exoplanets.back().getRow() << " is the last row read from the file saved into the vector." << endl;

    // Verify that the row number of every Exoplanet object in the vector is set properly.
    int row = exoplanets[0].getRow();
    for(int i = 0; i < exoplanets.size(); ++i) {
        // Verify row number.
        if(row != i + 1) {
            cout << "Error: Improper row set at entry " << i + 1 << "." << endl;
        }
        // Get the next row # from next object in the vector.
        row = exoplanets[i + 1].getRow();
    }
}

/**
 * This method uses assertions to test object instantiation with both default and alternative constructors,
 * as well as the getter methods, setter methods. If any test fails,
 * one of the assertions would cause the program to exit, and an “Assertion failed!” message would be displayed on
 * the console along with the expression that failed the test.
 */
void testExoplanetClass() {
    // Create test Exoplanet object. Test default constructor.
    Exoplanet testExoplanet = Exoplanet();
    assert(testExoplanet.getRow() == -1);
    assert(testExoplanet.getName() == "NO ENTRY");
    assert(testExoplanet.getMass() == -1);
    assert(testExoplanet.getPlanetaryRadius() == -1);
    assert(testExoplanet.getOrbitalPeriod() == -1);
    assert(testExoplanet.getDiscoveryYear() == -1);

    // Test getters and setters.
    testExoplanet.setRow(50);
    assert(testExoplanet.getRow() == 50);
    testExoplanet.setName("A10 Someplanet b");
    assert(testExoplanet.getName() == "A10 Someplanet b");
    testExoplanet.setMass(10);
    assert(testExoplanet.getMass() == 10);
    testExoplanet.setPlanetaryRadius(5);
    assert(testExoplanet.getPlanetaryRadius() == 5);
    testExoplanet.setOrbitalPeriod(100);
    assert(testExoplanet.getOrbitalPeriod() == 100);
    testExoplanet.setDiscoveryYear(2016);
    assert(testExoplanet.getDiscoveryYear() == 2016);

    // Create new test Exoplanet object. Test alternative constructor.
    Exoplanet testExoplanet2 = Exoplanet(5, "1 Coolplanet a", 50, 10, 2000, 2015);
    assert(testExoplanet2.getRow() == 5);
    assert(testExoplanet2.getName() == "1 Coolplanet a");
    assert(testExoplanet2.getMass() == 50);
    assert(testExoplanet2.getPlanetaryRadius() == 10);
    assert(testExoplanet2.getOrbitalPeriod() == 2000);
    assert(testExoplanet2.getDiscoveryYear() == 2015);

    // Print success message if test was successful.
    cout << "Exoplanet Class Test Successful!" << endl;
}

#endif //PROJECT5_EXOPLANET_H
