//Алексеева Ульяна st129990@student.spbu.ru

#pragma once

#include <iostream>
#include <vector>
#include "Kernel.h"

#ifndef IMAGE_H
#define IMAGE_H

struct Color
{
    float r, g, b;
    Color();
    Color(float r, float g, float b);
    ~Color();
};

#pragma pack(push, 1)
struct BITMAPFILEHEADER
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BITMAPINFOHEADER
{
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)


class Image
{
public:
    Image(int width, int height);
    ~Image();
    int GetWidth();
    int GetHeight();
    Color GetColor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);
    void Read(const char* path);
    void Export(const char* path) const;
    void GaussianBlur(int raduis, float sigma);
private:
    int m_width;
    int m_height;
    std::vector<Color> m_colors;
};

#endif
