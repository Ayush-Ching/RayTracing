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
                double r = double(x) / width;
                double g = double(y) / height;
                double b = 0.5;

                int ir = int(255.999 * r);
                int ig = int(255.999 * g);
                int ib = int(255.999 * b);

                imageFS << ir << ' ' << ig << ' ' << ib << '\n';
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