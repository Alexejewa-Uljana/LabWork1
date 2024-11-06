//
#include <iostream>
#include <vector>
#include "Image.h"
#include "TurnImage.h"

int main(int argc, char* argv [])
{
    int width = 640;
    int height = 480;
    Image image(width, height);
    for (int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
       {
            image.SetColor(Color((float)x / (float)width, 1.0f - ((float)x / (float)width), (float)y / (float)height), x, y);
       }
    }
    image.Export("image.bmp");
    Image Copy(0, 0);
    Copy.Read("image.bmp");
    Copy.Export("copy.bmp");
    Turn_Image::RightTurn("copy.bmp");
    Turn_Image::LeftTurn("copy.bmp");
    std::cout << image.GetWidth() << std::endl;
}
