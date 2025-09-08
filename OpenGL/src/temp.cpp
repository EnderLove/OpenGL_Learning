#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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

	GLFWwindow* window = glfwCreateWindow(800, 600, "League of Legends 2", NULL, NULL);

	if (window == NULL) //Verify if the window has been created or not
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate(); //Terminates the GLFW library and eliminates all crap
		return -1;
	}
	glfwMakeContextCurrent(window); //Set the context of the current window
	glViewport(0, 0, 800, 600); //Sets the size of the rendering window
	//The first two parameters set the coordinates of the lower left corner of the window

	//This function is called everytime the window is rezised 
	//The arguments are pointers, especially the second one, thats why you dont pass arguments :D REMEMBER THAT!!!!
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window); //This swap the buffers to avoid flickering issues
		glfwPollEvents();        //Checks for events
	}

	glfwTerminate();//Erease everything
	return 0;
}