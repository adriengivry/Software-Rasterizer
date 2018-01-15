#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Color.h"

class Image
{
public:
    Image(std::string p_path);
    ~Image();
    uint32_t GetPixel(SDL_Surface* p_src, int p_x, int p_y);

    Color* GetColorTable();
    int GetImagePitch();
    int GetImageWidth();
    int GetImageHeight();

private:
    Color* m_pColortable;
    int m_imagePitch;
    int m_imageWidth;
    int m_imageHeight;

};
