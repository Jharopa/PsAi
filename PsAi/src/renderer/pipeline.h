#pragma once

// PsAi includes
#include "device.h"

// STD library includes
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace PsAi::Renderer
{
	
	class Pipeline
	{
	public:
		// Public member functions
		Pipeline(Device& device, const std::string& vertPath, const std::string& fragPath);

	private:
		// Private member variables
		Device& m_device;

		// Private member functions
		static std::vector<char> read_binary(const std::string& filePath);

		void create_graphics_pipeline(const std::string& vertPath, const std::string& fragPath);
	};

} // PsAi::Renderer namespace
