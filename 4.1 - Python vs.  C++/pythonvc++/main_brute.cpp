#include <iostream>
#include <unistd.h>
#include <vector>
#include <iomanip>
#include <cstdlib>

/*
 * Title: Reaction Diffusion Simulation
 * Author: Natan Szczepaniak
 * Description: Simulation of the "Turing Pattern" using the
 * Gray-Scott Model
 *
 * Version: 0.0
 */

const int ITERATIONS = 1;


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
std::vector<std::vector<double> > kernel = {	
	{cor,adj,cor},
	{adj,cen,adj},
	{cor,adj,cor},
};

// Convolution function
void conv2D(std::vector<std::vector<double>>& M, std::vector<std::vector<double>>& conv_M,int WIDTH, int HEIGHT) {

	// Extremely inefficient 2d convolution
	for (int i=1; i < WIDTH-KCENTER; ++i) {
		for (int j=1; j < HEIGHT-KCENTER; ++j) {
			double sum = 0;
			for (int k=0; k < 2; ++k) {
				for (int l = 0; l < 2; ++l) {
					sum += kernel[k][l] * M[i - KCENTER + k][j - KCENTER + l];
				}
			}
			conv_M[i][j] = sum;
		}
	}
}


// Function including the Gray-Scott equations
void update (std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B,std::vector<std::vector<double>>& conv_A, std::vector<std::vector<double>>& conv_B,int WIDTH,int HEIGHT) {

	//Use convolution function on each of the matrices and obtain
	conv2D(A,conv_A,WIDTH,HEIGHT);
	conv2D(B,conv_B,WIDTH,HEIGHT);

	//Iteration through all of the values of the array to update each one
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			double diff_A = (DIFFUSION_A * conv_A[i][j] - (A[i][j] * B[i][j] * B[i][j] + (FEED * 1 - A[i][j])));
			double diff_B = (DIFFUSION_B * conv_B[i][j] + (A[i][j] * B[i][j] * B[i][j] + ((KILL + FEED) * B[i][j])));

			A[i][j] += diff_A;
			B[i][j] += diff_B;
		}
	} 

}

int main (int argc, char *argv[]) {

	// Set matrix parameters
	int WIDTH = atoi(argv[1]);
	int HEIGHT = atoi(argv[1]);

	// Assign two 2D arrays
	std::vector<std::vector<double> > array_A (WIDTH, std::vector<double> (HEIGHT,0));
	std::vector<std::vector<double> > array_B (WIDTH, std::vector<double> (HEIGHT,0));

	std::vector<std::vector<double> > conv_A (WIDTH, std::vector<double> (HEIGHT,0));
	std::vector<std::vector<double> > conv_B (WIDTH, std::vector<double> (HEIGHT,0));

	// Set the values
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (i >= WIDTH/4 && i <= (WIDTH*3)/4 && j >= HEIGHT/4 && j <= (HEIGHT*3)/4) {
				array_A[i][j] = 1;
			}
		}
	} 
	
	//Main Simulation loop
	for (int i = 0; i <= ITERATIONS ; ++i){
		std::cout << "Iteration " << i << ":" << std::endl;
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
			    //std::cout << std::fixed << std::setprecision(1) << array_A[i][j] << ", ";
			}
			//std::cout << std::endl;
		} 

		update(array_A,array_B,conv_A,conv_B,WIDTH,HEIGHT);

		//usleep(1000000);
		//system("clear");
	}
	std::cout << "Done" << std::endl;

	array_A.shrink_to_fit();
	array_B.shrink_to_fit();
	conv_A.shrink_to_fit();
	conv_B.shrink_to_fit();
	

	return 0;
}
