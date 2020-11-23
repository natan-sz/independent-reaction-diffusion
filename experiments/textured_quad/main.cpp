//Change Opengl libraries to static
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main( void )
{
    GLFWwindow *window;
	glfwSetErrorCallback(error_callback);
    
    // Initialize the library
    if ( !glfwInit( ) )
    {
		exit(EXIT_FAILURE);
    }
    
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Reaction Diffusion", NULL, NULL );

    if ( !window )
    {
        glfwTerminate( );
        exit(EXIT_FAILURE);
    }
    
    // Make the window's context current
    glfwMakeContextCurrent( window );
	glfwSetKeyCallback(window, key_callback);
    
	if (glewInit() != GLEW_OK){
		std::cout << "GLEW ERROR" << std::endl;
	}
    float vertices[8] =
    {
        0.25f, 0.75f, // top right corner
        0.25f, 0.75f, // top left corner
        0.25f, 0.25f, // bottom left corner
        0.75f, 0.25f // bottom right corner
    };

	/*
	// Setting up the Window and projection
    glViewport( 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1 ); // essentially set coordinate system
    glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world

    glLoadIdentity( ); // same as above comment
	*/

	unsigned int buffer;
	glGenBuffers(1,&buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, sizeof(float) * 2, 0);

	// Texture related
	/*
	// GLuint texture;
	// Creates OpenGL texture object
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Sets texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// Sets texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_FLOAT, 1, 1, 0, GL_FLOAT, GL_UNSIGNED_BYTE, nullptr);   
    // Loop until the user closes the window
	*/

    while ( !glfwWindowShouldClose( window ) )
    {
        glClear( GL_COLOR_BUFFER_BIT );
        // Render OpenGL here
		glBegin(GL_POLYGON);
		glVertex3f(2.0, 4.0, 0.0);
		glVertex3f(8.0, 4.0, 0.0);
		glVertex3f(8.0, 6.0, 0.0);
		glVertex3f(2.0, 6.0, 0.0);
		glEnd();
		glFlush();
        // Swap front and back buffers
        glfwSwapBuffers( window );
        
        // Poll for and process events
        glfwPollEvents( );
    }
    

	glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_FAILURE);
}
