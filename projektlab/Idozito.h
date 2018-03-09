#ifndef IDOZITO_H
#define IDOZITO_H

#include <SDL.h>

class Idozito
{
    public:
        Idozito();

        void start();
        void stop();
        void szunet();
        void ujraindit();

        Uint32 ido();

        bool elinditva();
        bool szunetel();

    private:
        Uint32 KezdoIdo;
        Uint32 MegallitottIdo;

        bool megy;
        bool Szunetel;
};

#endif // IDOZITO_H
