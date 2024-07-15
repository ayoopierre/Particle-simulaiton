#include "Screen.h"

Screen::Screen(): m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL), m_buffer2(NULL){

}

bool Screen::init() {
    SDL_Init(SDL_INIT_EVERYTHING);//SDL initialize

    m_window = SDL_CreateWindow("Particle explosion",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_ALLOW_HIGHDPI);
    if (NULL==m_window){
        std::cout << "Window error" << SDL_GetError() << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);//define renderer
    if (m_renderer == NULL) {
        std::cout << "Renderer error" << std::endl;
        SDL_Quit();
        return false;
    }

    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);//define texture
    if (m_texture == NULL){
        std::cout << "Texture error" << std::endl;
        SDL_Quit();
        return false;
    }

    m_buffer = new Uint32[WIDTH*HEIGHT];//define memory for each pixel( each in type Uint32)
    m_buffer2 = new Uint32[WIDTH*HEIGHT];
    memset(m_buffer, 0, WIDTH*HEIGHT*sizeof(Uint32));
    memset(m_buffer2, 0, WIDTH*HEIGHT*sizeof(Uint32));//memset - gives same value for all vars in memory set
    /*for (int i=0;i<HEIGHT*WIDTH;i++){
        m_buffer[i] = 0x123456ff;//hex, written in line 0x- cpp hex prefix, 00 -- FF, red green blue alpha
    }*/
    return true;
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
    if(x<0 or x>=Screen::WIDTH or y<0 or y>=Screen::HEIGHT){
        return;
    }
    Uint32 color = 0;
    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xff;
    m_buffer[(y * WIDTH) + x] = color;
}

void Screen::update(){
    SDL_UpdateTexture(m_texture, NULL, m_buffer, WIDTH*sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer,m_texture,NULL,NULL);
    SDL_RenderPresent(m_renderer);// render manipulating texture

}

bool Screen::processEvents() {
    SDL_Event event;//winodw event control
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            return false;
        }
    }
    return true;
}

void Screen::boxBlur(){
    Uint32 *temp = m_buffer;
    m_buffer = m_buffer2;
    m_buffer2 = temp;
    for(int y=0; y<HEIGHT; y++) {
		for(int x=0; x<WIDTH; x++) {

			int redTotal=0;
			int greenTotal=0;
			int blueTotal=0;

			for(int row=-1; row<=1; row++) {
				for(int col=-1; col<=1; col++) {
					int currentX = x + col;
					int currentY = y + row;

					if(currentX >= 0 && currentX < WIDTH && currentY >= 0 && currentY < HEIGHT) {
						Uint32 color = m_buffer2[currentY*WIDTH + currentX];

						Uint8 red = (color & 0xFF000000) >> 24;
						Uint8 green = (color & 0x00FF0000) >> 16;
						Uint8 blue = (color & 0x0000FF00) >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			Uint8 red = redTotal/9;
			Uint8 green = greenTotal/9;
			Uint8 blue = blueTotal/9;

			setPixel(x, y, red, green, blue);
		}
    }
}

void Screen::clear(){
    memset(m_buffer, 0, WIDTH*HEIGHT*sizeof(Uint32));
    memset(m_buffer2, 0, WIDTH*HEIGHT*sizeof(Uint32));
}

void Screen::close() {
    delete [] m_buffer;// clearing memory
    delete [] m_buffer2;
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Screen::setBigPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
    setPixel(x,y,red,green,blue);
    setPixel(x-1,y,red,green,blue);
    setPixel(x,y-1,red,green,blue);
    setPixel(x-1,y-1,red,green,blue);
}


void Screen::setBiggerPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
    setPixel(x,y,red,green,blue);
    setPixel(x-1,y,red,green,blue);
    setPixel(x+1,y,red,green,blue);
    setPixel(x,y-1,red,green,blue);
    setPixel(x-1,y-1,red,green,blue);
    setPixel(x+1,y-1,red,green,blue);
    setPixel(x,y+1,red,green,blue);
    setPixel(x-1,y+1,red,green,blue);
    setPixel(x+1,y+1,red,green,blue);
}