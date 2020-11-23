#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>



int main () {
	
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};  

	// Assigns VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);  

	// Binds Several buffers together (This creates the buffer)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Copy vertex data into the buffer
	// Use GL_DYNAMIC_DRAW for frequent access/change
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);




	///*		START OF VERTEX SHADER			*///

	// Shader source code in GLSL
	// This creates a 3D vector, at location 0 and puts this in a vec4 which is stored
	// as gl_Position
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// This creates the Shader object
	// This is a "vertex" shader therefore GL_VERTEX_SHADER is chosen
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// This Attaches the ShadeSource to the Shader object and compiles it in the second line
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Sets Parameters for checking if the shader was compiled successfully
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	// If shader not compiled, This happens
	if(!success){
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	///*		END OF VERTEX SHADER			*///



	///*		START OF FRAGMENT SHADER			*///
	const char *fragmentShaderSource = 	"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main ()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f)"
		"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	///*		END OF FRAGMENT SHADER			*///



	///*		START OF SHADER PROGRAM LINKING	*/// 

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		...
	}

	///*		END OF SHADER PROGRAM LINKING	*/// 

	// Use the shader Program created and delete the individual shaders
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);  

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);  

	return 0;
}
