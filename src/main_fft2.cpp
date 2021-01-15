#include <iostream>
#include <unistd.h>
#include <vector>
#include <iomanip>
#include "opencv2/imgproc.hpp"
#include <opencv2/core.hpp>
#include "opencv2/highgui.hpp"

/*
 * Title: Reaction Diffusion Simulation
 * Author: Natan Szczepaniak
 * Description: Simulation of the "Turing Pattern" using the
 * Gray-Scott Model
 *
 * Version: 1.0
 */

const int iterations = 10;

// Set matrix parameters
const int WIDTH = 1000;
const int HEIGHT = 1000;

// Set Kernel size
const int KSIZE = 3;
const int KCENTER = KSIZE%2;

// Set feed & kill rate
const float FEED = 0.034;
const float KILL = 0.060;

// Set Diffusion rate of A & B
const float DIFFUSION_A = 1.0;
const float DIFFUSION_B = 0.5;

// Kernel variables
const float cen = -1;
const float adj = 0.2;
const float cor = 0.005;

// Initialise kernel used for convolution
cv::Mat kernel=(cv::Mat_<float>(3,3)<<
	cor,adj,cor,
	adj,cen,adj,		
	cor,adj,cor);

//cv::Mat f_kernel;
cv::Point anchor(kernel.cols - kernel.cols/3 - 1, kernel.rows - kernel.rows/3 - 1);

// Flip code to flip the kernel by -1 on both axis and by 1 on the y axis.
//int flip_code = -1;
//cv::flip(kernel, f_kernel, flip_code);

// Function including the Gray-Scott equations
void update (cv::Mat& A, cv::Mat& B,cv::Mat& conv_A, cv::Mat& conv_B) {
	
	// perform convolution using cv::filter2D()
	cv::filter2D(A, conv_A,-1, kernel, anchor, 0, 4);
	cv::filter2D(B, conv_B,-1, kernel, anchor, 0, 4);

	//Iteration through all of the values of the array to update each one
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			double diff_A = (DIFFUSION_A * conv_A.at<double>(i, j) - (A.at<double>(i, j) * B.at<double>(i, j) * B.at<double>(i, j) + (FEED * 1 - A.at<double>(i, j))));
			double diff_B = (DIFFUSION_B * conv_B.at<double>(i, j) + (A.at<double>(i, j) * B.at<double>(i, j) * B.at<double>(i, j) + ((KILL + FEED) * B.at<double>(i, j))));
	
			A.at<double>(i, j) += diff_A;
			B.at<double>(i, j) += diff_B;
		}
	} 
}

int main () {

	// Assign two 2D arrays
	cv::Mat array_A(WIDTH,HEIGHT,CV_64F);
	cv::Mat array_B(WIDTH,HEIGHT,CV_64F);
	
	// Assign the matrices of convoluted arrays
	cv::Mat conv_A(WIDTH,HEIGHT,CV_64F);
	cv::Mat conv_B(WIDTH,HEIGHT,CV_64F);

	//// Set the values
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (i >= WIDTH/4 && i <= (WIDTH*3)/4 && j >= HEIGHT/4 && j <= (HEIGHT*3)/4) {
				array_A.at<double>(i, j) = 1.0;
			}
		}
	} 
	
	///Main Simulation loop
	for (int i = 0; i <= iterations ; ++i){
		std::cout << "Iteration " << i << ":" << std::endl;
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
			    //std::cout << std::fixed << std::setprecision(1) << array_A[i][j];
			}
			//std::cout << std::endl;
		} 

		update(array_A,array_B,conv_A,conv_B);

		//usleep(1000000);
		system("clear");
	}
	std::cout << "Done" << std::endl;

	//cv::imshow("kernel",array_A);
	//cv::waitKey(0);

	return 0;
}
