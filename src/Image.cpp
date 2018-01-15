#include "Image.h"

Image::Image(std::string p_path)
{
    SDL_Surface * image = IMG_Load(p_path.c_str());
    SDL_Surface * rgbaImage = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA32, 0);

    m_imagePitch = rgbaImage->pitch;
    m_imageHeight = rgbaImage->h;
    m_imageWidth = rgbaImage->w;

    m_pColortable = new Color[m_imageHeight * m_imagePitch];
    SDL_LockSurface(rgbaImage);
    for(int y = 0; y < m_imageHeight ; ++y)
    {
        for(int x = 0; x < m_imagePitch; ++x)
        {
            uint32_t pixel = GetPixel(rgbaImage, x, y);
            uint32_t index = 0;
            uint8_t red, green, blue;

            index = pixel & rgbaImage->format->Rmask;
            index = index >> rgbaImage->format->Rshift;
            index = index << rgbaImage->format->Rloss;
            red = static_cast<uint8_t>(index);

            index = pixel & rgbaImage->format->Gmask;
            index = index >> rgbaImage->format->Gshift;
            index = index << rgbaImage->format->Gloss;
            green = static_cast<uint8_t>(index);

            index = pixel & rgbaImage->format->Bmask;
            index = index >> rgbaImage->format->Bshift;
            index = index << rgbaImage->format->Gloss;
            blue = static_cast<uint8_t>(index);

            m_pColortable[x + y * m_imagePitch/4].r = red;
            m_pColortable[x + y * m_imagePitch/4].g = green;
            m_pColortable[x + y * m_imagePitch/4].b = blue;
        }
    }
    SDL_UnlockSurface(rgbaImage);
    SDL_FreeSurface(rgbaImage);
    SDL_FreeSurface(image);
}

Image::~Image() { delete m_pColortable; }

uint32_t Image::GetPixel(SDL_Surface* p_src, int p_x, int p_y)
{
    return static_cast<uint32_t *>(p_src->pixels)[p_x + p_y * p_src->pitch/ sizeof(unsigned int)];
}

Color* Image::GetColorTable()
{
    return m_pColortable;
}

int Image::GetImagePitch()
{
    return m_imagePitch;
}

int Image::GetImageWidth()
{
    return m_imageWidth;
}

int Image::GetImageHeight()
{
    return m_imageHeight;
}
