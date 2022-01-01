#include <GL/glew.h>
#include <iostream>
#include <time.h>

#include "sparky.h"

#define USE_BATCH_RENDERER 1
#define USE_10K 1

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
	// shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));
	shader.setUniform2f("light_pos", vec2(4, 1.5));

	std::vector<Renderable2D*> sprites;

	srand(time(NULL));

	for (float y = 0; y < 9.0f; y += 
#if USE_10K
		0.1f
#else
		1.0f
#endif
		)
	{
		for (float x = 0; x < 16.0f; x += 
#if USE_10K
			0.1f
#else
			1.0f
#endif
			)
		{
			sprites.push_back(new
#if USE_BATCH_RENDERER
				Sprite
#else
				StaticSprite
#endif
				(x, y, 
#if USE_10K
					0.08f
#else
					0.8f
#endif
					,
#if USE_10K
					0.08f
#else
					0.8f
#endif
					, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)
#if !USE_BATCH_RENDERER
					, shader
#endif
					));
		}
	}

#if USE_BATCH_RENDERER
	Sprite sprite(5, 5, 4, 4, vec4(1, 0, 1, 1));
	Sprite spriteB(7, 1, 2, 3, vec4(0.2f, 0, 1, 1));
	BatchRenderer2D renderer;

#else
	StaticSprite sprite(5, 5, 4, 4, vec4(1, 0, 1, 1), shader);
	StaticSprite spriteB(7, 1, 2, 3, vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;
#endif

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
#if USE_BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
		// renderer.submit(&sprite);
		// renderer.submit(&spriteB);
#if USE_BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();

		window.update();
	}
}