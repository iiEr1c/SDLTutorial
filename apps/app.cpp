#include "MySDL.hpp"

int main() {
  constexpr int weight = 640;
  constexpr int height = 480;
  auto sdl = std::make_shared<HF::MySDL>();
  sdl->CreateWindow("demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    weight, height, 0);
  sdl->RegisterEvent(SDL_QUIT, [](const std::shared_ptr<HF::MySDL> &mysdl,
                                  const SDL_Event &event) {
    mysdl->LoadOrChangeMediaSurface(
        "/home/eric/code/SDLTutorial/asset/exit.bmp");
    mysdl->StopLoop();
  });

  sdl->RegisterEvent(SDL_KEYDOWN, [](const std::shared_ptr<HF::MySDL> &mysdl,
                                     const SDL_Event &event) {
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      mysdl->LoadOrChangeMediaSurface(
          "/home/eric/code/SDLTutorial/asset/up.bmp");
      break;
    case SDLK_DOWN:
      mysdl->LoadOrChangeMediaSurface(
          "/home/eric/code/SDLTutorial/asset/down.bmp");
      break;
    case SDLK_LEFT:
      mysdl->LoadOrChangeMediaSurface(
          "/home/eric/code/SDLTutorial/asset/left.bmp");
      break;
    case SDLK_RIGHT:
      mysdl->LoadOrChangeMediaSurface(
          "/home/eric/code/SDLTutorial/asset/right.bmp");
      break;
    default:
      mysdl->LoadOrChangeMediaSurface(
          "/home/eric/code/SDLTutorial/asset/press.bmp");
      break;
    }
  });

  sdl->LoopAndWaitEvent();
  return 0;
}