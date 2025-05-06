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
        //to store string segs
        unsigned long long w[5] = {0};
        int index = 4;
        int len = k.size();

        //process in chunks of 6 chars
        for(int i = len; i > 0; i-=6) {
          unsigned long long val = 0;

          //converting to base 36 int
          for(int j = std::max(0, i - 6); j < i; j++) {
            val = val * 36 + letterDigitToNumber(k[j]);
          }
          w[index--] = val;
        }
        //use rvals to find hash value
        unsigned long long hashVal = 0;
        for(int i = 0; i < 5; i++) {
          hashVal += rValues[i] * w[i];
        }

        return hashVal;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = std::tolower(letter);

        if(letter >= '0' && letter <= '9') return letter - '0' + 26;
        else if(letter >= 'a' && letter <= 'z') return letter - 'a';

        return 0;
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
