#include <iostream>
#include "GLFW/glfw3.h"
#include "window.h"

int main()
{
	Core::Window& window = Core::Window::getInstance();

	while (!glfwWindowShouldClose(window.getGLFWwindow()))
	{
		glfwPollEvents();
		glfwSwapBuffers(window.getGLFWwindow());
	}
	return 0;
}