#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Idozito.h"
#include "Circle.h"
#include "time.h"

using namespace std;

class Graphics
{
    const int S_W = /*1920;*/ 1280;
    const int S_H = /*1080;*/ 720;

    const int S_C_X = S_W / 2;
    const int S_C_Y = S_H / 2;

    const int T_W = 256;
    const int T_H = 128;

    const int C_W = 80;
    const int C_H = 80;

    const int FPS = 60;

    Idozito FPS_Timer;

    bool succes_init;

    map<string,SDL_Texture*> Textures;
    SDL_Renderer* Renderer = NULL;
    SDL_Window* ablak = NULL;

    //int mouse_pozx, mouse_pozy;

    double Iso_cord_X, Iso_cord_Y;
    int map_width, map_height;

    int Board[5][5];
    circle* korok[8];

    SDL_Rect Tile;
    SDL_Rect clip;
public:
    Graphics(int w, int h);
    ~Graphics();
    bool init();
    bool LoadMedia();
    void bezar();
    bool getSuccess();
    void DrawFrame();
    //void StartTimer();
    //void setMapSize(int w, int h);
    void setIsoX(double Iso_cord_X);
    void setIsoY(double Iso_cord_Y);
    SDL_Texture* LoadTexture(string path);
};
#endif

