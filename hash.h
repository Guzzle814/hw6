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
      unsigned long long w[5] = {};
      int num = 4;
      int pos = k.size();
      while(pos > 0 && num >= 0)
      {
        int start = std::max(0, pos-6);
        for(int i = start; i < pos; i++)
        {
          w[num] = w[num]*36 + letterDigitToNumber(k[i]);
        }

        num--;
        pos = start;
      }

      HASH_INDEX_T target = 0; 
      for(int i = 0; i<5; i++)
      {
        //In our task, computation between long unsigned int and int should not have an issue
        target = target + rValues[i]*w[i]; 
      }
      
      return target;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
      // Add code here or delete this helper function if you do not want it
      char c = letter;//don't want to type "letter" all the time
      c = std::tolower(c);
      if(c >='a' && c<= 'z') return c - 'a';
      if(c >= '0' && c<= '9') return (c - '0') + 26;
      else return 0;
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
