#include "MySDL.hpp"

int main() {
  constexpr static int weight = 640;
  constexpr static int height = 480;
  auto sdl = std::make_shared<HF::MySDL>();
  sdl->CreateWindow("demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    weight, height, 0);
  sdl->RegisterEvent(SDL_QUIT, [](const std::shared_ptr<HF::MySDL> &mysdl,
                                  const SDL_Event &event) {
    mysdl->LoadOrChangeMediaSurfaceWithConvert(
        "/home/eric/code/SDLTutorial/asset/exit.bmp");
    mysdl->UpdateSurface();
    mysdl->StopLoop();
  });

  sdl->RegisterEvent(SDL_KEYDOWN, [](const std::shared_ptr<HF::MySDL> &mysdl,
                                     const SDL_Event &event) {
    switch (event.key.keysym.sym) {
    case SDLK_UP:
      mysdl->LoadOrChangeMediaSurfaceWithConvert(
          "/home/eric/code/SDLTutorial/asset/up.bmp");
      break;
    case SDLK_DOWN:
      mysdl->LoadOrChangeMediaSurfaceWithConvert(
          "/home/eric/code/SDLTutorial/asset/down.bmp");
      break;
    case SDLK_LEFT:
      mysdl->LoadOrChangeMediaSurfaceWithConvert(
          "/home/eric/code/SDLTutorial/asset/left.bmp");
      break;
    case SDLK_RIGHT:
      mysdl->LoadOrChangeMediaSurfaceWithConvert(
          "/home/eric/code/SDLTutorial/asset/right.bmp");
      break;
    default:
      mysdl->LoadOrChangeMediaSurfaceWithConvert(
          "/home/eric/code/SDLTutorial/asset/press.bmp");
      break;
    }
    mysdl->ScaledSurface(0, 0, weight, height);
  });

  sdl->LoopAndWaitEvent();
  return 0;
}