#include <cstddef>
#include <cstdio>
#include <iostream>

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloWorld = NULL;

bool init() {

    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }
    else {
        gWindow = SDL_CreateWindow("SDL Tutorial",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Windowcould not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            //get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia() {

    bool success = true;

    //load splash image
    gHelloWorld = SDL_LoadBMP("./hello_world.bmp");
    if (gHelloWorld == NULL) {
        printf("Unable to lead image: %s! SDL Error: %s\n", "./hello_world.bmp", SDL_GetError());
        success = false;
    }
    return success;
}

void close() {

    //deallocate surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    //destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //quit sdl
    SDL_Quit();
}

int main(int argc, char *argv[]) {

    //start sdl and create window
    if (!init()) {
        printf("Failed to initialize\n");
    }
    else {
        //load media
        if (!loadMedia()) {
            printf("Failed to load media\n");
        }
        else {
            //apply the image
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

            //update surface
            SDL_UpdateWindowSurface(gWindow);


            //hack to keep window open
            SDL_Event e;
            bool quit = false;

            while (quit == false) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
            }
        }
    }

    //free resources and close sdl
    close();

    return 0;
}
