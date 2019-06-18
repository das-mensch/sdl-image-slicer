#include "stdio.h"
#include "stdlib.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char** argv) {
  if (argc < 4) {
    printf("Usage: %s <filepath> <v-slice> <h-slice> [output-dir]\n", argv[0]);
    exit(1);
  }
  const char* filepath = argv[1];
  int vSlice = atoi(argv[2]);
  int hSlice = atoi(argv[3]);
  char* outputDir = "./";
  if (argc == 5) {
    outputDir = argv[4];
  }
  if (vSlice == 0 || hSlice == 0) {
    printf("Invalid number\n");
    exit(1);
  }
  int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
  if (SDL_Init(SDL_INIT_VIDEO) != 0 || IMG_Init(imgFlags) != imgFlags) {
    printf("%s\n", SDL_GetError());
    exit(1);
  }
  SDL_Surface* imageSurface = IMG_Load(filepath);
  if (!imageSurface) {
    printf("Error loading image '%s'\n", filepath);
    IMG_Quit();
    SDL_Quit();
    exit(1);
  }
  SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(imageSurface);
  if (!renderer) {
    printf("%s\n", SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    exit(1);
  }
  int tileWidth = imageSurface->w / vSlice;
  int tileHeight = imageSurface->h / hSlice;
  SDL_Rect sliceRect;
  sliceRect.x = 0;
  sliceRect.w = tileWidth;
  sliceRect.h = tileHeight;
  char buffer[255];
  size_t filepathLength = strlen(filepath);
  size_t newFilepathStemLength = (filepathLength - 4) * sizeof(char) + 1;
  char* newFilepathStem = (char*)malloc(newFilepathStemLength);
  memset((void*)newFilepathStem, 0, newFilepathStemLength);
  strncpy(newFilepathStem, filepath, (filepathLength - 4) * sizeof(char));
  SDL_Surface* blitSurface = SDL_CreateRGBSurface(imageSurface->flags, tileWidth, tileHeight, 32, 0, 0, 0, 0);
  int currentSlice = 0;
  for (int y = 0; y < hSlice; y++) {
    sliceRect.x = 0;
    for (int x = 0; x < vSlice; x++) {
      SDL_BlitSurface(imageSurface, &sliceRect, blitSurface, NULL);
      sprintf(buffer, "%s%s-%d.png", outputDir, newFilepathStem, currentSlice);
      IMG_SavePNG(blitSurface, buffer);
      currentSlice++;
      sliceRect.x += tileWidth;
    }
    sliceRect.y += tileHeight;
  }
  free(newFilepathStem);
  SDL_FreeSurface(blitSurface);
  SDL_FreeSurface(imageSurface);
  SDL_DestroyRenderer(renderer);
  exit(0);
}
