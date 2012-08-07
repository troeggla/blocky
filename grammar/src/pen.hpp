#ifndef pen_hpp
#define pen_hpp

#include <utility>
#include <math.h>
#include <sstream>

#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"

#include "exceptions.hpp"

#define PI 3.141592653589793238

class Pen {
    SDL_Surface *screen;
    std::pair<double, double> position;
    double direction;

    bool window_active;
    double delay;
    int red, green, blue;

    double toRadians(double);
    double getNewX(double);
    double getNewY(double);

    static Pen *inst;

    Pen();
public:
    static Pen *instance();
    ~Pen();

    void setColor(int, int, int);
    void move(double);
    void drawLine(double);
    void gotoXY(int, int);
    void setDirection(double);
    void setDelay(double);
    void turn(double);
    void lineTo(double, double);
    void close_listener();
};

#endif
