//Алексеева Ульяна st129990@student.spbu.ru

#pragma once

#include <iostream>
#include <vector>
#include "Kernel.h"

#ifndef IMAGE_H
#define IMAGE_H

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

#endif
