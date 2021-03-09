# SystemC-OpenCV
This project is to develop image processing systems using SystemC and OpenCV. The OpenCV libraries are used along with SystemC library functions to implement the application. The input pictures are read using OpenCV, processed in SystemC and displayed with OpenCV. 

The following figure shows the structure of the image processing system.

<p align="center"> <img width="640" src="https://github.com/Sujan05/SystemC-OpenCV/blob/master/Image/image_processing.png"/> </p>
<p align="center">
	Figure: Image Processing System
</p>

The initial image frame is stored in memory_0 (input module). The processing module reads the image frame from memory_0 on a pixel-by-pixel basis (24 bits RGB data). The processing module will then apply a convolution filter on the image and send it to memory_1 (output module), which will store the processed image. The processing module is modular, and it can be replaced by other modules performing a different computation without affecting the rest of the design, which makes the use of interfaces ideal.

As processing modules, you will implement the following two modules:

1. Median Filter
2. Sobel Edge Detector
