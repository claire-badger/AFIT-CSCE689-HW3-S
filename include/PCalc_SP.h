#ifndef PCALC_SP_H
#define PCALC_SP_H

#include "PCalc.h"

//const unsigned int size = 50;
// Add your PCalc_SP class definition here as a child class of PCalc
// Be sure to overload the right methods from PCalc or it won't compile

// This class should manage the single process implementation of the prime number generator. I'd recommend
// getting this working first, then tackling multithreaded
class PCalc_SP : public PCalc{
public:

    explicit PCalc_SP(unsigned int num) : PCalc(num) {this->size = num;}

    ~PCalc_SP() override;

    void markNonPrimes() override;

    //void cleanup();

private:
    PCalc_SP () : PCalc(size){};

    unsigned int size{};

};

#endif
