import time
import numpy as np
import matplotlib.pyplot as plt

# Parameters for testing purposes
total_time = 0
n_average = 100

# arrays to hold the size of array and the average time for the corresponding array
sequence = range(1,100)
avg_times = []

# Function to sum all the elements in the function
def sum_array(array):
    total = 0           # O(1)
    for row in array:   # N^2
        for i in row:   
            total += i  # O(1)
    return array        # O(1)

for N in sequence:
    #Function to run the function n_average times and take an average
    for i in range(n_average):
        start = time.time()
        total = sum_array(np.full((N,N),1))    # total is assigned to variable to avoid caching value
        end = time.time()

        total_time += (end-start)

    avg_times.append((total_time/float(n_average)))

x = list(sequence)
y = avg_times

plt.plot(x,y,"r.")
plt.title("Average run-time of function against array size",fontweight="bold")
plt.xlabel("Size of input array N",fontweight="bold")
plt.ylabel("Average run time T (s)",fontweight="bold")
plt.show()
