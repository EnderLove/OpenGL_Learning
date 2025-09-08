#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

/*
int main()
{
	glewExperimental = true;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);


	GLFWwindow* window;

	window = glfwCreateWindow(1024, 768, "HangManGame", NULL, NULL);

	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window");
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while ( glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			   glfwWindowShouldClose(window) == 0);
}
*/



