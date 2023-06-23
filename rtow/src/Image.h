#pragma once

#include <glm/vec3.hpp>

class Image
{
public:
	Image(uint32_t width, uint32_t height);
	~Image();

	inline uint32_t GetWidth() const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }
	inline uint32_t GetPixel(uint32_t x, uint32_t y) const { return m_Pixels[x + y * m_Width]; }

	void SetPixel(uint32_t x, uint32_t y, const glm::vec3& pixel, uint32_t samples);
	void SetPixel(uint32_t x, uint32_t y, uint32_t pixel);

private:
	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t* m_Pixels;
};
