#ifndef GUIDATA_H
#define GUIDATA_H

#define PI 3.14159

struct GuiData{
    int m1 = 20, m2 = 20;
    int l1 = 600, l2 = 600;
    float tx1 = PI/2, tx2 = PI/2;
    float damping = 0.999;
    float g = 5;
    
    bool clearPixels = true;

    bool showDemoSphere = false;
};

#endif