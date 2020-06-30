#include<iostream>

int main(){

    int x_width = 500;
    int y_width = 500;
    std::cout << "P3\n" << x_width << " " << y_width << "\n255\n";
    for(int i = 0; i < x_width; i++)
        for(int j = 0; j < y_width; j++){
            float red_pixel = float(i)/float(y_width);
            float green_pixel = float(j)/float(x_width);
            float blue_pixel = (red_pixel + green_pixel)/1000;
            // then convert these pixels into range of 0 - 256
            int ir = int(red_pixel*256.0f);
            int ig = int(green_pixel*256.0f);
            int ib = int(blue_pixel*256.0f);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    return 0;
}