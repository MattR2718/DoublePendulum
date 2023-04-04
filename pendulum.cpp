#include "pendulum.h"

Pendulum::Pendulum(int x_, int y_, int z_){
    this->x0 = x_;
    this->y0 = y_;
    this->z0 = z_;
    this->update();
}

void Pendulum::updateAngleAcceleration(){
    // https://www.myphysicslab.com/pendulum/double-pendulum-en.html
    double num11 = -g * (2*this->m1 + this->m2) * std::sin(this->tx1);
    double num12 = -this->m2 * g * std::sin(this->tx1 - 2 * this->tx2);
    double num13 = -2 * std::sin(this->tx1 - this->tx2) * this->m2 * (this->tx2_v * this->tx2_v * this->l2 + this->tx1_v * this->tx1_v * this->l1 * std::cos(this->tx1 - this->tx2));
    double num1 = num11 + num12 + num13;
    double den1 = this->l1 * ( 2 * this->m1 + this->m2 - this->m2 * std::cos(2 * this->tx1 - 2 * this->tx2));
    this->tx1_a = num1 / den1;

    double num21 = 2 * std::sin(this->tx1 - this->tx2);
    double num22 = this->tx1_v * this->tx1_v * this->l1 * (this->m1 + this->m2);
    double num23 = g * (this->m1 + this->m2) * std::cos(this->tx1);
    double num24 = this->tx2_v * this->tx2_v * this->l2 * this->m2 * std::cos(this->tx1 - this->tx2);
    double num2 = num21 * (num22 + num23 + num24);
    double den2 = this->l2 * (2 * this->m1 + this-> m2 - this->m2 * std::cos(2 * this->tx1 - 2 * this->tx2));
    this->tx2_a = num2 / den2;
}

void Pendulum::update(){

    this->updateAngleAcceleration();

    //Update velocity by acceleration
    this->tx1_v += this->tx1_a;
    this->tx2_v += this->tx2_a;

    //Add damping
    this->tx1_v *= this->damping;
    this->tx2_v *= this->damping;

    //Update angles by velocity
    this->tx1 += this->tx1_v;
    this->tx2 += this->tx2_v;

    //Update mass1 position
    this->x1 = this->x0 + this->l1 * std::sin(this->tx1);
    this->y1 = this->y0 + this->l1 * std::cos(this->tx1);
    this->z1 = this->z0 + this->l1 * std::sin(0);

    //Update mass2 posiiton
    this->x2 = this->x1 + this->l2 * std::sin(this->tx2);
    this->y2 = this->y1 + this->l2 * std::cos(this->tx2);
    this->z2 = this->z1 + this->l2 * std::sin(0);
}

void Pendulum::draw(sf::Uint8 *pixels, const int WIDTH, const int HEIGHT, Light light){
    this->update();
    
    int m = (this->m1 > this->m2) ? this->m1 : this->m2;

    Sphere bob0(this->x0, this->y0, this->z0, m * 5, 255, 0, 0, 255);
    Sphere bob1(this->x1, this->y1, this->z1, this->m1 * 5, 0, 255, 0, 255);
    Sphere bob2(this->x2, this->y2, this->z2, this->m2 * 5, 0, 0, 255, 255);

    if(drawLines){
        Line line1(this->x0, this->x1, this->y0, this->y1, 255, 0, 0);
        line1.draw(pixels, WIDTH, HEIGHT);
        Line line2(this->x1, this->x2, this->y1, this->y2, 255, 0, 0);
        line2.draw(pixels, WIDTH, HEIGHT);
    }

    bob0.draw(pixels, WIDTH, HEIGHT, light);
    bob1.draw(pixels, WIDTH, HEIGHT, light);
    bob2.draw(pixels, WIDTH, HEIGHT, light);
}

void Pendulum::updateFromGui(GuiData guiData){

    auto degToRad = [](const auto deg){ return deg * PI / 180; };

    this->m1 = guiData.m1;
    this->m2 = guiData.m2;
    this->l1 = guiData.l1;
    this->l2 = guiData.l2;
    /* this->tx1 = degToRad(guiData.tx1);
    this->tx2 = degToRad(guiData.tx2); */
    this->tx1 = guiData.tx1;
    this->tx2 = guiData.tx2;
    this->damping = guiData.damping;
    this->g = guiData.g;

    this->tx1_a = 0;
    this->tx2_a = 0;
    this->tx1_v = 0;
    this->tx2_v = 0;
}