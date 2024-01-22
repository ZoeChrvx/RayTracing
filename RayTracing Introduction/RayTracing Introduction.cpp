#include <iostream>
#include "HittableCollection.h"
#include "Sphere.h"
#include "Camera.h"

#include "DialectricMaterial.h"
#include "LambertianMaterial.h"
#include "MetalMaterial.h"

using namespace std;

int main(int argc, char* argv[])
{
    //World
    HittableCollection world;

    shared_ptr<Material> groundMat = make_shared<LambertianMaterial>(Color(0.5, 0.5, 0.5));
    world.Add(make_shared<Sphere>(Position(0, -1000, 0), 1000, groundMat));

    for (int i = -11; i < 11; i++) {
        for (int j = -11; j < 11; j++) {
            double materialChoice = RandomDouble();
            Position center(i + 0.9 * RandomDouble(), 0.2, j + 0.9 * RandomDouble());

            if ((center - Position(4, 0.2, 0)).Length() > 0.9) {
                shared_ptr<Material> chosenMat;
                if (materialChoice < 0.8) {
                    Color albedo = Color::Random() * Color::Random();
                    chosenMat = make_shared<LambertianMaterial>(albedo);
                }
                else if (materialChoice < 0.95) {
                    Color albedo = Color::Random(0.5, 1);
                    double fuzz = RandomDouble(0, 0.5);
                    chosenMat = make_shared<MetalMaterial>(albedo, fuzz);
                }
                else {
                    chosenMat = make_shared<DialectricMaterial>(1.5);
                }
                world.Add(make_shared<Sphere>(center, 0.2, chosenMat));
            }
        }
    }

    Camera camera(1200, 16.0 / 9.0, 500, 50, 20);
    camera.SetTransform(Position(13, 2, 3), Position(0, 0, 0), Vector3(0, 1, 0));
    camera.SetFocus(0.6, 10.0);
    camera.Render(world);
    return 0;

    /*shared_ptr<Material> groundMat = make_shared<LambertianMaterial>(Color(0.8, 0.8, 0.0));
    shared_ptr<Material> centerMat = make_shared<LambertianMaterial>(Color(0.1, 0.2, 0.5));
    shared_ptr<Material> leftMat = make_shared<DialectricMaterial>(1.5);
    shared_ptr<Material> rightMat = make_shared<MetalMaterial>(Color(0.8, 0.6, 0.2), 0.0);


    world.Add(make_shared<Sphere>(Position(0, -100.5, -1), 100, groundMat));
    world.Add(make_shared<Sphere>(Position(0, 0, -1), 0.5, centerMat));
    world.Add(make_shared<Sphere>(Position(-1, 0, -1), 0.5, leftMat));
    world.Add(make_shared<Sphere>(Position(-1, 0, -1), -0.4, leftMat));
    world.Add(make_shared<Sphere>(Position(1, 0, -1), 0.5, rightMat));


    Camera camera(400, 16.0 / 9.0, 100, 50, 20);
    camera.SetTransform(Position(-2, 2, 1), Position(0, 0, -1), Vector3(0, 1, 0));
    camera.SetFocus(10.0, 3.4);
    camera.Render(world);
    return 0;*/

}

