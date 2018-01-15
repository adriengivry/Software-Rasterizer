#include "Image.h"

Image::Image(std::string p_path)
{
    SDL_Surface * image = IMG_Load(p_path.c_str());
    SDL_Surface * rgbaImage = SDL_ConvertSurfaceFormat(image, SDL_PIXELFORMAT_RGBA32, 0);

    m_imagePitch = rgbaImage->pitch;
    m_imageHeight = rgbaImage->h;
    m_imageWidth = rgbaImage->w;

    m_pColortable = new Color[m_imageHeight * m_imageWidth];
    SDL_LockSurface(rgbaImage);
    for(int y = 0; y < m_imageHeight ; ++y)
    {
        for(int x = 0; x < m_imageWidth; ++x)
        {
            uint32_t pixel = GetPixel(rgbaImage, x, y);
            uint32_t index = 0;
            uint8_t red, green, blue;
            SDL_PixelFormat * format = rgbaImage->format;

            index = pixel & format->Rmask;
            index = index >> format->Rshift;
            index = index << format->Rloss;
            red = static_cast<uint8_t>(index);

            index = pixel & format->Gmask;
            index = index >> format->Gshift;
            index = index << format->Gloss;
            green = static_cast<uint8_t>(index);

            index = pixel & format->Bmask;
            index = index >> format->Bshift;
            index = index << format->Gloss;
            blue = static_cast<uint8_t>(index);

            m_pColortable[x + y * m_imageWidth].r = red;
            m_pColortable[x + y * m_imageWidth].g = green;
            m_pColortable[x + y * m_imageWidth].b = blue;
        }
    }
    SDL_FreeSurface(rgbaImage);
}

Image::~Image() { delete m_pColortable; }

uint32_t Image::GetPixel(SDL_Surface* p_src, int p_x, int p_y)
{
    uint32_t * pixels = static_cast<uint32_t *>(p_src->pixels);
    return pixels[p_x + p_y * p_src->pitch / sizeof(unsigned int)];
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
