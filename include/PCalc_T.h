#ifndef PCALC_T_H
#define PCALC_T_H
#include <map>
#include "PCalc.h"
#include <thread>
#include <vector>

// Your implementation of PCalc_T class should go here. 
// Make sure your constructor takes in two parameters:

// PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads);

// Call the parent constructor when initializing your constructor and pass in array_size. Then
// use num_threads to cap off how many threads you use to calculate all prime numbers

const unsigned int size = 50;
// Add your PCalc_SP class definition here as a child class of PCalc
// Be sure to overload the right methods from PCalc or it won't compile

// This class should manage the single process implementation of the prime number generator. I'd recommend
// getting this working first, then tackling multithreaded
class PCalc_T : public PCalc{
public:

    PCalc_T(unsigned int array_size, unsigned int num_threads): PCalc(array_size) {this->size = array_size; this->thread_num = num_threads;}

    ~PCalc_T() override;

    void markNonPrimes() override;

    void thread_helper(unsigned int num);

    int lowestVal (std::map <std::thread::id, unsigned int>);

    //void cleanup();

private:
    PCalc_T () : PCalc(size) {}
    unsigned int size;
    unsigned int thread_num;
    std::map <std::thread::id, unsigned  int> running;
};

#endif
