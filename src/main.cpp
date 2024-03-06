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

    auto material_ground = make_shared<lambertian>(color(0.75, 1.0, 0.5));
    auto material_red = make_shared<lambertian>(color(0.8, 0.0, 0.0));

    auto material_metal = make_shared<metal>(color(0.8, 0.8, 0.8), 0.0);

    auto material_glass = make_shared<dielectric>(1.5);

    // ground
    world.add(make_shared<sphere>(point3(0.0, -1000.0, 0.0), 1000.0, material_ground));

    // big spheres
    world.add(make_shared<sphere>(point3(4.0, 1.0, 0.0), 1.0, material_metal));

    world.add(make_shared<sphere>(point3(0.0, 1.0, 0.0), 1.0, material_glass));

    world.add(make_shared<sphere>(point3(-4.0, 1.0, 0.0), 1.0, material_glass));
    world.add(make_shared<sphere>(point3(-4.0, 1.0, 0.0), -0.6, material_glass));

    world.add(make_shared<sphere>(point3(-8.0, 1.0, 0.0), 1.0, material_red));

    // small spheres
    auto radius = 0.2;
    for (int j = -11; j < 11; j++)
    {
        for (int i = -11; i < 11; i++)
        {
            shared_ptr<material> sphere_material;
            point3 sphere_pos(i + (1 - radius / 2) * random_double(), radius, j + (1 - radius / 2) * random_double());

            auto material_random = random_double();
            if (material_random < 0.6)
            {
                sphere_material = make_shared<lambertian>(color(random_double(), random_double(), random_double()));
            }
            else if (material_random < 0.80)
            {
                sphere_material = make_shared<metal>(color(random_double(), random_double(), random_double()), random_double());
            }
            else
            {
                sphere_material = make_shared<dielectric>(1.5);
            }

            world.add(make_shared<sphere>(sphere_pos, radius, sphere_material));
        }
    }

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 1000;
    // cam.image_width = 200;
    cam.samples_per_pixel = 500;
    // cam.samples_per_pixel = 100;
    // cam.max_depth = 20;
    cam.max_depth = 40;

    cam.vertical_fov = 25;

    cam.look_from = point3(11, 2, 4);
    cam.look_at = point3(0, 0.5, 0);
    cam.v_up = vec3(0, 1, 0);

    cam.defocus_angle = 0.7;
    cam.focus_distance = 12.0;

    cam.render(world);
}

// TODO
// check why images are better stored in gamma space
