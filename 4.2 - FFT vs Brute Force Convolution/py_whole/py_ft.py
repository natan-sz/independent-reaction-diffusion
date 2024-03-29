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


import numpy as np
import matplotlib.pyplot as plt
import sys
import matplotlib.animation as animation
import cv2

# Set Constants
N = int(sys.argv[1])
DA = 1.0
DB = 0.5
feed = 0.034
k = 0.060

# Initialise Chemicals A & B
A = np.ones((N, N))
B = np.zeros((N, N))

# Set initial matrix (Add Square to the middle)
N2 = N // 2
r = int(N / 10.0)

A[N2 - r:N2 + r, N2 - r:N2 + r] = 0.5
B[N2 - r:N2 + r, N2 - r:N2 + r] = 0.25

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


# Live Preview (Errors at larger simulations)
#fig, axes = plt.subplots()
#im = plt.imshow(B, animated=True, vmin=0, vmax=1)
#plt.set_cmap("rainbow")
#plt.axis("off")
#fig.subplots_adjust(0, 0, 1, 1)
#fig.tight_layout(pad=0)

# Function iterates and animates the matrix evolution
#def animate(i):
#    for n in range(100):
#        update(A, B, DA, DB, feed, k, N, kernel)
#        im.set_array(A)
#    return [im]
#
#
#ani = animation.FuncAnimation(fig, animate, blit=True, interval=250)
#plt.show()
update(A, B, DA, DB, feed, k, N, kernel)
# Uncomment to enable non-preview mode (faster)
# No live preview (only last frame)
#iter = 10
#
#for i in range(iter):
#    update(A, B, DA, DB, feed, k, N, kernel)
#    print(str(float(float(i) * 100.0 // iter)) + "%", end="\r", flush=True)
#
#print("Done!")
#plt.imshow(A)
##plt.savefig("reaction.png", dpi=300)
#plt.show()

# TO DO:
#   - Add documentation
#   - Create a CLI interface (Setting parameters)
#   - Check for more FFT methods
#   - Rewrite in C
