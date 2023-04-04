#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>

class Line{
public:
    int x1, x2, y1, y2;

    Line(int x1_, int x2_, int y1_, int y2_, int r_ = 255, int g_ = 255, int b_ = 255);
    
    void draw(sf::Uint8 *pixels, int width, int height);

private:
    int r, g, b;
    int offsetx, offsety;
};


#endif