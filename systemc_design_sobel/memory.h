#ifndef MEMORY_H_
#define MEMORY_H_

#include <systemc>

using namespace sc_core;

const int WORD_SIZE = 24;
const int ADDR_SIZE = 16;
const int MEM_SIZE = 140000;
 
SC_MODULE(memory){
 
    sc_in<bool> en, rw, clk;
    sc_in<sc_dt::sc_int<ADDR_SIZE> > addr;
    sc_in<sc_dt::sc_int<WORD_SIZE> > data_in;
    sc_out<sc_dt::sc_int<WORD_SIZE> > data_out;

    void trans_memory();

    sc_dt::sc_int<WORD_SIZE> ram[MEM_SIZE];

    SC_CTOR(memory){
	SC_METHOD(trans_memory);
	sensitive<<clk.pos();
    }
  };
#endif /* MEMORY_H_ */
