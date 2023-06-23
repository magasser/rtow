#pragma once

#include <filesystem>

#include "../Image.h"

class PPMFileHandler
{
public:
	static void Save(const Image& image, const std::filesystem::path& path);

private:
	static void WriteHeader(std::ofstream& stream, uint32_t width, uint32_t height);
	static void WritePixel(std::ofstream& stream, uint32_t pixel);
};
