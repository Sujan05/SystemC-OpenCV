#ifndef SOBEL_H_
#define SOBEL_H_

#include <systemc>
#include "memory.h"
using namespace sc_core;

//const int WORD_SIZE = 24;
const int KERNEL_SIZE = 9; // Kernel size should be a odd number

 
SC_MODULE(sobel){
 
    sc_in<bool> go, clk;
    sc_out<bool> done;
    sc_in<sc_dt::sc_int<WORD_SIZE> > pixel_in;
    sc_out<sc_dt::sc_int<WORD_SIZE> > pixel_out;
    int i, j;

    void sobel_filter();
    int convolution_x();
    int convolution_y();

    sc_dt::sc_int<WORD_SIZE> array[KERNEL_SIZE];

    SC_CTOR(sobel){
	SC_CTHREAD(sobel_filter, clk.pos());
	done.initialize(false);
	i = 0;
	j = 0;
    }
  };
#endif /* SOBEL_H_ */
