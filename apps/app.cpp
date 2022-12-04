#include "MySDL.hpp"

int main() {
  auto sdl = std::make_shared<HF::MySDL>();
  sdl->CreateWindow("demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                   640, 480, 0);
  sdl->LoadOrChangeMediaSurface(
      "/home/eric/code/SDLTutorial/asset/hello_world.bmp");
  sdl->RegisterEvent(SDL_QUIT, [](const std::shared_ptr<HF::MySDL> &mysdl) {
    mysdl->LoadOrChangeMediaSurface(
        "/home/eric/code/SDLTutorial/asset/exit.bmp");
    mysdl->StopLoop();
  });
  sdl->LoopAndWaitEvent();
  sdl->Delay(500);
  /* MySDL应该提供接口: 关注的事件和对应的回调 */
  return 0;
}