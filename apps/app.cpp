#include "MySDL.hpp"
#include "PictureTexture.hpp"
#include "SDL.h"
#include "TTFFontTexture.hpp"
#include "TextureMessenger.hpp"

#include <vector>

int main() {
  constexpr static int width = 640;
  constexpr static int height = 480;
  auto sdl = std::make_shared<HF::MySDL>();
  sdl->CreateWindow("demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    width, height, SDL_WINDOW_SHOWN);
  sdl->CreateRenderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  constexpr int fontSize = 28;
  sdl->CreateTTFFont("/home/eric/code/SDLTutorial/asset/lazy.ttf", fontSize);
  sdl->RegisterEvent(SDL_QUIT, [](const std::shared_ptr<HF::MySDL> &mysdl,
                                  const SDL_Event &event) {
    mysdl->LoadOrChangeMediaSurfaceWithConvert(
        "/home/eric/code/SDLTutorial/asset/exit.bmp");
    mysdl->UpdateSurface();
    mysdl->Display();
    mysdl->StopLoop();
  });

  /* 带额外状态的回调 */
  auto background = HF::TextureMessenger(
      HF::PictureTexture(sdl->getRendererSharedPtr(),
                         "/home/eric/code/SDLTutorial/asset/background.png"));

  std::tuple<uint8_t, uint8_t, uint8_t> ignoreCyan = {0, 0xff, 0xff};
  auto SpritesTexture = HF::TextureMessenger(HF::PictureTexture(
      sdl->getRendererSharedPtr(), "/home/eric/code/SDLTutorial/asset/foo.png",
      ignoreCyan));

  SDL_Color textColor = {0, 0, 0};
  auto textTexture = HF::TextureMessenger(HF::TTFFontTexture(
      sdl->getRendererSharedPtr(), sdl->getTTFFontSharedPtr(), "Hello World!",
      textColor));

  constexpr int gapPixel = 64;
  constexpr int heightPixel = 205;
  std::vector<SDL_Rect> frame = {{0, 0, gapPixel, heightPixel},
                                 {gapPixel, 0, gapPixel, heightPixel},
                                 {gapPixel * 2, 0, gapPixel, heightPixel},
                                 {gapPixel * 3, 0, gapPixel, heightPixel}};
  int animationIndex = 0;
  sdl->RegisterEvent(
      SDL_KEYDOWN,
      [background = std::move(background),
       SpritesTexture = std::move(SpritesTexture),
       textTexture = std::move(textTexture), frame = std::move(frame),
       animationIndex = animationIndex](const std::shared_ptr<HF::MySDL> &mysdl,
                                        const SDL_Event &event) mutable {
        animationIndex++;
        animationIndex %= 4;
        constexpr int topLeftX = 0;
        constexpr int topLeftY = 0;
        auto key = event.key.keysym.sym;
        if (key == SDLK_UP) {
          SDL_RenderClear(mysdl->getRendererPtr());
          background.render(topLeftX, topLeftY);
          SpritesTexture.render(width / 2, 0, frame.data() + animationIndex);
        } else if (key == SDLK_DOWN) {
          SDL_RenderClear(mysdl->getRendererPtr());
          background.render(topLeftX, topLeftY);
          SpritesTexture.render(width / 2, height / 2,
                                frame.data() + animationIndex);
        } else if (key == SDLK_LEFT) {
          SDL_RenderClear(mysdl->getRendererPtr());
          background.render(topLeftX, topLeftY);
          textTexture.render(320, 240);
        } else if (key == SDLK_RIGHT) {

        } else {
          background.render(topLeftX, topLeftY);
        }

        SDL_RenderPresent(mysdl->getRendererPtr());
      });

  sdl->LoopAndWaitEvent();
  return 0;
}