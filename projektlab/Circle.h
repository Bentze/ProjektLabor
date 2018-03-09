#ifndef CIRCLE_H
#define CIRCLE_H

#include <SDL.h>

class circle
{
    public:
        circle(bool player, int x, int y);
        void addColor(int color_number);
        bool getRed();
        bool getYellow();
        bool getBlue();
        int getX();
        int getY();
        bool getPlayer();
        
    private:
        bool player;
        bool color[3];
        int x,y;
};

#endif
