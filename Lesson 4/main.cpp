#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <cstdio>
#include <iostream>

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces {//key press surfaces constants

    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window *gWindow = NULL;//window we are rendering to
SDL_Surface *gScreenSurface = NULL;//the surface contained by the window
SDL_Surface *gCurrentSuface = NULL;//currently displayed image
SDL_Surface *gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL];//the imags that correspond to a keypress

bool init() {//start up sdl and create window

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

void close() {//frees media and shuts down sdl

    //deallocate surface
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
        SDL_FreeSurface(gKeyPressSurface[i]);
        gKeyPressSurface[i] = NULL;
    }

    //destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //quit sdl
    SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {//load individual image
    
    //load image at specified path
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    return loadedSurface;
}

bool loadMedia() {//load media

    //loading success flag
    bool success = true;

    //load default surface
    gKeyPressSurface [KEY_PRESS_SURFACE_DEFAULT] = loadSurface("./press.bmp");
    if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        printf("Failed to load default image.\n");
        success = false;
    }
    
    //load up surface
    gKeyPressSurface [KEY_PRESS_SURFACE_UP] = loadSurface("./up.bmp");
    if (gKeyPressSurface[KEY_PRESS_SURFACE_UP] == NULL) {
        printf("Failed to load up image.\n");
        success = false;
    }

    //load down surface
    gKeyPressSurface [KEY_PRESS_SURFACE_DOWN] = loadSurface("./down.bmp");
    if (gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] == NULL) {
        printf("Failed to load down image.\n");
        success = false;
    }
    
    //load left surface
    gKeyPressSurface [KEY_PRESS_SURFACE_LEFT] = loadSurface("./left.bmp");
    if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL) {
        printf("Failed to load left image.\n");
        success = false;
    }

    //load right surface
    gKeyPressSurface [KEY_PRESS_SURFACE_RIGHT] = loadSurface("./right.bmp");
    if (gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        printf("Failed to load right image.\n");
        success = false;
    }

    return success;
}

int main(int argc, char *argv[]) {

    //start sdl and create window
    if (!init()) {
        printf("Failed to initialize\n");
    }
    else {
        if (!loadMedia()) {
            printf("Failed to load media\n");
        }
        else {
            //main loop flag
            bool quit = false;
            
            //event handler
            SDL_Event e;
            
            //set default current surface
            gCurrentSuface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
            
            //while application is running
            while (!quit) {
                
                //handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    
                    //if user requests exit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    //user presses a key
                    else if (e.type == SDL_KEYDOWN) {
                        //select surfaces based on key press
                        switch(e.key.keysym.sym) {
                            
                        case SDLK_UP:
                            gCurrentSuface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
                            break;
                            
                        case SDLK_DOWN:
                            gCurrentSuface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
                            break;
                            
                        case SDLK_LEFT: gCurrentSuface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
                            break;
                            
                        case SDLK_RIGHT:
                            gCurrentSuface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
                            break;
                            
                        default:
                            gCurrentSuface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                        }
                    }
                }
                
                //apply the current image
                SDL_BlitSurface(gCurrentSuface, NULL, gScreenSurface, NULL);
                
                //update window
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
        
    //free resources and close sdl
    close();

    return 0;
}
