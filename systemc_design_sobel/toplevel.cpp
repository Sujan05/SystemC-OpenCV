#include <opencv2/opencv.hpp>
#include <systemc>
#include "input.h"
#include "output.h"
#include "memory.h"
#include "sobel.h"
#include <iostream>
#include <vector>

enum {
	CV_IMWRITE_JPEG_QUALITY=1
};

using namespace cv;
using namespace std;

int sc_main(int argc, char** argv){
	Mat imagein, imageout;
	
	if (argc < 2)	{
		cout << "Image file not provided. \n\nExiting..." << endl;
		return -1;
	}
	
	imagein = imread( argv[1], 1 ); //read image from file

	input in("input"); //input module
	memory ram0("ram0"); //ram0 module
	sobel my_sobel("my_sobel"); //median filter module
	memory ram1("ram1"); //ram1 module
	output out("output"); //output module

	sc_signal<sc_dt::sc_int<24> > pixel; //24 bit signal to transfer pixel data between modules
	sc_signal<bool> done_input; //signal when input module is done transferring
	sc_signal<bool> done_output; //signal when output module is done transferring
	sc_signal<bool> go_output;   //go signal for output module
	sc_signal<bool> en_ram0; // enable signal for ram0
	sc_signal<bool> rw_ram0; // read/write signal for ram0
	sc_signal<bool> en_ram1; // enable signal for ram1
	sc_signal<bool> rw_ram1; // read/write signal for ram1
	sc_signal<bool> go_sobel; // go signal for median filter
	sc_signal<bool> done_sobel; // done signal for median filter
	sc_signal<sc_dt::sc_int<ADDR_SIZE> > addr_ram0; //address signal for ram0
	sc_signal<sc_dt::sc_int<ADDR_SIZE> > addr_ram1; //address signal for ram1
	sc_signal<sc_dt::sc_int<24> > dataout_ram0; 
	sc_signal<sc_dt::sc_int<24> > dataout_ram1;
	sc_signal<sc_dt::sc_int<24> > pixel_out_sobel; 
	sc_dt::sc_int<ADDR_SIZE> int_addr_ram0;
	sc_dt::sc_int<ADDR_SIZE> int_addr_ram1;
	sc_clock clk("clk",10,SC_NS,0.5);

	int num_pixel, i, j, num_iteration;

	in.pixel(pixel);
	in.done(done_input);
	in.clk(clk);

	out.pixel(dataout_ram1);
	out.go(go_output);
	out.done(done_output);
	out.clk(clk);

	ram0.en(en_ram0);
	ram0.rw(rw_ram0);
	ram0.clk(clk);
	ram0.addr(addr_ram0);
	ram0.data_in(pixel);
	ram0.data_out(dataout_ram0);

	my_sobel.go(go_sobel);
	my_sobel.done(done_sobel);
	my_sobel.clk(clk);
	my_sobel.pixel_in(dataout_ram0);
	my_sobel.pixel_out(pixel_out_sobel);

	ram1.en(en_ram1);
	ram1.rw(rw_ram1);
	ram1.clk(clk);
	ram1.addr(addr_ram1);
	ram1.data_in(pixel_out_sobel);
	ram1.data_out(dataout_ram1);

	in.setImage(imagein); //provides image to input module
	out.setMat(imagein.rows, imagein.cols); //provide image dimensions

	cout << "image row size = "<< imagein.rows << endl;
	cout << "image col size = "<< imagein.cols << endl;
	 
	int_addr_ram0 = "00000000";
	cout << "Starting Identity Function...\n" << endl;
	while(!done_input){ //run simulation till done signal is asserted
		//sc_start(100, SC_NS);
		// added by sujan 
		en_ram0.write(1);
		rw_ram0.write(0);
		//data.write(test_mem[i]);
		//data_in.write(i);
		addr_ram0.write(int_addr_ram0);
		sc_start(50, SC_NS);
		int_addr_ram0 = int_addr_ram0 + 1;
		//cout << addr_ram0.read() <<endl;
		if (addr_ram0.read() < 40) {
			cout <<"value from input at addr: "<< addr_ram0.read() <<" is "<<pixel.read()<<endl;
		}
		go_output.write(false);
	}

	//cout << "int_addr = "<<int_addr <<endl;
	num_pixel = int_addr_ram0;
	//go_output.write(true);
	int_addr_ram0 = "00000000";
	int_addr_ram1 = "00000000";
	num_iteration = num_pixel;

	for(i = 0; i < num_iteration; i++){
		for(j = 0; j < KERNEL_SIZE; j++){
			go_sobel.write(true);
			en_ram0.write(1);
			rw_ram0.write(1);
			//int_addr_ram0 = int_addr_ram0 + i * KERNEL_SIZE + j;
			int_addr_ram0 = i + j;
			addr_ram0.write(int_addr_ram0);
			sc_start(10, SC_NS);
		if (addr_ram0.read() < 40) {
		cout <<"value from ram0 at addr: "<< addr_ram0.read() <<" is "<<dataout_ram0.read()<<endl;
			}
		}

		//while(!done_sobel) {
			sc_start(10, SC_NS);
		//}
        
		go_sobel.write(true);
		en_ram1.write(1);
		rw_ram1.write(0);
		int_addr_ram1 = i ;
		addr_ram1.write(int_addr_ram1);
		sc_start(10, SC_NS);
		/*
		for(j = 0; j < KERNEL_SIZE; j++){
			go_median.write(true);
			en_ram1.write(1);
			rw_ram1.write(0);
			//int_addr_ram1 = int_addr_ram1 + i * KERNEL_SIZE + j;
			int_addr_ram1 = i * KERNEL_SIZE + j;
			addr_ram1.write(int_addr_ram1);
			sc_start(10, SC_NS);
		if (addr_ram1.read() < 40) {
		cout <<"value from median at addr: "<< addr_ram1.read() <<" is "<<pixel_out_median.read()<<endl;
		}
		}
		while(done_sobel){
			sc_start(10, SC_NS);
		}*/
	}
	/*
	for(i = 0; i < num_pixel; i++){
		en_ram0.write(1);
		rw_ram0.write(1);
		addr_ram0.write(int_addr);
		en_ram1.write(1);
		rw_ram1.write(0);
		addr_ram1.write(int_addr);
		sc_start(100, SC_NS);
		int_addr = int_addr + 1;
		//cout <<"value writen at addr: << addr "<<" is "<<data_in.read()<<endl;
		go_output.write(false);
	}
	*/
	int_addr_ram1 = "00000000";
	while(!done_output){ //run simulation till done signal is asserted
		// added by sujan 
		go_output.write(true);
		en_ram1.write(1);
		rw_ram1.write(1);
		addr_ram1.write(int_addr_ram1);
		sc_start(50, SC_NS);
		int_addr_ram1 = int_addr_ram1 + 1;
		if (addr_ram1.read() < 40) {
			cout <<"value from ram1 at addr: "<< addr_ram1.read() <<" is "<<dataout_ram1.read()<<endl;
		}
		
	}
	//cout << "int_addr = "<<int_addr <<endl;
	imageout = out.getImage();
	vector<int> params;
	params.push_back(CV_IMWRITE_JPEG_QUALITY);
	params.push_back(95);
	
	char outName[40];
	
	strcpy(outName, "copy_");	
	strcat(outName, argv[1]);


	imwrite(outName, imageout, params); //write image

	cout << "Finished Workload" << endl;

	return 0;
}
