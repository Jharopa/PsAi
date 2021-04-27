#include "vec3.h"

// STD library imports
#include <cmath>
#include <sstream>

namespace PsAi
{

	namespace Math
	{
	
		vec3::vec3() : m_x(0.0f), m_y(0.0f), m_z(0.0f) {}

		vec3::vec3(const float scalar) : m_x(scalar), m_y(scalar), m_z(scalar) {}

		vec3::vec3(const float x, const float y, const float z) : m_x(x), m_y(y), m_z(z) {}

		vec3& vec3::add(const vec3& vec)
		{
			m_x += vec.get_x();
			m_y += vec.get_y();
			m_z += vec.get_z();

			return *this;
		}

		vec3& vec3::sub(const vec3& vec)
		{
			m_x -= vec.get_x();
			m_y -= vec.get_y();
			m_z -= vec.get_z();

			return *this;
		}

		vec3& vec3::mult(const vec3& vec)
		{
			m_x *= vec.get_x();
			m_y *= vec.get_y();
			m_z *= vec.get_z();

			return *this;
		}

		vec3& vec3::div(const vec3& vec)
		{
			m_x /= vec.get_x();
			m_y /= vec.get_y();
			m_z /= vec.get_z();

			return *this;
		}

		vec3& vec3::add(const float& scalar)
		{
			m_x += scalar;
			m_y += scalar;
			m_z += scalar;

			return *this;
		}

		vec3& vec3::sub(const float& scalar)
		{
			m_x -= scalar;
			m_y -= scalar;
			m_z -= scalar;

			return *this;
		}

		vec3& vec3::mult(const float& scalar)
		{
			m_x *= scalar;
			m_y *= scalar;
			m_z *= scalar;

			return *this;
		}

		vec3& vec3::div(const float& scalar)
		{
			m_x /= scalar;
			m_y /= scalar;
			m_z /= scalar;

			return *this;
		}

		float vec3::mag() const
		{
			return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
		}

		float vec3::dist(vec3& vec) const
		{
			float a = m_x - vec.get_x();
			float b = m_y - vec.get_y();
			float c = m_z - vec.get_z();

			return sqrt(a * a + b * b + c * c);
		}

		vec3 vec3::norm() const
		{
			float mag = vec3::mag();

			return vec3(m_x / mag, m_y / mag, m_z / mag);
		}

		float vec3::dot(vec3& vec) const
		{
			return m_x * vec.get_x() + m_y * vec.get_y() + m_z * vec.get_z();
		}

		vec3 vec3::cross(vec3& vec) const
		{
			return vec3(
				m_y * vec.get_z() - m_z * vec.get_y(), 
				m_z * vec.get_x() - m_x * vec.get_z(),
				m_x * vec.get_y() - m_y * vec.get_x()
			);
		}

		std::string vec3::to_string() const
		{
			std::stringstream str;
			str << "vec3(" << m_x << ", " << m_y << ", " << m_z << ")";

			return str.str();
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vec)
		{
			stream << vec.to_string();

			return stream;
		}

}

}

