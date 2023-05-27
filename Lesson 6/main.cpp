#include <cstddef>
#include <cstdio>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gPNGSurface = NULL;

bool init();
bool loadMedia();
void close();
SDL_Surface *loadSurface(std::string path);

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
            //initialize png loding
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) &imgFlags)) {
                printf("SDL_image coulse not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else {
            //get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }

    return success;
}

bool loadMedia() {

    //loading success flag
    bool success = true;

    //load splash image
    gPNGSurface = loadSurface("./loaded.png");
    if (gPNGSurface == NULL) {
        printf("Failed to load PNG image\n");
        success = false;
    }
    return success;
}

void close() {

    //deallocate surface
    SDL_FreeSurface(gPNGSurface);
    gPNGSurface = NULL;

    //destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //quit sdl
    IMG_Quit();
    SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {//load individual image
    
    //the final optimized image
    SDL_Surface *optimizedSurface = NULL;

    //load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s. SDL_image Error: %s\n", path.c_str(), IMG_GetError());
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

                //apply the PNG image
                SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);
                
                //update window
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }
        
    //free resources and close sdl
    close();

    return 0;
}
