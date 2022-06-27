#include "fxpch.h"
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "Core/Core.h"

namespace Photoxel
{
	Image::Image(const std::string& filepath)
	{
		const int desiredChannels = 4;
		int width = 0, height = 0, bpp = 0;
		uint8_t* data = stbi_load(filepath.c_str(), &width, &height, &bpp, desiredChannels);

		m_Width = width;
		m_Height = height;
		m_Data = data;
		m_ImageFormat = ImageFormat::RGBA;

	}

	Image::Image(uint32_t width, uint32_t height, const void* data)
	{
		m_Width = width;
		m_Height = height;
		m_Data = new uint8_t[m_Width * m_Height * 4];
		m_ImageFormat = ImageFormat::RGBA;
	}

	Image::~Image()
	{
		delete[] m_Data;
	}

	void Image::PutPixel(uint32_t x, uint32_t y, uint32_t color)
	{
		// 0xffffffff
		// 00000000 00000000 00000000 00000000
		//     R       G        B        A
		
		m_Data[(x + y * m_Width) * 4 + 0] = (color) & 0x000000ff;
		m_Data[(x + y * m_Width) * 4 + 1] = (color << 8) & 0x000000ff;
		m_Data[(x + y * m_Width) * 4 + 2] = (color << 16) & 0x000000ff;
		m_Data[(x + y * m_Width) * 4 + 3] = (color << 24) & 0x000000ff;

		//PX_DEBUG("{} {} {} {}", x * 4 + y * m_Width, x * 4 + y * m_Width + 1, x * 4 + y * m_Width + 2, x * 4 + y * m_Width + 3);
	}

	void Image::PutPixel(uint32_t x, uint32_t y, int r, int g, int b, int a)
	{
		m_Data[(x + y * m_Width) * 4 + 0] = r;
		m_Data[(x + y * m_Width) * 4 + 1] = g;
		m_Data[(x + y * m_Width) * 4 + 2] = b;
		m_Data[(x + y * m_Width) * 4 + 3] = a;
	}

	bool Image::SaveImage(const std::string& filepath)
	{
		stbi_write_jpg(filepath.c_str(), m_Width, m_Height, 4, m_Data, 256);
		return true;
	}

	uint32_t Image::GetWidth() const
	{
		return m_Width;
	}

	uint32_t Image::GetHeight() const
	{
		return m_Height;
	}

	ImageFormat Image::GetImageFormat() const
	{
		return m_ImageFormat;
	}

	uint32_t Image::GetPitch() const
	{
		return m_Width * 4;
	}

	uint8_t* Image::GetData() const
	{
		return m_Data;
	}
}