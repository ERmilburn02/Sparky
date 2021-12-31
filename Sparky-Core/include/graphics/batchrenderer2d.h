#pragma once

#include "renderer2d.h"
#include "buffers/buffers.h"

namespace sparky { namespace graphics {

#define RENDERER_MAX_SPRITES	10000
#define RENDERER_VERTEX_SIZE 
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

	class BatchRenderer2D : public Renderer2D
	{
	private:
		VertexArray m_VAO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount;
		GLuint m_VBO;
	public:
		void submit(const Renderable2D* renderable) override;
		void flush() override;
	};

} }