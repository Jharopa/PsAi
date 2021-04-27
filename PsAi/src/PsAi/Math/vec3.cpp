#include "vec3.h"

namespace PsAi
{

	namespace Math
	{
	
		vec3::vec3() : m_x(0.0f), m_y(0.0f), m_z(0.0f) {}

		vec3::vec3(const float scalar) : m_x(scalar), m_y(scalar), m_z(scalar) {}

		vec3::vec3(const float x, const float y, const float z) : m_x(x), m_y(y), m_z(z) {}

	
	}

}

