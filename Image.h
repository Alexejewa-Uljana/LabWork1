#pragma once

#include <vector>
#include "Kernel.h"


struct Color {
    float r, g, b;
    Color();
    Color(float r, float g, float b);
    ~Color();
};

class Image {
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
