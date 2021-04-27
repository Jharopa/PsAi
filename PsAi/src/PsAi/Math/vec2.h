#pragma once

#include <string>
#include <iostream>

namespace PsAi  
{
	namespace Math
	{

		class vec2
		{
			public:
				float x, y;

				// Constructors
				vec2();
				vec2(float scalar);
				vec2(float x, float y);

				// Vector arithmetic
				vec2& add(const vec2& vec);
				vec2& sub(const vec2& vec);
				vec2& mult(const vec2& vec);
				vec2& div(const vec2& vec);

				// Scalar arithmetic
				vec2& add(float& val);
				vec2& sub(float& val);
				vec2& mult(float& val);
				vec2& div(float& val);

				// Special arithmetic
				float mag() const;
				float dist(vec2& vec) const;
				vec2 norm() const;
				float dot(vec2& vec) const;
				
				std::string to_string() const;

				// Vector operators
				friend vec2 operator+(vec2 l, const vec2& r);
				friend vec2 operator-(vec2 l, const vec2& r);
				friend vec2 operator*(vec2 l, const vec2& r);
				friend vec2 operator/(vec2 l, const vec2& r);

				// Scalar operators


				friend std::ostream& operator<<(std::ostream& stream, const vec2& vec);
		};

	}

}
