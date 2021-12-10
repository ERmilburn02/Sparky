#include "graphics/window.h"
#include <iostream>

namespace sparky { namespace graphics {

	void windowResize(GLFWwindow* window, int width, int height);

	Window::Window(const char* title, int width, int height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
		if (!init())
		{
			glfwTerminate();
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	bool Window::init()
	{
		if (glfwInit() != GLFW_TRUE)
		{
			std::cout << "[ERROR] Failed to initalize GLFW!" << std::endl;
			return false;
		}

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			glfwTerminate();
			std::cout << "[ERROR] Failed to create GLFW window!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "[ERROR] Failed to initalize GLEW!" << std::endl;
		}

		glfwSwapInterval(1);

		glfwSetWindowSizeCallback(m_Window, windowResize);

		return true;
	}

	void Window::clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Window::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void windowResize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

} }