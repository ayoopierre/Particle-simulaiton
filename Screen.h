#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <iostream>
#include <SDL2/SDL.h>
class Screen {
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture; 
    Uint32 *m_buffer;
    Uint32 *m_buffer2; 
public:
    const static int WIDTH = 800;
    const static int HEIGHT = 600;
    Screen();
    bool init();
    bool processEvents();
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void setBigPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void setBiggerPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void update();
    void boxBlur();
    void clear();
    void close();
};
#endif