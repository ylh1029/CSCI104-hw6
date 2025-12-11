#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T result = 0;
        unsigned long long w[5] = {0, 0, 0, 0, 0};

        for(size_t i = 0; i < k.length()/6+1; i++){
            int max = k.length() - 1 - (6 * i);
            int currpos = max - 5;
            unsigned long long val = 0;
            for(int j = 0; j < 6; j++){
                if (k[currpos]){
                    val = val * 36 + letterDigitToNumber(k[currpos]);
                }
                currpos++;
            }
            w[4-i] = val;
        } 

        for(size_t i = 0; i < 5; i++){
            result += w[i] * rValues[i];
        }

        return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        // 122-97, 90-65, 57-48 
        if(letter > 90){
        //Letter is lower-case
            return letter - 'a';
        }

        else if(letter > 57){
        //Letter is upper-case
            return letter - 'A';
        }

        else{
        // Letter is numbers
            return letter - '0' + 26;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
