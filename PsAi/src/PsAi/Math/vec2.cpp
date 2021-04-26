#include "vec2.h"

#include <cmath>
#include <sstream>

namespace PsAi
{

	namespace Math
	{
	
		vec2::vec2() : x(0.0f), y(0.0f) {}

		vec2::vec2(float scalar) : x(scalar), y(scalar) {}

		vec2::vec2(float x, float y) : x(x), y(y) {}

		vec2& vec2::add(vec2& v2)
		{
			x += v2.x;
			y += v2.y;

			return *this;
		}

		vec2& vec2::sub(vec2& v2)
		{
			x -= v2.x;
			x -= v2.y;

			return *this;
		}

		vec2& vec2::mult(vec2& v2)
		{
			x *= v2.x;
			x *= v2.y;

			return *this;
		}

		vec2& vec2::div(vec2& v2)
		{
			x /= v2.x;
			x /= v2.y;

			return *this;
		}

		vec2 vec2::add(float& val)
		{
			x += val;
			y += val;

			return *this;
		}

		vec2 vec2::sub(float& val)
		{
			x -= val;
			y -= val;

			return *this;
		}

		vec2 vec2::mult(float& val)
		{
			x *= val;
			y *= val;

			return *this;
		}

		vec2 vec2::div(float& val)
		{
			x /= val;
			y /= val;

			return *this;
		}

		float vec2::mag() const
		{
			return sqrt(x * x + y * y);
		}

		float vec2::dist(vec2& v2) const
		{
			float a = x - v2.x;
			float b = y - v2.y;

			return sqrt(a * a + b * b);
		}

		vec2 vec2::norm() const
		{
			float mag = vec2::mag();
			return vec2(x / mag, y / mag);
		}

		float vec2::dot(vec2& v2) const
		{
			return x * v2.x + y * v2.y;
		}

		std::string vec2::to_string() const
		{
			std::stringstream str;
			str << "vec2(" << x << ", " << y << ")";
			return str.str();
		}
	
	}

}
