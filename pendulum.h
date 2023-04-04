#ifndef PENDULUM_H
#define PENDULUM_H

#include <cmath>

#include "sphere.h"
#include "guiData.h"

#define PI 3.14159

class Pendulum{
public:
    int x0 = 0, y0 = -400, z0 = 0;
    int x1, y1, z1;
    int x2, y2, z2;
    int m1 = 20, m2 = 20;
    int l1 = 800, l2 = 800;
    double tx1 = PI/2, tx2 = PI/2;
    double tx1_v = 0, tx2_v = 0;
    double tx1_a = 0, tx2_a = 0;
    double damping = 0.999;
    double g = 5;


    Pendulum(int x_ = 0, int y_ = -400, int z_ = 0);
    void updateAngleAcceleration();
    void update();
    void draw(sf::Uint8 *pixels, const int WIDTH, const int HEIGHT, Light light);

    void updateFromGui(GuiData guiData);

private:



};

#endif