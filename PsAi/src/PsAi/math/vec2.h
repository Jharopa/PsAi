#pragma once

// STD library imports
#include <string>
#include <iostream>

namespace PsAi  
{
	
	namespace Math
	{

		class vec2
		{
			public:
				// Constructors
				vec2();
				vec2(const float scalar);
				vec2(const float x, const float y);

				// Getters
				float get_x() const { return m_x; }
				float get_y() const { return m_y; }

				// Setters
				void set_x(const float x) { m_x = x; }
				void set_y(const float y) { m_y = y; }

				// Vector arithmetic functions
				vec2& add(const vec2& vec);
				vec2& sub(const vec2& vec);
				vec2& mult(const vec2& vec);
				vec2& div(const vec2& vec);

				// Scalar arithmetic functions
				vec2& add(const float& val);
				vec2& sub(const float& val);
				vec2& mult(const float& val);
				vec2& div(const float& val);

				// Special arithmetic functions
				float mag() const;
				float dist(vec2& vec) const;
				vec2 norm() const;
				float dot(vec2& vec) const;
				
				std::string to_string() const;

				// Vector overloaded arithmetic operators
				friend vec2 operator+(vec2 l, const vec2& r);
				friend vec2 operator-(vec2 l, const vec2& r);
				friend vec2 operator*(vec2 l, const vec2& r);
				friend vec2 operator/(vec2 l, const vec2& r);

				// Scalar overloaded arithmetic operators
				friend vec2 operator+(vec2 l, const float& r);
				friend vec2 operator-(vec2 l, const float& r);
				friend vec2 operator*(vec2 l, const float& r);
				friend vec2 operator/(vec2 l, const float& r);

				// Overloaded relational operators
				bool operator==(const vec2& vec) const;
				bool operator!=(const vec2& vec) const;
				
				// Overloaded output stream operator
				friend std::ostream& operator<<(std::ostream& stream, const vec2& vec);

			private:
				float m_x, m_y;
		};

	}

}
