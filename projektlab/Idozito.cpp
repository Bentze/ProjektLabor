#include "Idozito.h"

Idozito::Idozito()
{
    megy = false;
    Szunetel = false;
    KezdoIdo = 0;
    MegallitottIdo = 0;
}

void Idozito::start()
{
    megy = true;
    Szunetel = false;
    KezdoIdo = SDL_GetTicks();
}

void Idozito::stop()
{
    megy = false;
    Szunetel = false;
    KezdoIdo = 0;
    MegallitottIdo = 0;
}

void Idozito::szunet()
{
    if (megy and !Szunetel)
    {
        Szunetel = true;
        MegallitottIdo = SDL_GetTicks() - KezdoIdo;
        KezdoIdo = 0;
    }
}

void Idozito::ujraindit()
{
    if(megy and Szunetel)
    {
        Szunetel = false;
        KezdoIdo = SDL_GetTicks() - MegallitottIdo;
        MegallitottIdo = 0;
    }
}

Uint32 Idozito::ido()
{
    if(megy)
    {
        if(Szunetel)
        {
            return MegallitottIdo;
        }
        else
        {
            return SDL_GetTicks() - KezdoIdo;
        }
    }
    return 0;
}

bool Idozito::elinditva()
{
    return megy;
}

bool Idozito::szunetel()
{
    return Szunetel;
}
