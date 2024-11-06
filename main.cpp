//Алексеева Ульяна st129990@student.spbu.ru

#include <iostream>
#include <vector>
#include "Image.h"
#include "TurnImage.h"
#include "Kernel.h"

int main(int argc, char* argv [])
{
    Turn_Image::RightTurn("123.bmp");
    Turn_Image::LeftTurn("123.bmp");
    Image image_left(0, 0);
    image_left.Read("Left_turn_image.bmp");
    image_left.GaussianBlur(10, 10.0f);
    image_left.Export("Blurring_left_turn_image.bmp");
    Image image_right(0, 0);
    image_right.Read("Right_turn_image.bmp");
    image_right.GaussianBlur(10, 10.0f);
    image_right.Export("Blurring_right_turn_image.bmp");
}
