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
    auto key = event.key.keysym.sym;
    if (key == SDLK_UP) {
      mysdl->LoadOrChangeMediaToTexture(
          "/home/eric/code/SDLTutorial/asset/viewport.png");
      SDL_Rect topLeftViewport{
          .x = 0, .y = 0, .w = weight / 2, .h = height / 2};
      SDL_RenderSetViewport(mysdl->getRendererPtr(),
                            std::addressof(topLeftViewport));
      SDL_RenderClear(mysdl->getRendererPtr());
      SDL_RenderCopy(mysdl->getRendererPtr(), mysdl->getTexturePtr(), nullptr,
                     nullptr);
      SDL_RenderPresent(mysdl->getRendererPtr());
    } else if (key == SDLK_DOWN) {

    } else if (key == SDLK_LEFT) {

    } else if (key == SDLK_RIGHT) {

    } else {
      mysdl->LoadOrChangeMediaToTexture(
          "/home/eric/code/SDLTutorial/asset/loaded.png");
      mysdl->DisplayTexture();
    }
  });

  sdl->LoopAndWaitEvent();
  return 0;
}