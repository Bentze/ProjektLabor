#include "Graphics.h"

Graphics::Graphics(int w, int h)
{
    if(init() == true)
    {
        succes_init = true;
        
        map_width = w;
        map_height = h;
        
        srand(time(NULL));
        int generator = rand() % 200;
        int szinek[3] = {0};
    
        for ( int i = 0; i < w; i++)		//Tábla generálása
        {
            for (int j = 0; j < h; j++)
            {
                srand(time(NULL) + generator);
                int szin = rand()%3;
                generator -= szin + rand()%997; 
                Board[i][j] = szin;
                SDL_Delay(rand()%7);
                szinek[szin]++;
            }
        }
        cout << szinek[0] << " " << szinek[1] << " " << szinek[2] << endl;
        
        korok[0] = new circle(0,0,0);
        korok[1] = new circle(0,1,0);
        korok[2] = new circle(0,1,1);
        korok[3] = new circle(0,0,1);
    
        korok[4] = new circle(1,3,3);
        korok[5] = new circle(1,4,3);
        korok[6] = new circle(1,4,4);
        korok[7] = new circle(1,3,4);
        
        korok[0]->addColor(0);
        korok[1]->addColor(1);
        korok[2]->addColor(2);
        korok[3]->addColor(0);
        korok[3]->addColor(1);
        korok[3]->addColor(2);
    
        korok[4]->addColor(0);
        korok[4]->addColor(1);
    
        korok[5]->addColor(0);
        korok[5]->addColor(2);
    
        korok[6]->addColor(1);
        korok[6]->addColor(2);
        
        FPS_Timer.start();
    }
    else
    {
        succes_init = false;
    }
}

Graphics::~Graphics()
{
    map<string,SDL_Texture*>::const_iterator it;
    for(it = Textures.begin(); it != Textures.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    
    SDL_DestroyWindow (ablak);
    SDL_DestroyRenderer (Renderer);
    
    SDL_Quit();
}

/*void Graphics::StartTimer()
{
    FPS_Timer.start();
}*/

void Graphics::setIsoX(double Iso_cord_X)
{
    this->Iso_cord_X = Iso_cord_X;
}

void Graphics::setIsoY(double Iso_cord_Y)
{
    this->Iso_cord_Y = Iso_cord_Y;
}

/*void Graphics::setMapSize(int w, int h)
{
    map_width = w;
    map_height = h;
}*/

void Graphics::DrawFrame()
{
        SDL_RenderClear( Renderer );
        
        Tile.h = S_H; //a talaj textúra dimenziói jelenleg megegyeznek a képernyő dimenzióival
        Tile.w = S_W;
        Tile.x = 0;
        Tile.y = 0;
        
        SDL_RenderCopy( Renderer, Textures["Talaj"], NULL, &Tile);
        
        Tile.w = T_W;
        Tile.h = T_H;
        
        for ( int i = 0; i <  map_width; i++)		//Tábla felrajzolása
        {
            SDL_Texture* mezo = NULL;
            for (int j = 0; j < map_height; j++)
            {
                Tile.x= (map_height-1)*T_W/2+(j-i)*(T_W/2);
                Tile.y=(i+j)*(T_H/2);
                if(Board[i][j] == 0)
                {
                    mezo = Textures["RedTile"];
                }
                else if(Board[i][j] == 1)
                {
                    mezo = Textures["YellowTile"];
                }
                else
                {
                    mezo = Textures["BlueTile"];
                }
                
                SDL_RenderCopy( Renderer, mezo, NULL, &Tile);
            }
            mezo = NULL;
            SDL_DestroyTexture(mezo);
        }
        
        if (Iso_cord_X >= 0 and Iso_cord_X < map_width and Iso_cord_Y >= 0 and Iso_cord_Y < map_height)
        {    
            Tile.x = (map_height-1)*T_W/2+(Iso_cord_X-Iso_cord_Y)*(T_W/2);
            Tile.y = (Iso_cord_Y+Iso_cord_X)*(T_H/2);
            SDL_RenderCopy( Renderer, Textures["Selection"] , NULL, &Tile);
        }
        
        Tile.w = C_W;
        Tile.h = C_H;
        
        for(int i = 0; i < 8; i++)                                      //Körök felrajzolása
        {
            int x = korok[i]->getX();
            int y = korok[i]->getY();
            
            Tile.x = (map_height-1)*T_W/2+(y-x)*(T_W/2) + (T_W-C_H)/2;
            Tile.y = (x+y)*(T_H/2) + (T_H-C_H)/2;
            
            bool red = korok[i]->getRed();
            bool yellow = korok[i]->getYellow();
            bool blue = korok[i]->getBlue();
            
            if(red == 1 and yellow == 0 and blue == 0)
            {
                SDL_RenderCopy( Renderer, Textures["RedCircleTexture"], NULL, &Tile);
            }
            else if(red == 0 and yellow == 1 and blue == 0)
            {
                SDL_RenderCopy( Renderer, Textures["YellowCircleTexture"], NULL, &Tile);
            }
            else if(red == 0 and yellow == 0 and blue == 1)
            {
                SDL_RenderCopy( Renderer, Textures["BlueCircleTexture"], NULL, &Tile);
            }
            else if(red == 1 and yellow == 1 and blue == 0)
            {
                SDL_RenderCopy( Renderer, Textures["OrangeCircleTexture"], NULL, &Tile);
            }
            else if(red == 1 and yellow == 0 and blue == 1)
            {
                SDL_RenderCopy( Renderer, Textures["PurpleCircleTexture"], NULL, &Tile);
            }
            else if(red == 0 and yellow == 1 and blue == 1)
            {
                SDL_RenderCopy( Renderer, Textures["GreenCircleTexture"], NULL, &Tile);
            }
            else if(red == 1 and yellow == 1 and blue == 1)
            {
                SDL_RenderCopy( Renderer, Textures["BrownCircleTexture"], NULL, &Tile);
            }
            else if (red == 0 and yellow == 0 and blue == 0)
            {
                SDL_RenderCopy( Renderer, Textures["WhiteCircleTexture"], NULL, &Tile);
            }
            
            if(korok[i]->getPlayer())
            {
                SDL_RenderCopy( Renderer, Textures["CircleTexture_grey"], NULL, &Tile);
            }
            else
            {
                SDL_RenderCopy( Renderer, Textures["CircleTexture"], NULL, &Tile);
            }
            
            
        }
        
        SDL_RenderPresent( Renderer );			//Képernyő frissítése
        
        if (FPS_Timer.ido() < 1000 / FPS)		//FPS korlátozás
        {
            SDL_Delay(1000 / FPS - FPS_Timer.ido());
        }
}

bool Graphics::getSuccess()
{
    return succes_init;
}

bool Graphics::init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        cout << "Nem sikerult az SDL-t inicializálni!" << endl;
        return false;
    }
    else
    {
        ablak = SDL_CreateWindow( "Projekt Labor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, S_W, S_H, /*SDL_WINDOW_FULLSCREEN*/ SDL_WINDOW_SHOWN);
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
                if (LoadMedia() == false)
                {
                    cout << "A fájlok betöltése sikertelen!" << endl;
                    return false;
                }
            }
        }
    }
    return true;
}

bool Graphics::LoadMedia()
{
    SDL_Texture* Talaj =LoadTexture( "talaj.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("Talaj",Talaj));
    
    SDL_Texture* YellowTile =LoadTexture( "yellow.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("YellowTile",YellowTile));
    
    SDL_Texture* RedTile =LoadTexture( "red.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("RedTile",RedTile));
    
    SDL_Texture* BlueTile =LoadTexture( "blue.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("BlueTile",BlueTile));
    
    SDL_Texture* Selection =LoadTexture( "template.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("Selection",Selection));
    
    SDL_Texture* CircleTexture =LoadTexture( "circle.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("CircleTexture",CircleTexture));
    
    SDL_Texture* CircleTexture_grey =LoadTexture( "circle_grey.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("CircleTexture_grey",CircleTexture_grey));
    
    SDL_Texture* RedCircleTexture =LoadTexture( "red_circle_texture.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("RedCircleTexture",RedCircleTexture));
    
    SDL_Texture* YellowCircleTexture =LoadTexture( "yellow_circle_texture.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("YellowCircleTexture",YellowCircleTexture));
    
    SDL_Texture* BlueCircleTexture =LoadTexture( "blue_circle_texture.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("BlueCircleTexture",BlueCircleTexture));

    SDL_Texture* PurpleCircleTexture =LoadTexture( "purple_circle_texture.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("PurpleCircleTexture",PurpleCircleTexture));
    
    SDL_Texture* GreenCircleTexture =LoadTexture( "green_circle_texture.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("GreenCircleTexture",GreenCircleTexture));
    
    SDL_Texture* OrangeCircleTexture =LoadTexture( "orange_circle_texture.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("OrangeCircleTexture",OrangeCircleTexture));
    
    SDL_Texture* BrownCircleTexture =LoadTexture( "brown_circle_texture.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("BrownCircleTexture",BrownCircleTexture));
    
    SDL_Texture* WhiteCircleTexture =LoadTexture( "white_circle_texture.bmp" );
    Textures.insert(pair<string,SDL_Texture*>("WhiteCircleTexture",WhiteCircleTexture));
    
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

SDL_Texture* Graphics::LoadTexture(string path)
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
