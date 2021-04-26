#pragma once

#include <string>

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
				vec2& add(vec2& v2);
				vec2& sub(vec2& v2);
				vec2& mult(vec2& v2);
				vec2& div(vec2& v2);

				// Scalar arithmetic
				vec2 add(float& val);
				vec2 sub(float& val);
				vec2 mult(float& val);
				vec2 div(float& val);

				float mag() const;
				float dist(vec2& v2) const;
				vec2 norm() const;
				float dot(vec2& v2) const;

				std::string to_string() const;
		};

	}

}
