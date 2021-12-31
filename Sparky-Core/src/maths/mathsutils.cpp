#include "maths/mathsutils.h"

namespace sparky { namespace maths {

	float toRadians(float degrees)
	{
		return degrees * ((float)M_PI / 180.0f);
	}

} }