#include "median.h"

using namespace std;

/* Function to sort an array using insertion sort*/
void median::insertionSort() 
{ 
    int i, j; 
    sc_dt::sc_int<8> key_R, key_G, key_B;
    for (i = 1; i < KERNEL_SIZE; i++)
    { 
        key_R = array[i].range(7,0); 
        j = i - 1; 

        while (j >= 0 && array[j].range(7,0) > key_R)
        { 
            array[j + 1].range(7,0) = array[j].range(7,0); 
            j = j - 1; 
        } 
        array[j + 1].range(7,0) = key_R; 
    } 

    for (i = 1; i < KERNEL_SIZE; i++)
    { 
        key_G = array[i].range(15,8); 
        j = i - 1; 

        while (j >= 0 && array[j].range(15,8) > key_G)
        { 
            array[j + 1].range(15,8) = array[j].range(15,8); 
            j = j - 1; 
        } 
        array[j + 1].range(15,8) = key_G; 
    } 
    
    for (i = 1; i < KERNEL_SIZE; i++)
    { 
        key_B = array[i].range(23,16); 
        j = i - 1; 

        while (j >= 0 && array[j].range(23,16) > key_B)
        { 
            array[j + 1].range(23,16) = array[j].range(23,16); 
            j = j - 1; 
        } 
        array[j + 1].range(23,16) = key_B; 
    } 
}

void median::median_kernel() 
{
	sc_dt::sc_lv<WORD_SIZE> allzs = "000000000000000000000000";
	sc_dt::sc_lv<WORD_SIZE> allxs = "XXXXXXXXXXXXXXXXXXXXXXXX";

	bool done_internal = false;

	while(true){
	if (go) {
		//modified code
		if (done_internal == false){
			if(i < KERNEL_SIZE){
				array[i] = pixel_in.read();
				i++;
				pixel_out = allzs;
				//cout <<" inside i = "<< pixel_in.read() << endl;
				//cout <<" AAAAA "<< endl;
				done = false;
			}
			else {
				done_internal = true;
				done = true;
				i = 0;
				insertionSort();
				//cout <<"BBBBB"<< endl;
				pixel_out = allzs;
			}
		}
		else {
			if(j < KERNEL_SIZE){
				pixel_out = array[((KERNEL_SIZE+1)/2)-1];
				j++;
				done = true;
				//cout <<"CCCCC"<< endl;
			}
			else {
				j = 0;
				done = false;
				done_internal = false;
				pixel_out = allzs;
				//cout <<"DDDDD"<< endl;
			}
		}
	}
	else {
		pixel_out = allzs;
		done = false;
		i = 0;
		j = 0;
		for (i = 0; i < KERNEL_SIZE; i++){
			array[i] = allzs;
		}
	}
	wait();
	wait();
	wait();
	wait();
	wait();
	}
}

