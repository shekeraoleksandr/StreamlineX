#include <iostream>
#include "../glfw/include/GLFW/glfw3.h"
#include "../include/window.h"

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