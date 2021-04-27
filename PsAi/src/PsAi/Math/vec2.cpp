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

		vec2& vec2::add(const vec2& vec)
		{
			x += vec.x;
			y += vec.y;

			return *this;
		}

		vec2& vec2::sub(const vec2& vec)
		{
			x -= vec.x;
			y -= vec.y;

			return *this;
		}

		vec2& vec2::mult(const vec2& vec)
		{
			x *= vec.x;
			y *= vec.y;

			return *this;
		}

		vec2& vec2::div(const vec2& vec)
		{
			x /= vec.x;
			y /= vec.y;

			return *this;
		}

		vec2& vec2::add(const float& val)
		{
			x += val;
			y += val;

			return *this;
		}

		vec2& vec2::sub(const float& val)
		{
			x -= val;
			y -= val;

			return *this;
		}

		vec2& vec2::mult(const float& val)
		{
			x *= val;
			y *= val;

			return *this;
		}

		vec2& vec2::div(const float& val)
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

		float vec2::dot(vec2& vec) const
		{
			return x * vec.x + y * vec.y;
		}

		std::string vec2::to_string() const
		{
			std::stringstream str;
			str << "vec2(" << x << ", " << y << ")";
			return str.str();
		}
	
		vec2 operator+(vec2 l, const vec2& r)
		{
			return l.add(r);
		}

		vec2 operator-(vec2 l, const vec2& r)
		{
			return l.sub(r);
		}

		vec2 operator*(vec2 l, const vec2& r)
		{
			return l.mult(r);
		}

		vec2 operator/(vec2 l, const vec2& r)
		{
			return l.div(r);
		}

		vec2 operator+(vec2 l, const float& r)
		{
			return l.add(r);
		}

		vec2 operator-(vec2 l, const float& r)
		{
			return l.sub(r);
		}

		vec2 operator*(vec2 l, const float& r)
		{
			return l.mult(r);
		}

		vec2 operator/(vec2 l, const float& r)
		{
			return l.div(r);
		}

		std::ostream& operator<<(std::ostream& stream, const vec2& vec)
		{
			stream << vec.to_string();
			return stream;
		}

}

}
