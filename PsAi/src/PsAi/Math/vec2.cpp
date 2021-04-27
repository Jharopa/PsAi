#include "vec2.h"

#include <cmath>
#include <sstream>

namespace PsAi
{

	namespace Math
	{
	
		vec2::vec2() : m_x(0.0f), m_y(0.0f) {}

		vec2::vec2(float scalar) : m_x(scalar), m_y(scalar) {}

		vec2::vec2(float x, float y) : m_x(x), m_y(y) {}

		vec2& vec2::add(const vec2& vec)
		{
			m_x += vec.get_x();
			m_y += vec.get_y();

			return *this;
		}

		vec2& vec2::sub(const vec2& vec)
		{
			m_x -= vec.get_x();
			m_y -= vec.get_y();

			return *this;
		}

		vec2& vec2::mult(const vec2& vec)
		{
			m_x *= vec.get_x();
			m_y *= vec.get_y();

			return *this;
		}

		vec2& vec2::div(const vec2& vec)
		{
			m_x /= vec.get_x();
			m_y /= vec.get_y();

			return *this;
		}

		vec2& vec2::add(const float& val)
		{
			m_x += val;
			m_y += val;

			return *this;
		}

		vec2& vec2::sub(const float& val)
		{
			m_x -= val;
			m_y -= val;

			return *this;
		}

		vec2& vec2::mult(const float& val)
		{
			m_x *= val;
			m_y *= val;

			return *this;
		}

		vec2& vec2::div(const float& val)
		{
			m_x /= val;
			m_y /= val;

			return *this;
		}

		float vec2::mag() const
		{
			return sqrt(m_x * m_x + m_y * m_y);
		}

		float vec2::dist(vec2& v2) const
		{
			float a = m_x - v2.get_x();
			float b = m_y - v2.get_y();

			return sqrt(a * a + b * b);
		}

		vec2 vec2::norm() const
		{
			float mag = vec2::mag();
			return vec2(m_x / mag, m_y / mag);
		}

		float vec2::dot(vec2& vec) const
		{
			return m_x * vec.get_x() + m_y * vec.get_y();
		}

		std::string vec2::to_string() const
		{
			std::stringstream str;
			str << "vec2(" << m_x << ", " << m_y << ")";
			return str.str();
		}

		bool vec2::operator==(const vec2& vec) const
		{
			return m_x == vec.get_x() && m_y == vec.get_y();
		}

		bool vec2::operator!=(const vec2& vec) const
		{
			return !(*this == vec);
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
