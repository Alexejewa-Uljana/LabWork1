//Алексеева Ульяна st129990@student.spbu.ru

#include <iostream>
#include <fstream>
#include <vector>
#include "Image.h"
#include "TurnImage.h"
#include "Kernel.h"

Color::Color()
    : r(0), g(0), b(0)
{
}

Color::Color(float r, float g, float b)
    : r(r), g(g), b(b)
{
}

Color::~Color()
{
}

Image::Image(int width, int height)
    : m_width(width), m_height(height), m_colors(std::vector<Color>(width * height))
{
}

Image::~Image()
{
}

int Image::GetWidth()
{
    return m_width;
}

int Image::GetHeight()
{
    return m_height;
}

Color Image::GetColor(int x, int y) const
{
    return m_colors[y * m_width + x];
}

void Image::SetColor(const Color& color, int x, int y)
{
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

void Image::Read(const char* path)
{
    std::ifstream file(path, std::ios::binary);
    if (!file)
    {
        std::cerr << "File could not be opened." << std::endl;
        return;
    }
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    if (fileHeader.bfType != 0x4D42)
    {
        std::cerr << "The specified path is not a bitmap image." << std::endl;
        return;
    }
    m_width = infoHeader.biWidth;
    m_height = abs(infoHeader.biHeight);
    m_colors.resize(m_width * m_height);
    const int paddingAmount = (4 - (m_width * 3) % 4) % 4;
    file.seekg(fileHeader.bfOffBits, std::ios::beg);
    const bool isFlipped = infoHeader.biHeight > 0;
    for (int y = 0; y < m_height; ++y)
    {
        int row = isFlipped ? (m_height - 1 - y) : y;
        for (int x = 0; x < m_width; ++x)
        {
            unsigned char color[3];
            file.read(reinterpret_cast<char*>(color), 3);
            m_colors[row * m_width + x] = Color(
                                              color[2] / 255.0f,
                                              color[1] / 255.0f,
                                              color[0] / 255.0f
                                          );
        }
        file.ignore(paddingAmount);
    }
}

void Image::Export(const char* path) const
{
    std::ofstream file(path, std::ios::binary);
    if (!file)
    {
        std::cerr << "File could not be opened." << std::endl;
        return;
    }
    BITMAPFILEHEADER fileHeader = {};
    BITMAPINFOHEADER infoHeader = {};
    const int paddingAmount = (4 - (m_width * 3) % 4) % 4;
    const int dataSize = (m_width * 3 + paddingAmount) * m_height;
    fileHeader.bfType = 0x4D42;
    fileHeader.bfSize = sizeof(fileHeader) + sizeof(infoHeader) + dataSize;
    fileHeader.bfOffBits = sizeof(fileHeader) + sizeof(infoHeader);
    infoHeader.biSize = sizeof(infoHeader);
    infoHeader.biWidth = m_width;
    infoHeader.biHeight = -m_height;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 24;
    infoHeader.biSizeImage = dataSize;
    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    unsigned char padding[3] = {0, 0, 0};
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            const Color& c = GetColor(x, y);
            unsigned char color[3] =
            {
                static_cast<unsigned char>(c.b * 255),
                static_cast<unsigned char>(c.g * 255),
                static_cast<unsigned char>(c.r * 255)
            };
            file.write(reinterpret_cast<const char*>(color), 3);
        }
        file.write(reinterpret_cast<const char*>(padding), paddingAmount);
    }
}

void Image::GaussianBlur(int radius, float sigma)
{
    std::vector<std::vector<float>> kernel = Gauss_Kernel::GenerateGaussianKernel(radius, sigma);
    int kernelSize = 2 * radius + 1;
    Image blurredImage(m_width, m_height);
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            Color newColor;
            float totalWeight = 0.0f;
            for (int ky = -radius; ky <= radius; ++ky) {
                for (int kx = -radius; kx <= radius; ++kx) {
                    int pixelX = x + kx;
                    int pixelY = y + ky;
                    if (pixelX < 0) pixelX = 0;
                    if (pixelX >= m_width) pixelX = m_width - 1;
                    if (pixelY < 0) pixelY = 0;
                    if (pixelY >= m_height) pixelY = m_height - 1;
                    Color currentColor = GetColor(pixelX, pixelY);
                    newColor.r += currentColor.r * kernel[ky + radius][kx + radius];
                    newColor.g += currentColor.g * kernel[ky + radius][kx + radius];
                    newColor.b += currentColor.b * kernel[ky + radius][kx + radius];
                    totalWeight += kernel[ky + radius][kx + radius];
                }
            }
            newColor.r /= totalWeight;
            newColor.g /= totalWeight;
            newColor.b /= totalWeight;
            blurredImage.SetColor(newColor, x, y);
        }
    }
    m_colors = std::move(blurredImage.m_colors);
}
