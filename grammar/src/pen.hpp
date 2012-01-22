#ifndef pen_hpp
#define pen_hpp

#include <utility>
#include <math.h>

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

#define PI 3.141592653589793238

class Pen {
    SDL_Surface *screen;
    std::pair<int, int> position;
    int direction;

    double toRadians(int);
    double getNewX(int, int);
    double getNewY(int, int);

    static Pen *inst;

    Pen();
public:
    static Pen *instance();
    ~Pen();

    void drawLine(int);
    void gotoXY(int, int);
    void turn(int);
    void update();
};

#endif