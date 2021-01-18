#include <iostream>
#include <unistd.h>

/*
 * Title: Reaction Diffusion Simulation
 * Author: Natan Szczepaniak
 * Description: Simulation of the "Turing Pattern" using the
 * Gray-Scott Model
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

// This is potentially the most inefficient way of doing this but should work for now
// In the future this will be replace with FFT
void conv2D(double **M) {

	// Initialise kernel used for convolution
	double kernel[KSIZE][KSIZE] = {	
		{cor,adj,cor},
		{adj,cen,adj},
		{cor,adj,cor},
	};

	// Initialise temporary matrix 
	double** L = new double*[HEIGHT];
	for (int i = 0; i < WIDTH; ++i) {
		L[i] = new double[WIDTH];
	}

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

	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			M[i][j] = L[i][j];
		}
	} 
}

//// This function will update the values of A and B for each cell
//// (PSEUDO CODE CHANGE)
//void updateFunc () {
//
//	// Find the difference after one iteration
//	diff_A = (DA * conv2D(A, -1, kernel)) - (A * B**2) + (feed * (1 - A))    
//	diff_B = (DB * conv2D(B, -1, kernel)) + (A * B**2) - ((k + feed) * B)    
//
//	// Add the difference to previous
//	A += diff_A    
//	B += diff_B 
//}

// Function including the Gray-Scott equations
void update (double **A, double **B) {

	// Initialise 2 2D Arrays of pointers
	double** C = new double*[HEIGHT];
	double** D = new double*[HEIGHT];

	// Populate the previous array with arrays (leading to 2D array) 
	for (int i = 0; i < WIDTH; ++i) {
		C[i] = new double[WIDTH];
		D[i] = new double[WIDTH];
	}

	C = conv2D(A);
	D = conv2D(B);

	//Iteration through all of the values of the array to update each one
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			double diff_A = (DIFFUSION_A ) - (A[i][j] * B[i][j] * B[i][j] + (FEED * 1 - A[i][j]));
			double diff_B = (DIFFUSION_B ) + (A[i][j] * B[i][j] * B[i][j] + ((KILL + FEED) * B[i][j]));

		}
	} 

}

int main () {

	// Initialise 2 2D Arrays of pointers
	double** A = new double*[HEIGHT];
	double** B = new double*[HEIGHT];

	// Populate the previous array with arrays (leading to 2D array) 
	for (int i = 0; i < WIDTH; ++i) {
		A[i] = new double[WIDTH];
		B[i] = new double[WIDTH];
	}


	// Temporary Initial position
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			if (i >= WIDTH/4 && i <= (WIDTH*3)/4 && j >= HEIGHT/4 && j <= (HEIGHT*3)/4) {
				A[i][j] = 1;
			}
		}
	} 

	
	//Main Simulation loop
	for (int i = 0; i <= iterations ; ++i){
		std::cout << "Iteration " << i << ":" << std::endl;
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < WIDTH; ++j) {
			    std::cout << A[i][j];
			}
			std::cout << std::endl;
		} 

		update(A,B);

		usleep(1000000);
		system("clear");
	}

	return 0;
}
