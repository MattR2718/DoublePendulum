#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "light.h"

class Sphere{

public:
    Sphere(int x_, int y_, int z_, int rad_ = 20, int r_ = 255, int g_ = 255, int b_ = 255, int a_ = 255);

    void draw(sf::Uint8 *pixels, const int WIDTH, const int HEIGHT, Light light);

    int x, y, z;
    int px, py, pz;

private:
    int r, g, b, a;
    int rad;
    int offsetx, offsety;

    void plotOctants(sf::Uint8 *pixels, const int WIDTH, const int HEIGHT, int x, int y, Light light);

};


#endif