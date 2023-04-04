#include "line.h"

Line::Line(int x1_, int x2_, int y1_, int y2_, int r_, int g_, int b_){
    this->x1 = x1_;
    this->x2 = x2_;
    this->y1 = y1_;
    this->y2 = y2_;
    this->r = r_;
    this->g = g_; 
    this->b = b_;
}

template <typename T>
int iPart(T x){
    return floor(x);
}

template <typename T>
int roundN(T x){
    return iPart(x + 0.5);
}

template <typename T>
float fPart(T x){
    return x - floor(x);
}

template <typename T>
float rfPart(T x){
    return 1 - fPart(x);
}

//Performs Xiaolin Wu's Line drawing algorithm to draw an anti-aliased line between the two points in line
void Line::draw(sf::Uint8 *pixels, const int width, const int height){
    this->offsetx = width / 2;
    this->offsety = height / 2;
    //Lambda function to plot a single point at position (xval, yval) on screen
    auto plot = [&](int xval, int yval, float bright){
        if(xval < -this->offsetx || xval >= this->offsetx || yval < -this->offsety || yval >= this->offsety){return;}
        int index = ((yval + this->offsety) * width + (xval + this->offsetx)) * 4;
        pixels[index] = this->r;
        pixels[index + 1] = this->g;
        pixels[index + 2] = this->b;
        pixels[index + 3] = 255 * bright;
    };
    
    int LENGTH = width * height * 4;
    
    bool steep = std::abs(this->y2 - this->y1) > std::abs(this->x2 - this->x1);

    if(steep){
        int t = this->x1;
        this->x1 = this->y1;
        this->y1 = t;

        t = this->x2;
        this->x2 = this->y2;
        this->y2 = t;
    }

    if(this->x1 > this->x2){
        int t = this->x1;
        this->x1 = this->x2;
        this->x2 = t;

        t = this->y1;
        this->y1 = this->y2;
        this->y2 = t;
    }

    float dx = this->x2 - this->x1;
    float dy = this->y2 - this->y1;

    float gradient = 0;

    if (dx == 0){
        gradient = 1;
    } else{
        gradient = dy/dx;
    }

    float xend = roundN(this->x1);
    float yend = this->y1 + gradient * (xend - this->x1);
    float xgap = rfPart(static_cast<float>(this->x1) + 0.5);
    float xpxl1 = xend;
    float ypxl1 = iPart(yend);

    if (steep){
        plot(ypxl1, xpxl1, rfPart(yend) * xgap);
        plot(ypxl1 + 1, xpxl1, fPart(yend) * xgap);
    } else{
        plot(xpxl1, ypxl1, rfPart(yend) * xgap);
        plot(xpxl1, ypxl1 + 1, fPart(yend) * xgap);
    }
    float intery = yend + gradient;

    xend = roundN(this->x2);
    yend = this->y2 + gradient * (xend - this->x2);
    xgap = fPart(this->x2 + 0.5);
    float xpxl2 = xend;
    float ypxl2 = iPart(yend);
    if(steep){
        plot(ypxl2, xpxl2, rfPart(yend) * xgap);
        plot(ypxl2 + 1, xpxl2, fPart(yend) * xgap);
    }else{
        plot(xpxl2, ypxl2, rfPart(yend) + xgap);
        plot(xpxl2, ypxl2 + 1, fPart(yend) * xgap);
    }

    if(steep){
        for (int x = xpxl1 + 1; x < xpxl2; x++){
            plot(iPart(intery), x, rfPart(intery));
            plot(iPart(intery) + 1, x, fPart(intery));
            intery += gradient;
        }
    }else{
        for(int x = xpxl1 + 1; x < xpxl2; x++){
            plot(x, iPart(intery), rfPart(intery));
            plot(x, iPart(intery) + 1, fPart(intery));
            intery += gradient;
        }
    }

}
