#include "pen.hpp"

Pen* Pen::inst = 0;

Pen* Pen::instance() {
    if (inst == 0) {
        inst = new Pen();
    }

    return inst;
}

Pen::Pen() {
    this->window_active = false;
    this->direction = 0;
    this->delay = 0;
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

double Pen::toRadians(double degree) {
    return ((double)degree) * PI/180;
}

double Pen::getNewX(double len) {
    double rad = this->toRadians(this->direction);
    double line_len = cos(rad) * len;

    return this->position.first + line_len;
}

double Pen::getNewY(double len) {
    double rad = this->toRadians(this->direction);
    double line_len = sin(rad) * len;

    return this->position.second + line_len;
}

void Pen::setColor(int r, int g, int b) {
    std::stringstream s;

    if (r<0 || r>255) {
        s << r;
        throw IllegalValueException(s.str());
    }

    if (g<0 || g>255) {
        s << g;
        throw IllegalValueException(s.str());
    }

    if (b<0 || b>255) {
        s << b;
        throw IllegalValueException(s.str());
    }

    red = r;
    green = g;
    blue = b;
}

void Pen::setDelay(double delay) {
    if (delay < 0) {
        std::stringstream s;
        s << delay;

        throw IllegalValueException(s.str());
    }

    this->delay = delay;
}

void Pen::drawLine(double length) {
    double newX = this->getNewX(length);
    double newY = this->getNewY(length);

    lineRGBA(screen, 
             position.first, position.second, 
             newX, newY, 
             red, green, blue, 255);

    position.first = newX;
    position.second = newY;

    SDL_Delay(delay);
    SDL_Flip(screen);

    window_active = true;
}

void Pen::move(double length) {
    int newX = this->getNewX(length);
    int newY = this->getNewY(length);

    position.first = newX;
    position.second = newY;
}

void Pen::gotoXY(int x, int y) {
    position.first = x;
    position.second = y;
}

void Pen::turn(double degrees) {
    direction = direction + degrees;

    if (direction >= 360) {
        direction = direction - 360;
    }
}

void Pen::setDirection(double direction) {
    this->direction = direction;
}

void Pen::close_listener() { 
    if (!window_active) {
        return;
    }

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
