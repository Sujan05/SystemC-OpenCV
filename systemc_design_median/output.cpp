#include "output.h"

void output::buildImage(){
	while(true){
		if (it == end){
			done = true;
		}
		else if (go && count >= I.cols + 7){ //delays till fifo is full
			sc_dt::sc_int<24> tempsc;
			tempsc = pixel.read();
			(*it)[0] = tempsc.range(7,0); //puts RGB values into Mat variable
			(*it)[1] = tempsc.range(15,8);
			(*it)[2] = tempsc.range(23,16);
			it++;
		}
		count++;
		wait();
	}
}

void output::setMat(int rows, int cols){
	Mat temp(rows,cols, CV_8UC3, Scalar(0,0,0)); //sets up image with correct dimensions
	I = temp;
	it = I.begin<Vec3b>();
	end = I.end<Vec3b>();
}

Mat& output::getImage(){
	return I;
}



