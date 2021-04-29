// PsAi imports
#include "pipeline.h"

// STD library imports
#include <string>
#include <vector>

#include <fstream>
#include <iostream>

namespace PsAi
{
	
	namespace Renderer
	{
	
		Pipeline::Pipeline(Device& device, const std::string& vertPath, const std::string& fragPath)
			: m_device(device)
		{
			create_graphics_pipeline(vertPath, fragPath);
		}

		std::vector<char> Pipeline::read_binary(const std::string& filePath)
		{
			std::ifstream file(filePath, std::ios::ate | std::ios::binary);

			if (!file.is_open())
			{
				throw std::runtime_error("Failed to open file: " + filePath);
			}

			size_t fileSize = (size_t)file.tellg();
			std::vector<char> buffer(fileSize);

			file.seekg(0);
			file.read(buffer.data(), fileSize);

			file.close();

			return buffer;
		}

		void Pipeline::create_graphics_pipeline(const std::string& vertPath, const std::string& fragPath)
		{
			auto vertCode = read_binary(vertPath);
			auto fragCode = read_binary(fragPath);

			std::cout << "Vertex shader code size: " << vertCode.size() << std::endl;
			std::cout << "Fragment shader code size: " << fragCode.size() << std::endl;
		}

	} // Renderer namespace

} // PsAi namespace
