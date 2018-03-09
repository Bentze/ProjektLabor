/*This source code copyrighted by Zajzon Dániel (2017-2018)
 
 
 -----------------------------------------------------*/

#include <SDL.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include "Idozito.h"
#include "Circle.h"
#include "Graphics.h"

using namespace std;

const int S_W = /*1920;*/ 1280;
const int S_H = /*1080;*/ 720;

const int S_C_X = S_W / 2;
const int S_C_Y = S_H / 2;

const int T_W = 256;
const int T_H = 128;

const int C_W = 80;
const int C_H = 80;

const int FPS = 60;

fstream F;

SDL_Event event;

SDL_Window* ablak = NULL;
SDL_Renderer* Renderer = NULL;

/*SDL_Texture* YellowTile = NULL;
SDL_Texture* RedTile = NULL;
SDL_Texture* BlueTile = NULL;
SDL_Texture* Talaj = NULL;
SDL_Texture* Selection = NULL;
SDL_Texture* CircleTexture = NULL;
SDL_Texture* CircleTexture_grey = NULL;
SDL_Texture* RedCircleTexture = NULL;
SDL_Texture* YellowCircleTexture = NULL;
SDL_Texture* BlueCircleTexture = NULL;
SDL_Texture* PurpleCircleTexture = NULL;
SDL_Texture* GreenCircleTexture = NULL;
SDL_Texture* OrangeCircleTexture = NULL;
SDL_Texture* BrownCircleTexture = NULL;
SDL_Texture* WhiteCircleTexture = NULL;*/

double heron (double a, double b, double c)			//Hérón képlet
{
    double s = (a + b + c) / 2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

double tavolsag (double x1, double y1, double x2, double y2)   //Kép pont távolsága
{
    double diff_x = x1-x2;
    double diff_y = y1-y2;
    diff_x = diff_x*diff_x;
    diff_y = diff_y*diff_y;
    return sqrt(diff_x + diff_y );
}
/*
SDL_Texture* textura_betolt(string path)			//Textúra létrehozása BMP fájlból
{
    SDL_Texture* ujTextura = NULL;
    SDL_Surface* felulet = SDL_LoadBMP( path.c_str() );
    
    if (felulet == NULL)
    {
        cout << "Egy képet nem sikerült betölteni!" << endl;
    }
    else
    {
        SDL_SetColorKey( felulet, SDL_TRUE, SDL_MapRGB( felulet->format, 0xFF, 0xFF, 0xFF ) );
        ujTextura = SDL_CreateTextureFromSurface(Renderer, felulet);
        if (ujTextura == NULL)
        {
            cout << "Nem sikerült textúrát létrehozni egy képbõl!" << endl;
        }
        
        SDL_FreeSurface(felulet);
    }
    
    return ujTextura;
}

bool media_betolt()
{
    Talaj = textura_betolt( "talaj.bmp" );
    YellowTile = textura_betolt( "yellow.bmp" );
    RedTile = textura_betolt( "red.bmp" );
    BlueTile = textura_betolt( "blue.bmp" );
    Selection = textura_betolt( "template.bmp" );
    CircleTexture = textura_betolt( "circle.bmp" );
    CircleTexture_grey = textura_betolt( "circle_grey.bmp" );
    RedCircleTexture = textura_betolt( "red_circle_texture.bmp" );
    YellowCircleTexture = textura_betolt( "yellow_circle_texture.bmp" );
    BlueCircleTexture = textura_betolt( "blue_circle_texture.bmp" );
    PurpleCircleTexture = textura_betolt( "purple_circle_texture.bmp" );
    GreenCircleTexture = textura_betolt( "green_circle_texture.bmp" );
    OrangeCircleTexture = textura_betolt( "orange_circle_texture.bmp" );
    BrownCircleTexture = textura_betolt( "brown_circle_texture.bmp" );
    WhiteCircleTexture = textura_betolt( "white_circle_texture.bmp" );
    
    if (Selection == NULL)
    {
        return false;
    }
    SDL_SetTextureAlphaMod(Selection, 120);
    if (YellowTile == NULL)
    {
        return false;
    }
    if (RedTile == NULL)
    {
        return false;
    }
    if (BlueTile == NULL)
    {
        return false;
    }
    if (Talaj == NULL)
    {
        return false;
    }
    if (CircleTexture == NULL)
    {
        return false;
    }
    if (CircleTexture_grey == NULL)
    {
        return false;
    }
    if (RedCircleTexture == NULL)
    {
        return false;
    }
    if (YellowCircleTexture == NULL)
    {
        return false;
    }
    if (BlueCircleTexture == NULL)
    {
        return false;
    }
    if (PurpleCircleTexture == NULL)
    {
        return false;
    }
    if (GreenCircleTexture == NULL)
    {
        return false;
    }
    if (BlueCircleTexture == NULL)
    {
        return false;
    }
    if (BrownCircleTexture == NULL)
    {
        return false;
    }
    if (WhiteCircleTexture == NULL)
    {
        return false;
    }
    return true;
}
*/
/*bool elokeszit ()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "Nem sikerult az SDL-t inicializálni!" << endl;
        return false;
    }
    else
    {
        ablak = SDL_CreateWindow( "Tileset tesztprogram", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_W, S_H, /SDL_WINDOW_FULLSCREEN/ SDL_WINDOW_SHOWN);
        if (ablak == NULL)
        {
            cout << "Az ablakot nem sikerült létrehozni!" << endl;
            return false;
        }
        else
        {
            Renderer = SDL_CreateRenderer( ablak, -1, SDL_RENDERER_ACCELERATED  | SDL_RENDERER_PRESENTVSYNC );
            if( Renderer == NULL )
            {
                cout << "A Renderer-t nem sikerült létrehozni!" << endl;
                return false;
            }
            else
            {
                SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                if (media_betolt() == false)
                {
                    cout << "A fájlok betöltése sikertelen!" << endl;
                    return false;
                }
            }
        }
    }
    
    return true;
}

void bezar()
{
    SDL_DestroyTexture( YellowTile );
    SDL_DestroyTexture( RedTile );
    SDL_DestroyTexture( BlueTile );
    SDL_DestroyTexture( Talaj );
    SDL_DestroyTexture( Selection );
    SDL_DestroyTexture( CircleTexture );
    SDL_DestroyTexture( CircleTexture_grey );
    SDL_DestroyTexture( RedCircleTexture );
    SDL_DestroyTexture( YellowCircleTexture );
    SDL_DestroyTexture( BlueCircleTexture );
    SDL_DestroyTexture( PurpleCircleTexture );
    SDL_DestroyTexture( GreenCircleTexture );
    SDL_DestroyTexture( OrangeCircleTexture );
    SDL_DestroyTexture( BrownCircleTexture );
    SDL_DestroyTexture( WhiteCircleTexture );
    
    SDL_DestroyWindow (ablak);
    SDL_DestroyRenderer (Renderer);
    
    SDL_Quit();
}

bool rombuszban_van(int pont_x, int pont_y, int a_x, int a_y, int b_x, int b_y, int c_x, int c_y, int d_x, int d_y, const double &area)
{
    double edge1 = tavolsag(pont_x, pont_y, a_x, a_y);
    double edge2 = tavolsag(pont_x, pont_y, b_x, b_y);
    double edge3 = tavolsag(pont_x, pont_y, c_x, c_y);
    double edge4 = tavolsag(pont_x, pont_y, d_x, d_y);
    
    double border_edge = tavolsag(a_x, a_y, b_x, b_y);
    
    double t1 = heron(edge1,edge2,border_edge);
    double t2 = heron(edge1,edge3,border_edge);
    double t3 = heron(edge2,edge4,border_edge);
    double t4 = heron(edge3,edge4,border_edge);
    double sumt = t1+t2+t3+t4;
    return (1 > abs(sumt - area));
}
*/
int main( int argc, char* args[] )
{
    
    int map_width, map_height;
    int mouse_pozx, mouse_pozy;
    
    double Iso_cord_X, Iso_cord_Y;
    
    map_width = 5;
    map_height = 5;
    
    
    Graphics GraphicsHandler(map_width, map_height);
    if (GraphicsHandler.getSuccess() == false)
    {
        return 1;
    }
    
    bool kilep = false;
    //GraphicsHandler.StartTimer();
    do
    {
        while( SDL_PollEvent( &event ) != 0 )
        {
            if( event.type == SDL_QUIT )
            {
                kilep = true;
            }
            else if( event.type == SDL_KEYDOWN )
            {
                switch( event.key.keysym.sym )
                {
                    case SDLK_ESCAPE:
                        kilep = true;
                        break;
                }
            }
            else if( event.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState( &mouse_pozx, &mouse_pozy );
                Iso_cord_X = int(  (mouse_pozx / (T_W/2.0) + (mouse_pozy) / (T_H/2.0)) / 2 - map_width/2.0 ); 
                Iso_cord_Y = int(  (-mouse_pozx / (T_W/2.0) + (mouse_pozy) / (T_H/2.0)) / 2 + map_height/2.0 ); 
                GraphicsHandler.setIsoX(Iso_cord_X);
                GraphicsHandler.setIsoY(Iso_cord_Y);
            }
            GraphicsHandler.DrawFrame();
        }
    }
    while(kilep == false);
    return 0;
}
