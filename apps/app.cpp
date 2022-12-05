#include "MySDL.hpp"

#include <vector>

int main() {
  constexpr static int weight = 640;
  constexpr static int height = 480;
  auto sdl = std::make_shared<HF::MySDL>();
  sdl->CreateWindow("demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    weight, height,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  sdl->CreateRenderer();
  sdl->RegisterEvent(SDL_QUIT, [](const std::shared_ptr<HF::MySDL> &mysdl,
                                  const SDL_Event &event) {
    mysdl->LoadOrChangeMediaSurfaceWithConvert(
        "/home/eric/code/SDLTutorial/asset/exit.bmp");
    mysdl->UpdateSurface();
    mysdl->Display();
    mysdl->StopLoop();
  });

  /* 带额外状态的回调 */
  auto background = std::make_shared<HF::MySDLTexture>(
      sdl->getRendererSharedPtr(),
      "/home/eric/code/SDLTutorial/asset/background.png");

  auto SpritesTexture = std::make_shared<HF::MySDLTexture>(
      sdl->getRendererSharedPtr(), "/home/eric/code/SDLTutorial/asset/foo.png",
      std::make_tuple(0, 0xff, 0xff));

  std::vector<SDL_Rect> frame = {
      {0, 0, 64, 205}, {64, 0, 64, 205}, {128, 0, 64, 205}, {192, 0, 64, 205}};
  int animationIndex = 0;
  sdl->RegisterEvent(
      SDL_KEYDOWN,
      [background = std::move(background), texture = std::move(SpritesTexture),
       frame = std::move(frame),
       animationIndex = animationIndex](const std::shared_ptr<HF::MySDL> &mysdl,
                                        const SDL_Event &event) mutable {
        animationIndex++;
        animationIndex %= 4;
        auto key = event.key.keysym.sym;
        if (key == SDLK_UP) {
          SDL_RenderClear(mysdl->getRendererPtr());
          background->render(0, 0);
          texture->render(288, 0, frame.data() + animationIndex);
        } else if (key == SDLK_DOWN) {
          SDL_RenderClear(mysdl->getRendererPtr());
          background->render(0, 0);
          texture->render(288, 295, frame.data() + animationIndex);
        } else if (key == SDLK_LEFT) {

        } else if (key == SDLK_RIGHT) {

        } else {
          auto color =
              HF::MySDLTexture(mysdl->getRendererSharedPtr(),
                               "/home/eric/code/SDLTutorial/asset/colors.png");
          color.setColor({128, 128, 128});
          color.setAlpha(128);
          color.render(0, 0);
        }

        SDL_RenderPresent(mysdl->getRendererPtr());
      });

  sdl->LoopAndWaitEvent();
  return 0;
}