#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include "Screen.h"
#include "Screen.cpp"
#include "Swarm.h"
#include "Swarm.cpp"
#include "Particle.h"
#include "Particle.cpp"


int main(int argc, char* argv[]){

    srand(time(NULL));

    Screen screen;
    if(screen.init() == false){
        std::cout<<"SDL2 initialization failed..."<<std::endl;
    }

    Swarm swarm;
    const double speed = 0.05;

    while(true){
        int elapsed = SDL_GetTicks();//color animation
        unsigned char green = (unsigned char) ((1 + sin(elapsed * 0.0001)) * 128);
		unsigned char red = (unsigned char) ((1 + sin(elapsed * 0.0002)) * 128);
		unsigned char blue = (unsigned char) ((1 + sin(elapsed * 0.0003)) * 128);
        swarm.update(elapsed);




        const Particle * const pParticles = swarm.getParticles();
        for(int i=0; i <Swarm::NPARTICLES;i++) {
            Particle particle = pParticles[i];
            int x = (particle.m_x + 1) * Screen::WIDTH/2;
            int y = particle.m_y * Screen::WIDTH/2 + Screen::HEIGHT/2;
            screen.setPixel(x,y,red,green,blue);      
        }

        if(screen.processEvents() == false){
            break;
        }
        screen.boxBlur();
        screen.update();
    }   
    screen.close();
    return EXIT_SUCCESS;
}