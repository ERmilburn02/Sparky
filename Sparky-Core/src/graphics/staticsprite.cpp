#include "graphics/staticsprite.h"

namespace sparky { namespace graphics {

	StaticSprite::StaticSprite(float x, float y, float w, float h, const maths::vec4& color, Shader& shader)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(w, h), color), m_Shader(shader)
	{
		m_VertexArray = new VertexArray();

		GLfloat vertices[] =
		{
			0, 0, 0,
			0, h, 0,
			w, h, 0,
			w, 0, 0,
		};

		GLfloat colors[] =
		{
			color.x, color.y, color.z, color.h,
			color.x, color.y, color.z, color.h,
			color.x, color.y, color.z, color.h,
			color.x, color.y, color.z, color.h,
		};

		m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
		m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
		m_IndexBuffer = new IndexBuffer(indices, 6);
	}

	StaticSprite::~StaticSprite()
	{
		delete m_VertexArray;
		delete m_IndexBuffer;
	}

} }