#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace sparky { namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

	class Window
	{
	private:
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;
		bool m_Closed;

		bool m_Keys[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		double mx, my;
	public:
		Window(const char* title, int width, int height);
		~Window();

		void clear() const;
		bool closed() const;
		void update();

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }

		bool isKeyPressed(unsigned int keycode) const;
		bool isMouseButtonPressed(unsigned int button) const;
		void getMousePosition(double& x, double& y) const;
	private:
		bool init();
		friend static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	};

} }