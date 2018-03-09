#include "Circle.h"

circle::circle(bool player, int x, int y)
{
    this->player = player;
    color[0] = false;
    color[1] = false;
    color[2] = false;
    this->x = x;
    this->y = y;
}

void circle::addColor(int color_number)
{
    if(color[color_number] == true)
    {
        color[color_number] = false;
    }
    else
    {
        color[color_number] = true;
    }
}

bool circle::getRed()
{
    return color[0];
}

bool circle::getYellow()
{
    return color[1];
}

bool circle::getBlue()
{
    return color[2];
}

int circle::getX()
{
    return x;
}

int circle::getY()
{
    return y;
}

bool circle::getPlayer()
{
    return player;
}
