#!/usr/bin/env python3

# Reaction Diffusion Simulator
# By Natan Szczepaniak
#
# Simulates a reaction between arbitrary chemicals "A" and
# to "B" to obtain a pattern displayed. The Simulation
# relies on 5 parameters. Varying these parameters creates
# various different patterns.
#
# N - resolution of the simulation (aspect ratio 1:1)
# DA - Diffusion rate of chemical A
# DB - Diffusion rate of chemical B
# feed - rate at which the chemical is fed into the system
# kill - rate at which chemical "dies" off


import os
import time
import numpy as np
import matplotlib.pyplot as plt
import sys
import matplotlib.animation as animation
import cv2

# Set Constants
DA = 1.0
DB = 0.5
feed = 0.034
k = 0.060


# Create a scanning kernel
cen = -1
adj = 0.2
cor = 0.05

kernel = np.array([[cor, adj, cor], [adj, cen, adj], [cor, adj, cor]])


# Function updates the matrix by one iteration
def update(A, B, DA, DB, feed, k, N, kernel):
    diff_A = (DA * cv2.filter2D(A, -1, kernel)) - (A * B**2) + (feed * (1 - A))
    diff_B = (DB * cv2.filter2D(B, -1, kernel)) + (A * B**2) - ((k + feed) * B)

    A += diff_A
    B += diff_B

    return A, B

# Parameters for testing purposes
n_average = 5

# arrays to hold the size of array and the average time for the corresponding array
sequence = range(1,1000)
avg_times = []

for N in sequence:

    # Initialise Chemicals A & B
    A = np.ones((N, N))
    B = np.zeros((N, N))

    # Set initial matrix (Add Square to the middle)
    N2 = N // 2
    r = int(N / 10.0)

    A[N2 - r:N2 + r, N2 - r:N2 + r] = 0.5
    B[N2 - r:N2 + r, N2 - r:N2 + r] = 0.25

    total_time = 0

    #Function to run the function n_average times and take an average
    print(N)
    for i in range(n_average):
        start = time.time()
        update(A, B, DA, DB, feed, k, N, kernel)
        end = time.time()

        total_time += (end-start)

    avg_times.append((total_time/float(n_average)))

x = list(sequence)
y = avg_times

plt.plot(x,y,"r.")
plt.title("Average run-time of function against array size (Python|FFT)",fontweight="bold")
plt.xlabel("Size of input array N",fontweight="bold")
plt.ylabel("Average run time T (s)",fontweight="bold")
plt.show()
