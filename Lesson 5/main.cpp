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
SDL_Surface *gStretchedSurface = NULL;

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

    //free loaded image
    SDL_FreeSurface(gStretchedSurface);
    gStretchedSurface = NULL;

    //destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //quit sdl
    SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {//load individual image
    
    //the final optimized image
    SDL_Surface *optimizedSurface = NULL;

    //load image at specified path
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else {
        //convert surface to screen format 
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL) {
            printf("Unable to optimize image %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return optimizedSurface;
}

bool loadMedia() {//load media

    //loading success flag
    bool success = true;

    gStretchedSurface = loadSurface("./stretch.bmp");
    if (gStretchedSurface == NULL) {
        printf("Failed to load stretching image.\n");
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
            
            //while application is running
            while (!quit) {
                
                //handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    
                    //if user requests exit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                //apply the image stretched
                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = SCREEN_WIDTH;
                stretchRect.h = SCREEN_HEIGHT;
                SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);
                
                //update window
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
        
    //free resources and close sdl
    close();

    return 0;
}
