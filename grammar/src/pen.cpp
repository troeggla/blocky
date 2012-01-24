#include "pen.hpp"

Pen* Pen::inst = 0;

Pen* Pen::instance() {
    if (inst == 0) {
        inst = new Pen();
    }

    return inst;
}

Pen::Pen() {
    this->direction = 0;
    this->position = std::make_pair(0, 0);

    red = 255;
    green = 255;
    blue = 255;

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(640, 480, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetCaption("Blocky - Graphical Interface", 0);
}

Pen::~Pen() {
    SDL_FreeSurface(screen);
    SDL_Quit();
}

double Pen::toRadians(int degree) {
    return ((double)degree) * PI/180;
}

double Pen::getNewX(int angle, int len) {
    double rad = this->toRadians(angle);
    double line_len = cos(rad) * len;

    return this->position.first + line_len;
}

double Pen::getNewY(int angle, int len) {
    double rad = this->toRadians(angle);
    double line_len = sin(rad) * len;

    return this->position.second + line_len;
}

void Pen::setColor(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
}

void Pen::drawLine(int length) {
    int newX = this->getNewX(this->direction, length);
    int newY = this->getNewY(this->direction, length);

    lineRGBA(screen, 
             position.first, position.second, 
             newX, newY, 
             red, green, blue, 255);

    position.first = newX;
    position.second = newY;
}

void Pen::gotoXY(int x, int y) {
    position.first = x;
    position.second = y;
}

void Pen::turn(int degrees) {
    direction = direction + degrees;

    if (direction >= 360) {
        direction = direction - 360;
    }
}

void Pen::setDirection(int direction) {
    this->direction = direction;
}

void Pen::update() {
    SDL_Flip(screen);
    
    SDL_Event event;
    while (true) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                return;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE || 
                    event.key.keysym.sym == SDLK_q) {
                    return;
                }
            }
        }
    }
}
