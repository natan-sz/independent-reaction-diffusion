# independent-reaction-diffusion

This is the repository for my reaction diffusion simulation code in C++.

The purpose of this project is to compare the performance increase of transferring the existing code to C++ visualised using openGL. The comparison will be made using the same parameters and same starting conditions for the same amount of iterations. I will also compare the different 2D convolution methods used in order to make the code even more efficient. Lastly, I will explore different methods of assigning multi-dimensional arrays in order to drive down the Big-O notation of the code with respect to array size. 

Once this comparison is made, as an extension I will attempt to add a graphical user interface to the program so the user can interact and change the parameters real-time. I am going to be using the GLFW OpenGL library which will let me control user input and manage windows.

As it stands, the code has the general structure needed to work as a CLI application with the exception of the Gray-Scott equation function which should be an easy next step. 

I tried to keep away from using external libraries for the mathematical aspect of the program as I wish to have full control over the method that is being used. As it is, the 2D convolution function i created consists of 4 nested "for" loop which is extremely inefficient however it lays the groundwork for the rest of the program. Next, I plan on using the convolution theorem to turn this into 2 nested "for" loops increasing the speed greatly.

Another way in which i plan on making the code run faster, is computing and displaying the 2D matrices treating them as simple 1D matrices. This should technically give us an O(n) which means the time taken to complete the simulation would scale linearly with the size of the display matrix. 

# Compatibility

I am initially designing this code to work on Linux however when implementing the OpenGL library, I will ideally create builds for linux, mac and windows however as it stands I do not have a MacOS environment to test this on. I will be using cmake in order to build the program on linux and Visual Studio Code to do it on Windows. For linux I will be making a bash script that will install and build the program for the user meaning they wouldnt need to pick any options themselves.

# IDE

For this project I am mainly using VIM as my primary text editor with the g++ compiler. As the project expands I may move to visual studio code due to easier linking of c++ files. 


# Animation So Far

This is a gif of the current code working. Given an initial starting point of a block of values 1 in a 20x20 matrix the convolution function is applied to the matrix. Animation was slowed down to a 1 second gap in between iterations as it was too fast to see what was happening. 

![Alt Text](https://i.imgur.com/JDApozr.gif)
