#include "graphics/sprite.h"

namespace sparky { namespace graphics {

	Sprite::Sprite(float x, float y, float w, float h, const maths::vec4& color)
		: Renderable2D(maths::vec3(x, y, 0), maths::vec2(w, h), color)
	{

	}

} }