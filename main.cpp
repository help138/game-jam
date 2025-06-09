#define SDL_MAIN_USE_CALLBACKS 1
#include <time.h>
#include <stdio.h>
// #include <stdlib.h>
#include "include/SDL.h"
#include "include/SDL_main.h"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HIGHT 480

int wind_width = DEFAULT_WINDOW_WIDTH;
int wind_hight = DEFAULT_WINDOW_HIGHT;

SDL_Window* wind = NULL;
SDL_Renderer* render = NULL;
SDL_Texture* texture = NULL;

void clouds(unsigned scale){
  SDL_srand(time(NULL) ^ SDL_GetTicksNS());
  int len = SDL_rand(scale);

  SDL_CreateTexture(render, 0, SDL_TEXTUREACCESS_TARGET, wind_width, wind_hight);  
  for (int i = 0; i < len; i++){
    SDL_rand(scale);
  }
  
  
}
void draw(){
  
}
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  SDL_CreateWindowAndRenderer("callback demo", wind_width, wind_hight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OCCLUDED | SDL_WINDOW_MAXIMIZED /*| SDL_WINDOW_MOUSE_GRABBED | SDL_WINDOW_FULLSCREEN*/, &wind, &render);
  SDL_srand(time(NULL));
  
  if (wind == NULL){
    printf("failed to create window: %s\n", SDL_GetError());
    return SDL_APP_FAILURE; 
  }
  if (render == NULL){
    printf("failed to render: %s\n", SDL_GetError());
    return SDL_APP_FAILURE; 
  }

  return SDL_APP_CONTINUE; 
}
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
  switch (event->type){
    case SDL_EVENT_QUIT:
        return SDL_APP_SUCCESS;
    case SDL_EVENT_KEY_DOWN:
      if (event->key.key == SDLK_ESCAPE || event->key.key == SDLK_Q){
        return SDL_APP_SUCCESS;
      }
      if (event->key.key == SDLK_D){
        // SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "debug box", "debug box", wind);
      }
      if (event->key.key == SDLK_T){
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "test", "this is a test", wind);
      }
          break;
    case SDL_EVENT_WINDOW_RESIZED:
      wind_width = event->window.data1;
      wind_hight = event->window.data2;
        break;
    default:
        return SDL_APP_CONTINUE;
  }
  return SDL_APP_CONTINUE; 
}
SDL_AppResult SDL_AppIterate(void *appstate){

  draw();
  SDL_RenderPresent(render); 

  return SDL_APP_CONTINUE;
}
void SDL_AppQuit(void *appstate, SDL_AppResult result){
  //SDL will handle most of the cleanup
}