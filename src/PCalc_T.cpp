//
// Created by claire on 2/3/20.
//

#include "PCalc_T.h"
#include <cmath>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <future>
#include <iostream>
/**
 * The idea of segmented sieve is to divide the range [0..n-1] in different segments and compute primes in all segments one by one. This algorithm first uses Simple Sieve to find primes smaller than or equal to √(n). Below are steps used in Segmented Sieve.

Use Simple Sieve to find all primes upto square root of ‘n’ and store these primes in an array “prime[]”. Store the found primes in an array ‘prime[]’.
We need all primes in range [0..n-1]. We divide this range in different segments such that size of every segment is at-most √n
Do following for every segment [low..high]
Create an array mark[high-low+1]. Here we need only O(x) space where x is number of elements in given range.
Iterate through all primes found in step 1. For every prime, mark its multiples in given range [low..high].
 * */


/*
 * markNonPrimes():
 * */
void PCalc_T::markNonPrimes(){
    std::vector <std::thread> thread_list;
    this->at(0) = false;
    this->at (1) = false;
    unsigned int p = 1;
    while ((p+1) < sqrt(this->size)) {

            for (unsigned int i = 0; i < (this->thread_num - thread_list.size()); i++) { //go through all open threads

                if ((p + 1) > sqrt(this->size)) //makes sure not over the size
                    break;

                if (this->at(p+1)) { //makes sure its not a number marked non prime

                    //if ((p+1) < lowestVal(running)) {
                        p++;
                        std::function<void()> func = [this, p]() { //lambda for thread
                            thread_helper(p);
                        };
                        thread_list.emplace_back(std::thread(func));
                        running[thread_list.back().get_id()] = (p);
                   //} //else
                     //  p++;
               }
                else
                    p++;
            }

        int i = 0;
        for (auto &t : thread_list) {
            if (t.joinable()) {
                t.join();
                thread_list.erase(thread_list.begin()+i);
            }
            i++;
        }
    }
    for (auto &t : thread_list) {
        if (t.joinable())
            t.join();
    }
}

/*
 * lowestVal(map)
 * find the lowest value in the map of threads mapped to their current values
 * */
int PCalc_T::lowestVal (std::map <std::thread::id, unsigned int> map_comp){
    int lowest = 1000000000;
    for (auto [key, value]: map_comp) {
        if (value < lowest)
            lowest = value;
    }
    return lowest;
}

/*
 * thread_helper(num):
 * parameters: number to mark off multiples as non prime
 * also changes the std::map keeping track of the min value of the threads
 * */
void PCalc_T::thread_helper(unsigned int num){
    std::mutex mtx;
    for (unsigned int j = pow(num, 2); j < this->size; j += num) {
        mtx.lock();
        running[std::this_thread::get_id()] = j;
        mtx.unlock();
        this->at(j) = false;
    }
    running.erase(std::this_thread::get_id());
}


PCalc_T::~PCalc_T() {

}