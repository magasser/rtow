#include "pch.h"
#include "PPMFileHandler.h"

void PPMFileHandler::Save(const Image& image, const std::filesystem::path& path)
{
	assert(!path.empty());

	std::ofstream stream;

	stream.open(path);

	WriteHeader(stream, image.GetWidth(), image.GetHeight());

	float progress;
	for (uint32_t y = image.GetHeight() - 1; y < image.GetHeight(); --y)
	{
		for (uint32_t x = 0; x < image.GetWidth(); ++x)
		{
			WritePixel(stream, image.GetPixel(x, y));
		}

		progress = 100.0f - y * 100.0f / image.GetHeight();

		std::cout << "Save: " << progress << " %" << std::endl;
	}

	stream.close();
}

inline void PPMFileHandler::WriteHeader(std::ofstream& stream, uint32_t width, uint32_t height)
{
	stream << "P3" << std::endl;
	stream << width << ' ' << height << std::endl;
	stream << "255" << std::endl;
}

inline uint32_t GetR(uint32_t pixel)
{
	return pixel & 0xFF;
}

inline uint32_t GetG(uint32_t pixel)
{
	return (pixel >> 8) & 0xFF;
}

inline uint32_t GetB(uint32_t pixel)
{
	return (pixel >> 16) & 0xFF;
}

inline void PPMFileHandler::WritePixel(std::ofstream& stream, uint32_t pixel)
{
	stream << GetR(pixel) << ' ' << GetG(pixel) << ' ' << GetB(pixel) << std::endl;
}
