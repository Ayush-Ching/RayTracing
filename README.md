# Ray Tracing (in a month....?)

This is a static raytracer written in `C++` and runs entirely on the CPU (that is why it is super slow (took 8 hours to render the output below)).

Currently, it can only render spheres and has only three inbuilt materials (Lambertians, Metals and Dielectrics).

Made by following the book [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

The current output looks like this :

![the output](/img/image.png "a beautiful chessboard indeed")

-----

## Build Instructions

### Dependencies

- Any `C++` compiler like `gcc` or `clang`

### Compiling

Almost all of the code is written in `.h` files so no `make` or `cmake` is required.

Simply compile `main.cc` using any modern `C++` compiler.

### Running

Just run the compiles binary and the output will be saved in a new directory as `./img/image.ppm`. This is in `.ppm` so you will have to comvert to `.png` for any practical uses (you can use `GIMP`).

> **Tip :** Before compiling, go to `main.cc` and change the `cam.samples_per_pixel` and `cam.max_depth` to be a bit lower and maybe even decrease the number of balls in the for loops above because without these modifications, it takes **8 hours** to render the scene which is shown above. Do not change these settings if you have no job and want this exact scene.

-----

Will probably not go ahead with this one until I integrate GPU computation.