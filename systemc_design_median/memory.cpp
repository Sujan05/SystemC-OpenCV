#include "memory.h"

using namespace std;

void memory::trans_memory() 
{
	//sc_dt::sc_lv<WORD_SIZE> allzs = "ZZZZZZZZZZZZZZZZZZZZZZZZ";
	//sc_dt::sc_lv<WORD_SIZE> allxs = "XXXXXXXXXXXXXXXXXXXXXXXX";

	sc_dt::sc_lv<WORD_SIZE> allzs = "000000000000000000000000";
	sc_dt::sc_lv<WORD_SIZE> allxs = "XXXXXXXXXXXXXXXXXXXXXXXX";

	if(en){
		if(rw){
			if(addr.read() < MEM_SIZE)
				data_out = ram[addr.read()];
			else{
				data_out = allxs;
				cout<<"Address "<< addr <<" out of range for read operation"<<endl;	
			    }
		      }
		else{
			if(addr.read() < MEM_SIZE)
				ram[addr.read()] = data_in;
			else{
				ram[addr.read()] = allxs;
				cout<<"Address "<< addr <<" out of range for write operation"<<endl;
																	
			    }
		    }

	      }
	else
		data_out = allzs;
}


