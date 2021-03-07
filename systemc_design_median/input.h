#ifndef INPUT_H_
#define INPUT_H_

#include <systemc>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace sc_core;

SC_MODULE(input){
	Mat I;
	MatIterator_<Vec3b> it;
	MatIterator_<Vec3b> end;
	sc_out<sc_dt::sc_int<24> > pixel;
	sc_in_clk clk;
	sc_out<bool> done;
	int count;

	void nextPixel();
	void setImage(Mat& imagein);

	SC_CTOR(input){
		SC_CTHREAD(nextPixel, clk.pos());
		done.initialize(false);
		Mat temp;
		I = temp; //temporary init
		count = 0;
	}

};


#endif
