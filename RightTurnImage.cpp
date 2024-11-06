//Алексеева Ульяна st129990@student.spbu.ru

#include <iostream>
#include "Image.h"
#include "TurnImage.h"
#include <vector>
#include "Kernel.h"

void Turn_Image::RightTurn(const char* path)
{
    Image image(0, 0);
    image.Read(path);
    int height = image.GetHeight();
    int width = image.GetWidth();
    Image turn_image(height, width);
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            turn_image.SetColor(image.GetColor(x, y), y, width - x - 1);
        }
    }
    std::cout << "Right turn image created" << std::endl;
    turn_image.Export("Right_turn_image.bmp");
}

