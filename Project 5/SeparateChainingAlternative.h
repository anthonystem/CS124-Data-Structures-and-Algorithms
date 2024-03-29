/**
* Created by Lisa Dion on 11/5/21.
* Modified by Anthony Stem for Project 5.
*/


#ifndef PROJECT5_SEPARATECHAININGALTERNATIVE_H
#define PROJECT5_SEPARATECHAININGALTERNATIVE_H

#include <functional>
#include <string>
#include <vector>
using std::function, std::string, std::vector;

#include <optional>
using std::optional;
using std::nullopt;
using std::make_optional;

template<typename Hashable>
class SeparateChainingAlternative {
private:
    unsigned long tableSize;
    vector<vector<Hashable>> table;
    function<string(Hashable)> getKey;

    // Modified Horner Hash function. Value is changed to 13 instead of 37.
    unsigned long modifiedHornerHash(string key) {
        unsigned long hashVal = 0;
        for (char letter : key) {
            hashVal = hashVal * 13 + letter;
        }
        return hashVal % tableSize;
    }

    // Find the next prime number
    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }
        bool prime = false;
        while (!prime) {
            prime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                }
            }
            n += 2;
        }
        return (n-2);
    }

public:
    // Constructor
    SeparateChainingAlternative(unsigned long tableSize, function<string(Hashable)> getKey) {
        this->tableSize = nextPrime(tableSize);
        this->getKey = getKey;
        table.resize(this->tableSize);
    }

    // Insert
    void insert(Hashable item, int &reads) {
        // get a key from the item
        string key = getKey(item);
        // only insert if the key is not already in the table
        if (find(key, reads)) {
            // the key is already in the table. No duplicates allowed.
            return;
        }
        // hash the key into an index
        unsigned long index = modifiedHornerHash(key);
        // store the item at the index
        table[index].push_back(item);
    }

    // Find
    optional<Hashable> find(string key, int &reads) {
        // hash the key into an index
        unsigned long index = modifiedHornerHash(key);
        // Check if the vector at the index has the item we're looking for
        for (int i = 0; i < table[index].size(); ++i) {
            ++reads;
            if (getKey(table[index][i]) == key) { // 1 read
                // Found the item
                return table[index][i];
            }
        }
        return nullopt;
    }

    // Remove
    bool remove(string key) {
        // hash the key into an index
        unsigned long index = modifiedHornerHash(key);
        // Check if the vector at the index has the item we're looking for
        for (int i = 0; i < table[index].size(); ++i) {
            if (getKey(table[index][i]) == key) {
                // Found the item. Remove it.
                table[index].erase(table[index].begin() + i);
                return table[index][i];
            }
        }
        return false;
    }
};

#endif //PROJECT5_SEPARATECHAININGALTERNATIVE_H
