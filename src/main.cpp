#include <iostream>
#include <vector>
#include <string>
#include <vec3.h>
#include <color.h>

using namespace std;

int main()
{
    auto image_width = 256;
    auto image_height = 256;

    std::cout << "P3\n"
              << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_height; i++)
        {
            auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);

            write_color(std::cout, pixel_color);
        }
    }

    // vec3 test = vec3(1.0f, 1.0f, 1.0f);
    // test = unit_vector(test);

    // std::cout << test[0] << std::endl;
    // std::cout << test[1] << std::endl;
    // std::cout << test[2] << std::endl;

    std::clog << "\rDone                                      \n";
}