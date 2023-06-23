#include "pch.h"
#include "Image.h"

Image::Image(uint32_t width, uint32_t height)
	: m_Width(width),
	  m_Height(height),
	  m_Pixels(new uint32_t[width * height]) {}

Image::~Image()
{
	delete[] m_Pixels;
}

void Image::SetPixel(uint32_t x, uint32_t y, const glm::vec3& pixel, uint32_t samples)
{
	uint32_t p = 0;

	float scale = 1.0f / samples;
	
	float r = 256 * glm::clamp(glm::sqrt(pixel.r * scale), 0.0f, 0.999f);
	float g = 256 * glm::clamp(glm::sqrt(pixel.g * scale), 0.0f, 0.999f);
	float b = 256 * glm::clamp(glm::sqrt(pixel.b * scale), 0.0f, 0.999f);

	p |= 0xFF & static_cast<uint32_t>(r);
	p |= 0xFF00 & (static_cast<uint32_t>(g) << 8);
	p |= 0xFF0000 & (static_cast<uint32_t>(b) << 16);

	SetPixel(x, y, p);
}

void Image::SetPixel(uint32_t x, uint32_t y, uint32_t pixel)
{
	assert(x < m_Width);
	assert(y < m_Height);

	uint32_t index = x + m_Width * y;
	m_Pixels[index] = pixel;
}
