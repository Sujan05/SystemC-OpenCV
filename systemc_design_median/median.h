#ifndef MEDIAN_H_
#define MEDIAN_H_

#include <systemc>
#include "memory.h"

using namespace sc_core;

//const int WORD_SIZE = 24;
const int KERNEL_SIZE = 15; // Kernel size should be a odd number

 
SC_MODULE(median){
 
    sc_in<bool> go, clk;
    sc_out<bool> done;
    sc_in<sc_dt::sc_int<WORD_SIZE> > pixel_in;
    sc_out<sc_dt::sc_int<WORD_SIZE> > pixel_out;
    int i, j;

    void median_kernel();
    void insertionSort();

    sc_dt::sc_int<WORD_SIZE> array[KERNEL_SIZE];

    SC_CTOR(median){
	SC_CTHREAD(median_kernel, clk.pos());
	done.initialize(false);
	i = 0;
	j = 0;
    }
  };
#endif /* MEDIAN_H_ */
