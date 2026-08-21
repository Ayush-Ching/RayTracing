#include "color.h"
#include "vec3.h"

#include <iostream>
#include <fstream>

int main(){

    std::ofstream imageFS("img/image.ppm");

    int width  = 512;
    int height = 512;

    if(imageFS.is_open()){

        imageFS << "P3\n" << width << ' ' << height << "\n255\n";

        for(int y=0; y<height; y++){
            std::clog << "\rScanlines remaining : " << (height - y) << ' ' << std::flush;
            
            for(int x=0; x<width; x++){
                auto pixel_color = color(double(x) / (width-1), double(y) / (height - 1), 0.0);
                write_color(imageFS, pixel_color);
            }
        }

        imageFS.close();
        std::clog << "\rDone.                     \n";
    }
    else {
        std::cerr << "Unable to open output image file location\n";
    }

    return 0;
}