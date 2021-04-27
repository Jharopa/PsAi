#pragma once

// STD library imports
#include <string>
#include <vector>

namespace PsAi
{
	
	namespace Renderer
	{
	
		class Pipeline
		{
		public:
			// Public member functions
			Pipeline(const std::string& vertPath, const std::string& fragPath);

		private:
			// Private member functions
			static std::vector<char> read_binary(const std::string& filePath);

			void create_graphics_pipeline(const std::string& vertPath, const std::string& fragPath);
		};
	
	}

} // PsAi namespace
