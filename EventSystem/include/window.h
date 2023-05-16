#pragma once
#include <string>
#include <functional>
#include "event.h"
#include "../glfw/include/GLFW/glfw3.h"


namespace Core
{
	class Window final
	{
	private:
		std::string name;
		int width, height;
		GLFWwindow* window = nullptr;
		std::function<void(Event&)> fnCallback;
	private:
		Window(const std::string& name, int width, int height);
	private:
		~Window();
	public:
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
	public:
		static Window& getInstance() { static Window instance("Window", 1200, 720); return instance; }
		void init(const std::string& name, int width, int height);
		__forceinline GLFWwindow* getGLFWwindow() const { return window; }
		void setfnCallback(const std::function<void(Event&)>& fn) { fnCallback = fn; }
	public:
		static void mouseMovedCallback(GLFWwindow* window, double x, double y);
		static void mouseScrollCallback(GLFWwindow* window, double x, double y);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void keyCallback(GLFWwindow*, int key, int scancode, int action, int mods);
		static void windowResizeCallback(GLFWwindow* window, int width, int height);
		static void windowCloseCallback(GLFWwindow* window);
	};
}