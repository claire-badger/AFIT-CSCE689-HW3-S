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
//std::vector<std::future<void>> futures;
 //so create four threads, right? each calling the helper to make the primes false. so as many as sqrt(size)
/*
       for(auto &e : futures) {
          bool working = e.valid();
       }*/
/*
               std::thread myThread([this, p, i]() {
                   thread_helper((p+i));
               });*/
/*
          futures.push_back (std::async([this,p]() {this->thread_helper(p);})); //use lambda to call the helper and store func in thread*/

void PCalc_T::markNonPrimes(){
    std::vector <std::thread> thread_list;
    this->at(0) = false;
    this->at (1) = false;
    int p = 2;
    while (p < sqrt(this->size)) {
        if (thread_list.size() < this->thread_num) {
            for (int i = 0; i < (this->thread_num - thread_list.size()); i++) { //go through all open threads
                std::function<void()> func = [this, p, i]() { thread_helper(p + i); }; //lambda to call helper function
                thread_list.emplace_back(std::thread(func));
                running[thread_list.back().get_id()] = (p+i);
            }
        }
        for (auto &t : thread_list) {
            if (t.joinable()) {
                t.join();
                p++;
            }
        }
    }
}

void PCalc_T::thread_helper(int num){
    int help = (running.find(std::this_thread::get_id())->second);
    while (help < sqrt(this->size)) {
        if (num > size)
            return;
            std::mutex mtx;
            //std::cout<<"thread created for " << num << "\n";
            if (this->at(num)) {
                for (int j = pow(num, 2); j < this->size; j += num) {
                    mtx.lock(); //mutex lock for shared resource
                    this->at(j) = false;
                    mtx.unlock();
                }
            }
        int max = 0;
        for (const auto& [key, value]: running) {if (value > max) max = value;}
        num = max + 1;
        running[std::this_thread::get_id()] = num;
        }
    return;
}

PCalc_T::~PCalc_T() {

}