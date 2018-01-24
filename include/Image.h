#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Color.h"

class Image
{
public:
	explicit Image(std::string p_path);
    ~Image();
    uint32_t GetPixel(SDL_Surface* p_src, const int p_x, const int p_y);

    Color* GetColorTable() const;
    int GetImagePitch() const;
    int GetImageWidth() const;
    int GetImageHeight() const;

private:
    Color* m_pColortable;
    int m_imagePitch;
    int m_imageWidth;
    int m_imageHeight;
};