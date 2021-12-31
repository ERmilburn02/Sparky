#include <GL/glew.h>
#include <iostream>

#include "sparky.h"

int main()
{
	using namespace sparky;
	using namespace graphics;
	using namespace maths;

	Window window("Sparky!", 960, 540);

	std::cout << "[INFO] OpenGL Version " << glGetString(GL_VERSION) << std::endl;

	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("data/shaders/Basic.vert", "data/shaders/Basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
	shader.setUniform2f("light_pos", vec2(4, 1.5));

	Renderable2D sprite(vec3(5, 5, 0), vec2(4, 4), vec4(1, 0, 1, 1), shader);
	Renderable2D spriteB(vec3(7, 1, 0), vec2(2, 3), vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
		renderer.submit(&sprite);
		renderer.submit(&spriteB);
		renderer.flush();

		window.update();
	}
}