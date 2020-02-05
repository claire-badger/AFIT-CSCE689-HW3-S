//
// Created by claire on 2/3/20.
//
#include <cmath>
#include "PCalc_SP.h"


void PCalc_SP::markNonPrimes(){
    this->at(0) = false;
    this->at (1) = false;
    for (int i = 2; i < sqrt(this->size); i++){
        if (this->at(i)){
            for (int j = pow(i,2); j < this->size; j += i){
             this->at(j) = false;
            }
        }
    }
}

PCalc_SP::~PCalc_SP() {
}

