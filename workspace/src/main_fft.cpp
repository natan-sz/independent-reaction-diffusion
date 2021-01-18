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

// Function that turns std::vector to cv::Mat
cv::Mat vector2mat (std::vector<std::vector<double> >& array) {

	cv::Mat M(array.size(), array.size(), CV_64F);

	for (int i = 0; i < array.size(); i++){
		for (int j = 0; j < array.size(); j++){
			M.at<double>(i,j) = array[i][j];
		}
	}

	return M;
}

// Function including the Gray-Scott equations
void update (std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B) {
	
	// Swap vector input of A and B to cv::Mat
	cv::Mat mat_A = vector2mat(A);
	cv::Mat mat_B = vector2mat(B);
	
	// Create destination matrices
	cv::Mat conv_A(A.size(), A.size(), CV_64F);
	cv::Mat conv_B(B.size(), B.size(), CV_64F);

	// perform convolution using cv::filter2D()
	cv::filter2D(mat_A, conv_A,-1, kernel, anchor, 0, 4);
	cv::filter2D(mat_B, conv_B,-1, kernel, anchor, 0, 4);

	//Iteration through all of the values of the array to update each one
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			double diff_A = (DIFFUSION_A * conv_A.at<double>(i, j) - (A[i][j] * B[i][j] * B[i][j] + (FEED * 1 - A[i][j])));
			double diff_B = (DIFFUSION_B * conv_B.at<double>(i, j) + (A[i][j] * B[i][j] * B[i][j] + ((KILL + FEED) * B[i][j])));
	
			A[i][j] += diff_A;
			B[i][j] += diff_B;
		}
	} 
}

int main () {

	// Assign two 2D arrays
	std::vector<std::vector<double> > array_A (WIDTH, std::vector<double> (HEIGHT,0));
	std::vector<std::vector<double> > array_B (WIDTH, std::vector<double> (HEIGHT,0));

	//// Set the values
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (i >= WIDTH/4 && i <= (WIDTH*3)/4 && j >= HEIGHT/4 && j <= (HEIGHT*3)/4) {
				array_A[i][j] = 1;
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

		update(array_A,array_B);

		//usleep(1000000);
		system("clear");
	}
	std::cout << "Done" << std::endl;

//	cv::imshow("kernel",vector2mat(array_A));
//	cv::waitKey(0);

	return 0;
}
