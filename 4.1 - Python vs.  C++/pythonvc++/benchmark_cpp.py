import os
import time
import numpy as np
import matplotlib.pyplot as plt

# Parameters for testing purposes
n_average = 10

# arrays to hold the size of array and the average time for the corresponding array
sequence = range(1,200)
avg_times = []

for N in sequence:
    #Function to run the function n_average times and take an average
    total_time = 0
    print(N)
    for i in range(n_average):
        start = time.time()
        os.system("./run_brute " + str(N)) # Command to test
        end = time.time()

        total_time += (end-start)

    avg_times.append((total_time/float(n_average)))

x = list(sequence)
y = avg_times

coeffs = np.polyfit(x,y,4)
a = coeffs[0]
b = coeffs[1]
c = coeffs[2]
d = coeffs[3]
e = coeffs[4]

x2 = np.arange(min(x)-1, max(x)+1, .01)
y2 = np.polyval(coeffs, x2)

eq = "y= " + str("{:.2e}".format(a)) + "$x^4$ + " + str("{:.2e}".format(b)) + "$x^3$ + " + str("{:.2e}".format(c)) + "$x^2$ + " + str("{:.2e}".format(d)) + "$x$ + " + str("{:.2e}".format(e))

plt.plot(x,y,"k.")
plt.plot(x2,y2,"r-")
plt.text(0,0.1,eq,fontsize=8)
plt.title("Average run-time of C++|Brute Force Implementation",fontweight="bold")
plt.xlabel("Size of input array N",fontweight="bold")
plt.ylabel("Average run time T (s)",fontweight="bold")
plt.show()
