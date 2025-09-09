#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//SETTINGS
const unsigned int SCR_WIDTH  = 800;
const unsigned int SCR_HEIGHT = 600;

//Compiled at run-time
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4 (aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

void processInput(GLFWwindow* window) //Gets the window
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true); //If the key has been pressed the window close state change to true
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	
	//Just to check if the function is being called
	std::cout << "width: " << width << " || heigth: " << height << std::endl;
}

int main()
{
	glfwInit(); //This function initialize the glfw library

	//"glfwWindowHint" let us configurate the glfw options
	//In the first argument we specify which option we want to configure

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Sets the OpenGl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Sets the OpenGl version
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Access to core profile

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "League of Legends 2", NULL, NULL);

	if (window == NULL) //Verify if the window has been created or not
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate(); //Terminates the GLFW library and eliminates all crap
		return -1;
	}
	glfwMakeContextCurrent(window); //Set the context of the current window

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	
	//This function is called everytime the window is rezised 
	//The arguments are pointers, especially the second one, thats why you dont pass arguments :D REMEMBER THAT!!!!
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//==================================================================
	//====================== VERTEX SHADER CREATION ====================
	//==================================================================

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //Creates a Shader

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Takes as input the shader and the source code
	//The second argument specifies how many strings we are passing
	glCompileShader(vertexShader); //Compiles the shader

	//================== COMPILATION SHADER CHECK ERROR ================

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//==================================================================
	//===================== FRAGMENT SHADER CREATION ===================
	//==================================================================

	unsigned int fragmentShader;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Create shader type Fragment
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//==================================================================
	//====================== SHADER PROGRAM CREATION ===================
	//==================================================================

	//The shader program links all the shaders to render objects
	//Links all the inputs and outputs of the OpenGL graphics pipeline

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram(); //Creates the program shader and returns the ID

	//Now we attach the proviously compiled shaders to the program object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram); //Links the whole program

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK::LINKING FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//We delete the shader objects because there are now linked to the program object

	//So far we sent the input vertex data to the GPU and instructed the GPU how it should 
	//process the vertex data within a vertex and fragemnt shader.

	/*
		float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	*/



	float vertices[] = {
		 0.5,  0.5, 0.0,
	   	 0.5, -0.5, 0.0,
		-0.5, -0.5, 0.0,
		-0.5,  0.5, 0.0
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};


	//==================================================================
	//================== VERTEX DATA STORED IN MEMORY ==================
	//==================================================================
	//==================================================================
	//===================== LINKING VERTEX ATTRIBUTES ==================
	//==================================================================
	//==================================================================
	//===================== VERTEX ARRAY OBJECT (VAO) ==================
	//==================================================================

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO); 
	glGenBuffers(1, &VBO); //This function generates a buffer with an ID
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO); //Always bind the Vertex Array Object first

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //We bind our buffer to an array type one
	//Now we can configure the buffer 

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//The fourth parameter specifies how we want the graphics card to manage the given data
	//GL_STREAM_DRAW, GL_STATIC_DRAW, GL_DYNAMIC_DRAW

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//The first  argument takes the location of the vertex attribute
	//The second argument gives the dimension
	//The third  argument specifies the data type (always float)
	//The fourth argument tell if we want to Normalize the coordinates if we did not 
	//the fifth  argument stablish the stride 
	//The sixth  argument will be studied later haha! 

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) //RENDER LOOP (FRAMES)
	{
		processInput(window); //Checks for esc

		glClearColor(0.1f, 0.1f, 0.3f, 1.0f); //This sets the color of the screen
		glClear(GL_COLOR_BUFFER_BIT);         //This clear the previus frame so you dont watch it

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		glfwSwapBuffers(window); //This swap the buffers to avoid flickering issues
		glfwPollEvents();        //Checks for events
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();//Erease everything
	return 0;
}