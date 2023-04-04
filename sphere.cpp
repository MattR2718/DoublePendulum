#include "sphere.h"

Sphere::Sphere(int x_, int y_, int z_, int rad_, int r_, int g_, int b_, int a_){
    this->x = x_;
    this->y = y_;
    this->z = z_;
    this->px = x_;
    this->py = y_;
    this->pz = z_;
    this->r = r_;
    this->g = g_;
    this->b = b_;
    this->a = a_;
    this->rad = rad_;
}


//Plot all 8 points, one in each octant of the circle
void Sphere::plotOctants(sf::Uint8 *pixels, const int WIDTH, const int HEIGHT, int x, int y, Light light){
    //Lambda finction to plot a single pixel in the pixel array
    auto plot = [&](const int i, const int j, bool outline = false){
        if(i < -this->offsetx || i >= this->offsetx || j < -this->offsety || j >= this->offsety){return;}
        
        //Calculate brightness based on angle of light
        int a = this->px; 
        int b = this->py;
        int c = this->pz;
        
        int dx = i - a;
        int dy = j - b;
        int dz = c + std::sqrt((this->rad * this->rad) - (dx * dx) - (dy * dy));

        /* float x_t = std::asin((float)dx/this->rad);
        float y_t = std::acos((float)dy/this->rad);
        float z_t = std::asin((float)dz/this->rad); */

        float dp = (light.dx * dx + light.dy * dy + light.dz * dz) / (std::sqrt(light.dx * light.dx + light.dy * light.dy + light.dz * light.dz) * std::sqrt(dx*dx+dy*dy+dz*dz));

        /* float rr = this->r / (this->r + this-> g + this->b);
        float gr = this->g / (this->r + this-> g + this->b);
        float br = this->b / (this->r + this-> g + this->b); */

        float rr = 1, gr = 1, br = 1;


        int red = (dp > 0) ? (this->r * dp + 25) : 25 * rr;
        int green = (dp > 0) ? (this->g * dp + 25) : 25 * gr;
        int blue = (dp > 0) ? (this->b * dp + 25): 25 * br;
        red = (red > 255) ? 255 : red;
        green = (green > 255) ? 255 : green;
        blue = (blue > 255) ? 255 : blue;


        /* int red = ((dp * this->r) < 20) ? 20 : dp * this->r;
        int green = ((dp * this->g) < 20) ? 20 : dp * this->g;
        int blue = ((dp * this->b) < 20) ? 20 : dp * this->b; */
        
        pixels[((j + this->offsety) * WIDTH + (i + this->offsetx)) * 4] = red;
        pixels[((j + this->offsety) * WIDTH + (i + this->offsetx)) * 4 + 1] = green;
        pixels[((j + this->offsety) * WIDTH + (i + this->offsetx)) * 4 + 2] = blue;
    };
    //Plots points accordint to bresenhams algorithm
    plot(this->px + x, this->py + y);
    plot(this->px - x, this->py + y);
    plot(this->px + x, this->py - y);
    plot(this->px - x, this->py - y);
    plot(this->px - y, this->py + x);
    plot(this->px + y, this->py - x);
    plot(this->px - y, this->py - x);
    plot(this->px + y, this->py + x);

    //Lambda finction to fill the pixel array with a line
    auto plotLine = [&](const int x1, const int x2, const int y){
        int px1 = x1, px2 = x2;
        if(px1 > px2){ px1 = x2; px2 = x1; }
        for(int c = px1 + 1; c < px2; c++){
            plot(c, y, true);
        }
    };

    //draws lines across each point to fill in the circle
    plotLine(this->px - y, this->px + y, this->py + x);
    plotLine(this->px - x, this->px + x, this->py + y);
    plotLine(this->px - x, this->px + x, this->py - y);
    plotLine(this->px - y, this->px + y, this->py - x);

}

void Sphere::draw(sf::Uint8 *pixels, const int WIDTH, const int HEIGHT, Light light){
    this->offsetx = WIDTH / 2;
    this->offsety = HEIGHT / 2;
    this->px = this->x; 
    this->py = this->y; 
    this->pz = this->z; 

    //Bresenhams circle drawing algorithm
    int x = 0;
    int y = this->rad;
    int decPar = 3 - 2 * this->rad;
    plotOctants(pixels, WIDTH, HEIGHT, x, y, light);
    while( y >= x){
        x++;
        if(decPar > 0){
            y--;
            decPar = decPar + 4 * (x - y) + 10;
        }else{
            decPar = decPar + 4 * x + 6;
        }
        plotOctants(pixels, WIDTH, HEIGHT, x, y, light);
    }
}