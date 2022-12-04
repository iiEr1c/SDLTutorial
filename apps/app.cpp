#include "MySDL.hpp"

int main() {
  constexpr static int weight = 640;
  constexpr static int height = 480;
  auto sdl = std::make_shared<HF::MySDL>();
  sdl->CreateWindow("demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    weight, height, 0);
  sdl->CreateRenderer();
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
      mysdl->LoadOrChangeMediaToTexture(
          "/home/eric/code/SDLTutorial/asset/texture.png");
      break;
    case SDLK_DOWN:
      mysdl->LoadOrChangeMediaToTexture(
          "/home/eric/code/SDLTutorial/asset/texture.png");
      break;
    case SDLK_LEFT:
      mysdl->LoadOrChangeMediaToTexture(
          "/home/eric/code/SDLTutorial/asset/texture.png");
      break;
    case SDLK_RIGHT:
      mysdl->LoadOrChangeMediaToTexture(
          "/home/eric/code/SDLTutorial/asset/texture.png");
      break;
    default:
      mysdl->LoadOrChangeMediaToTexture(
          "/home/eric/code/SDLTutorial/asset/loaded.png");
      break;
    }

    mysdl->UpdateTexture();
  });

  sdl->LoopAndWaitEvent();
  return 0;
}