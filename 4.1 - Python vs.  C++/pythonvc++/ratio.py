import numpy as np
import matplotlib.pyplot as plt


cpp_coeffs = [6.08*pow(10,-11), -2.43*pow(10,-8), 4.88*pow(10,-6), -3.43*pow(10,-5), 2.15*pow(10,-2)]
py_coeffs = [8.61*pow(10,-10), -3.09*pow(10,-7), 2.28*pow(10,-4), -1.79*pow(10,-3), 4.98*pow(10,-1)]

x = list(range(1,200))

y_cpp = np.polyval(cpp_coeffs, x)
y_py = np.polyval(py_coeffs, x)

ratio = []

for i in x:
    ratio.append(y_py[i-1]/y_cpp[i-1])

plt.plot(x,ratio)

plt.show()
