#include<iostream>

int main(){

    freopen("img/image.ppm", "w", stdout);

    int width  = 256;
    int height = 256;

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            int col = (x/32 + y/32) % 2 == 0 ? 128 : 64;
            std::cout << col + (x + y) / 4 << ' ' << col + x / 2 << ' ' << col + y / 2 << '\n';
        }
    }

    return 0;
}