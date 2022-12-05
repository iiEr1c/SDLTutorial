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
    mysdl->Display();
    mysdl->StopLoop();
  });

  sdl->RegisterEvent(SDL_KEYDOWN, [](const std::shared_ptr<HF::MySDL> &mysdl,
                                     const SDL_Event &event) {
    auto key = event.key.keysym.sym;
    if (key == SDLK_UP) {
      auto texture = mysdl->LoadOrChangeMediaToTextureWithColorKey(
          "/home/eric/code/SDLTutorial/asset/foo.png", {0, 0xff, 0xff});
      texture.render(240, 190);
    } else if (key == SDLK_DOWN) {

    } else if (key == SDLK_LEFT) {

    } else if (key == SDLK_RIGHT) {

    } else {
      auto texture = mysdl->LoadOrChangeMediaToTexture(
          "/home/eric/code/SDLTutorial/asset/background.png");
      texture.render(0, 0);
    }

    SDL_RenderPresent(mysdl->getRendererPtr());
  });

  sdl->LoopAndWaitEvent();
  return 0;
}