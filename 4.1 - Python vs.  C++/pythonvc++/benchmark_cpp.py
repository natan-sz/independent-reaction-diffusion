import os
import time
import numpy as np
import matplotlib.pyplot as plt

# Parameters for testing purposes
n_average = 5

# arrays to hold the size of array and the average time for the corresponding array
sequence = range(1,200)
avg_times = []

for N in sequence:
    #Function to run the function n_average times and take an average
    total_time = 0
    print(N)
    for i in range(n_average):
        start = time.time()
        os.system("./run_brute" + str(N)) # Command to test
        end = time.time()

        total_time += (end-start)

    avg_times.append((total_time/float(n_average)))

x = list(sequence)
y = avg_times

a, b, c = np.polyfit()
coeffs = [a,b,c]

x2 = np.arange(min(x)-1, max(x)+1, .01)
y2 = np.polyval(coeffs, x2)


plt.plot(x,y,"k.")
plt.plot(x,y,"r-")
plt.title("Average run-time of function against array size",fontweight="bold")
plt.xlabel("Size of input array N",fontweight="bold")
plt.ylabel("Average run time T (s)",fontweight="bold")
plt.show()
