#pragma once

#include "../Includes.h"

namespace Utility
{
	class BMPSaver
	{
	public:
		static void Save(std::filesystem::path path, const std::vector<float>& imageData);
	private:
		BMPSaver() = delete;
		BMPSaver(const BMPSaver&) = delete;
		BMPSaver(BMPSaver&&) = delete;
		BMPSaver& operator=(const BMPSaver&) = delete;
		BMPSaver& operator=(BMPSaver&&) = delete;
	};
}
