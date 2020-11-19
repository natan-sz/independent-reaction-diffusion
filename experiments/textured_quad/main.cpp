#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

int main( void )
{
    GLFWwindow *window;
    
    // Initialize the library
    if ( !glfwInit( ) )
    {
        return -1;
    }
    
    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Reaction Diffusion", NULL, NULL );
    
    if ( !window )
    {
        glfwTerminate( );
        return -1;
    }
    
    // Make the window's context current
    glfwMakeContextCurrent( window );
    
    float vertices[] =
    {
        3*SCREEN_WIDTH/4.0, 3*SCREEN_HEIGHT/4.0, 0.0, // top right corner
        SCREEN_WIDTH/4.0, 3*SCREEN_HEIGHT/4.0, 0.0, // top left corner
        SCREEN_WIDTH/4.0, SCREEN_WIDTH/4.0, 0.0, // bottom left corner
        3*SCREEN_WIDTH/4.0, SCREEN_WIDTH/4.0, 0.0 // bottom right corner
    };
    
	float texCoords[] = {
		0.0f, 0.0f,  // lower-left corner  
		1.0f, 0.0f,  // lower-right corner
		0.5f, 1.0f   // top-center corner
	};

    glViewport( 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1 ); // essentially set coordinate system
    glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity( ); // same as above comment
    
	// Set wrapping method of texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	// Set colour outside border
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  

	// Set texture filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Assign one texture with id and specify it is 2D
	unsigned int texture;
	glGenTextures(1, &texture);  
	glBindTexture(GL_TEXTURE_2D, texture);  

	int width, height;

	width = 10;
	height = 10;

	float data[100] = {0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9,0.1,0.9};
	
	// Check if data is present, if so, load in texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, data);
	std::cout << "Here" << std::endl;
	
    // Loop until the user closes the window
    while ( !glfwWindowShouldClose( window ) )
    {
        glClear( GL_COLOR_BUFFER_BIT );
        
        // Render OpenGL here
        glEnableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're using a vertex array for fixed-function attribute
        glVertexPointer( 3, GL_FLOAT, 0, vertices ); // point to the vertices to be used
        glDrawArrays( GL_QUADS, 0, 4 ); // draw the vertixes
        glDisableClientState( GL_VERTEX_ARRAY ); // tell OpenGL that you're finished using the vertex arrayattribute
        
        
        // Swap front and back buffers
        glfwSwapBuffers( window );
        
        // Poll for and process events
        glfwPollEvents( );
    }
    
    glfwTerminate( );
    
    return 0;
}
