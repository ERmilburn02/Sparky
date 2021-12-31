#pragma once

#include "graphics/buffers/buffers.h"
#include "maths/maths.h"

namespace sparky { namespace graphics {

	class Renderable2D
	{
		maths::vec3 m_Position;
		maths::vec2 m_Size;
		maths::vec4 m_Color;

		Buffer m_VertexBuffer;
	};

} }