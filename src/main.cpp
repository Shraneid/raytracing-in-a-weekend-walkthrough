#include "common.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include <iostream>

int main()
{
    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left = make_shared<metal>(color(0.2, 0.2, 0.8), 0.3);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.8);
    auto material_glass = make_shared<dielectric>(1.5);

    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100.0, material_ground));

    // left
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), 0.5, material_glass));
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.0), -0.3, material_glass));

    // center
    world.add(make_shared<sphere>(point3(-0.5, 0, -1.5), 0.5, material_center));
    world.add(make_shared<sphere>(point3(0., -0.2, -1.0), 0.2, material_glass));

    // right
    world.add(make_shared<sphere>(point3(1.0, 0, -1.0), 0.5, material_right));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 20;

    cam.render(world);
}

// TODO
// check why images are better stored in gamma space
