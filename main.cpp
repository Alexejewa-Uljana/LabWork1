//Алексеева Ульяна st129990@student.spbu.ru

#include <iostream>
#include <vector>
#include <string>
#include "Image.h"
#include "TurnImage.h"
#include "Kernel.h"

int main(int argc, char* argv [])
{
    std::cout << "Enter path to file, radius(int type) and sigma(float type) for Gauss blur" << std::endl;
    std::string path_string;
    std::getline(std::cin, path_string);
    const char* path = path_string.c_str();
    int radius;
    float sigma;
    std::cin >> radius >> sigma;
    Turn_Image::RightTurn(path);
    Turn_Image::LeftTurn(path);
    Image image_left(0, 0);
    image_left.Read("Left_turn_image.bmp");
    image_left.GaussianBlur(radius, sigma);
    image_left.Export("Blurring_left_turn_image.bmp");
    Image image_right(0, 0);
    image_right.Read("Right_turn_image.bmp");
    image_right.GaussianBlur(radius, sigma);
    image_right.Export("Blurring_right_turn_image.bmp");
}
