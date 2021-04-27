#pragma once

#include <string>
#include <iostream>

namespace PsAi
{

	namespace Math
	{

		class vec3
		{
			public:
				// Constructors
				vec3();
				vec3(const float scalar);
				vec3(const float x, const float y, const float z);

				// Getters
				float get_x() const { return m_x; }
				float get_y() const { return m_y; }
				float get_z() const { return m_z; }

				// Setters
				void set_x(const float x) { m_x = x; }
				void set_y(const float y) { m_y = y; }
				void set_z(const float z) { m_z = z; }



			private:
				float m_x, m_y, m_z;
		};

	} // Math namespace

} // PsAi namespace
