#pragma once
#ifndef _PHOTOXEL_IMAGE_H_
#define _PHOTOXEL_IMAGE_H_

namespace Photoxel
{
	enum class ImageFormat
	{
		Unknown,
		//RGB,
		RGBA
	};

	class Image
	{
	public:
		Image(const std::string& filepath);
		Image(uint32_t width, uint32_t height, const void* data);
		Image(const Image& other) = default;
		Image(Image&& other) noexcept = default;
		~Image();

		void PutPixel(uint32_t x, uint32_t y, uint32_t color);
		void PutPixel(uint32_t x, uint32_t y, int r, int g, int b, int a);
		bool SaveImage(const std::string& filepath);

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		ImageFormat GetImageFormat() const;

		uint32_t GetPitch() const;

		uint8_t* GetData() const;

	private:
		uint32_t m_Width, m_Height;
		ImageFormat m_ImageFormat;
		uint8_t* m_Data;
	};
}

#endif
