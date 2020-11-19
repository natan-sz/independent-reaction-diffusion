#include <iostream>
#include <unistd.h>
#include <vector>
#include <iomanip>
saa
/*
 * Title: Reaction Diffusion Simulation
 * Author: Natan Szczepaniak
 * Description: Simulation of the "Turing Pattern" using the
 * Grey-Scott Model
 *
 * Version: 0.0
 */

const int iterations = 1000;

// Set matrix parameters
const int WIDTH = 20;
const int HEIGHT = 20;

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

// Convolution function
std::vector<std::vector<double> > conv2D(std::vector<std::vector<double>>& M) {

	// Initialise kernel used for convolution
	double kernel[KSIZE][KSIZE] = {	
		{cor,adj,cor},
		{adj,cen,adj},
		{cor,adj,cor},
	};

	std::vector<std::vector<double> > L (WIDTH, std::vector<double> (HEIGHT,0));

	// Extremely inefficient 2d convolution
	for (int i=1; i < WIDTH-KCENTER; ++i) {
		for (int j=1; j < HEIGHT-KCENTER; ++j) {
			double sum = 0;
			for (int k=0; k < 2; ++k) {
				for (int l = 0; l < 2; ++l) {
					sum += kernel[k][l] * M[i - KCENTER + k][j - KCENTER + l];
				}
			}
			L[i][j] = sum;
		}
	}
	return L;
}


// Function including the Gray-Scott equations
void update (std::vector<std::vector<double>>& A, std::vector<std::vector<double>>& B) {
	
	std::vector<std::vector<double>> C;
	std::vector<std::vector<double>> D;

	C = conv2D(A);
	D = conv2D(B);

	//Iteration through all of the values of the array to update each one
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			double diff_A = (DIFFUSION_A * conv2D(A)[i][j] - (A[i][j] * B[i][j] * B[i][j] + (FEED * 1 - A[i][j])));
			double diff_B = (DIFFUSION_B * conv2D(B)[i][j] + (A[i][j] * B[i][j] * B[i][j] + ((KILL + FEED) * B[i][j])));

			A[i][j] += diff_A;
			B[i][j] += diff_B;
		}
	} 

}

int main () {

	// Assign two 2D arrays
	std::vector<std::vector<double> > array_A (WIDTH, std::vector<double> (HEIGHT,0));
	std::vector<std::vector<double> > array_B (WIDTH, std::vector<double> (HEIGHT,0));

	// Set the values
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (i >= WIDTH/4 && i <= (WIDTH*3)/4 && j >= HEIGHT/4 && j <= (HEIGHT*3)/4) {
				array_A[i][j] = 1;
			}
		}
	} 
	
	//Main Simulation loop
	for (int i = 0; i <= iterations ; ++i){
		std::cout << "Iteration " << i << ":" << std::endl;
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
			    std::cout << std::fixed << std::setprecision(1) << array_A[i][j];
			}
			std::cout << std::endl;
		} 

		update(array_A,array_B);

		usleep(1000000);
		system("clear");
	}

	return 0;
}
