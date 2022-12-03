#include "MySDL.hpp"

int main() {
  HF::MySDL sdl;
  sdl.CreateWindow("demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                   640, 480, 0);
  sdl.Delay(3000);
  return 0;
}