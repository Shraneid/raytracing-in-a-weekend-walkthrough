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
    auto material_eyes = make_shared<lambertian>(color(0.0, 0.0, 0.0));
    auto material_left = make_shared<metal>(color(0.2, 0.2, 0.8));
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2));

    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0, -1.5), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0, -1.0), 0.5, material_right));

    world.add(make_shared<sphere>(point3(-0.15, 0.12, -0.53), 0.05, material_eyes));
    world.add(make_shared<sphere>(point3(0.15, 0.12, -0.53), 0.05, material_eyes));

    world.add(make_shared<sphere>(point3(-0.17, -0.12, -0.5), 0.03, material_eyes));
    world.add(make_shared<sphere>(point3(-0.14, -0.13, -0.5), 0.03, material_eyes));
    world.add(make_shared<sphere>(point3(-0.11, -0.14, -0.5), 0.03, material_eyes));
    world.add(make_shared<sphere>(point3(-0.08, -0.148, -0.5), 0.03, material_eyes));
    world.add(make_shared<sphere>(point3(-0.05, -0.155, -0.5), 0.03, material_eyes));
    world.add(make_shared<sphere>(point3(-0.02, -0.16, -0.5), 0.03, material_eyes));

    world.add(make_shared<sphere>(point3(0.0, -0.163, -0.5), 0.03, material_eyes));

    world.add(make_shared<sphere>(point3(0.17, -0.12, -0.5), 0.03, material_eyes));
    world.add(make_shared<sphere>(point3(0.14, -0.13, -0.5), 0.03, material_eyes));
    world.add(make_shared<sphere>(point3(0.11, -0.14, -0.5), 0.03, material_eyes));
    world.add(make_shared<sphere>(point3(0.08, -0.148, -0.5), 0.03, material_eyes));
    world.add(make_shared<sphere>(point3(0.05, -0.155, -0.5), 0.03, material_eyes));
    world.add(make_shared<sphere>(point3(0.02, -0.16, -0.5), 0.03, material_eyes));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1000;
    cam.samples_per_pixel = 200;
    cam.max_depth = 20;

    cam.render(world);
}

// TODO
// check why images are better stored in gamma space
