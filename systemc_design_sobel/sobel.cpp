#include "sobel.h"

using namespace std;

int sobel::convolution_x()
{
	int Kernel_mat_x[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
	//int Kernel_mat_x[9] = {3, 0, -3, 10, 0, -10, 3, 0, -3};
	int i, temp;
	temp = 0;
	for (i = 0; i < KERNEL_SIZE; i++){
		temp = temp + array[i] * Kernel_mat_x[i];
	}
	
	return temp;
}

int sobel::convolution_y()
{
	int Kernel_mat_y[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
	//int Kernel_mat_y[9] = {3, 10, 3, 0, 0, 0, -3, -10, -3};
	int i, temp;
	temp = 0;
	for (i = 0; i < KERNEL_SIZE; i++){
		temp = temp + array[i] * Kernel_mat_y[i];
	}
	
	return temp;
}

void sobel::sobel_filter() 
{
	//sc_dt::sc_lv<WORD_SIZE> allzs = "000000000000000000000000";
	//sc_dt::sc_lv<WORD_SIZE> allxs = "XXXXXXXXXXXXXXXXXXXXXXXX";
	//bool done_internal = false;

	int G_x, G_y, G_x_abs, G_y_abs;
	while(true){
		if (go) {
			if(i < KERNEL_SIZE){
				array[i] = pixel_in.read();
				i++;
				//pixel_out = allzs;
				//cout <<" inside i = "<< pixel_in.read() << endl;
				//cout <<" AAAAA "<< endl;
				done = false;
			}
			else {
				//done_internal = true;
				done = true;
				i = 0;
				G_x = convolution_x();
				G_y = convolution_y();
				if (G_x > 0) G_x_abs = G_x;
				else G_x_abs = G_x * (-1);
				if (G_y > 0) G_y_abs = G_y;
				else G_y_abs = G_y * (-1);
				//cout <<"BBBBB"<< endl;
				pixel_out = G_x_abs * 0.5 + G_y_abs * 0.5;
			}
		
		}
		wait();
	}
}
