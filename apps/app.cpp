#include "Button.hpp"
#include "MySDL.hpp"
#include "MySDLMixer.hpp"
#include "MySDLMusic.hpp"
#include "PictureTexture.hpp"
#include "SDL.h"
#include "TTFFontTexture.hpp"
#include "TextureMessenger.hpp"

#include <vector>

int main() {
  constexpr static int width = 640;
  constexpr static int height = 480;
  auto sdl = std::make_shared<HF::MySDL>(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  sdl->CreateWindow("demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                    width, height, SDL_WINDOW_SHOWN);
  sdl->CreateRenderer(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  constexpr int fontSize = 28;
  sdl->CreateTTFFont("/home/eric/code/SDLTutorial/asset/lazy.ttf", fontSize);
  sdl->RegisterEvent(SDL_QUIT, [](const std::shared_ptr<HF::MySDL> &mysdl,
                                  const SDL_Event &event) {
    auto exitTexture = HF::TextureMessenger(
        HF::PictureTexture(mysdl->getRendererSharedPtr(),
                           "/home/eric/code/SDLTutorial/asset/exit.png"));
    constexpr int topLeftX = 0;
    constexpr int topLeftY = 0;
    exitTexture.render(topLeftX, topLeftY);
    SDL_RenderPresent(mysdl->getRendererPtr());
    mysdl->Delay(500);
    mysdl->StopLoop();
  });

  /* use SDL_GetKeyboardState */
  std::move_only_function<void()> combineKeyboardCallback = []() {
    const uint8_t *currentKeyStates = SDL_GetKeyboardState(nullptr);
    /* check ctrl + C */
    if (currentKeyStates[SDL_SCANCODE_LCTRL] &&
        currentKeyStates[SDL_SCANCODE_C]) {
      fmt::print("ctrl + C combine\n");
    }
  };
  sdl->addPeerLoopTask(std::move(combineKeyboardCallback));

  auto wifiButton =
      HF::Button(sdl->getRendererSharedPtr(),
                 "/home/eric/code/SDLTutorial/asset/wifiButton.png", 100, 100);
  wifiButton.render();
  SDL_RenderPresent(sdl->getRendererPtr());
  /* mouse event */
  sdl->RegisterEvent(
      SDL_MOUSEBUTTONDOWN, [wifiButton = std::move(wifiButton)](
                               const std::shared_ptr<HF::MySDL> &mysdl,
                               const SDL_Event &event) mutable {
        wifiButton.render();
        int curPosX = 0, curPosY = 0;
        SDL_GetMouseState(&curPosX, &curPosY);
        auto [posX, posY] = wifiButton.getPosition();
        auto [imgWidth, imgHeight] = wifiButton.getButtonImgAttr();
        if (curPosX >= posX && curPosX <= posX + imgWidth && curPosY >= posY &&
            curPosY <= posY + imgHeight) {
          fmt::print("curPos:[{}, {}], buttonPos[{},{}], imgAttr[{},{}]\n",
                     curPosX, curPosY, posX, posY, imgWidth, imgHeight);
        }
      });

  /* music & 键盘事件 */
  auto music =
      HF::MySDLMusic("/home/eric/code/SDLTutorial/asset/audio/beat.wav");
  auto lowChunk =
      HF::MySDLMixer("/home/eric/code/SDLTutorial/asset/audio/low.wav");
  auto highChunk =
      HF::MySDLMixer("/home/eric/code/SDLTutorial/asset/audio/high.wav");
  auto scratchChunk =
      HF::MySDLMixer("/home/eric/code/SDLTutorial/asset/audio/scratch.wav");
  auto mediumChunk =
      HF::MySDLMixer("/home/eric/code/SDLTutorial/asset/audio/medium.wav");
  sdl->RegisterEvent(
      SDL_KEYDOWN,
      [music = std::move(music), lowChunk = std::move(lowChunk),
       highChunk = std::move(highChunk), scratchChunk = std::move(scratchChunk),
       mediumChunk = std::move(mediumChunk)](
          const std::shared_ptr<HF::MySDL> &mysdl, const SDL_Event &event) {
        auto key = event.key.keysym.sym;
        if (key == SDLK_1) {
          highChunk.play();
        } else if (key == SDLK_2) {
          mediumChunk.play();
        } else if (key == SDLK_3) {
          lowChunk.play();
        } else if (key == SDLK_4) {
          scratchChunk.play();
        } else if (key == SDLK_9) {
          // if there is no music playing
          fmt::print("Mix_PlayingMusic = {}\n", Mix_PlayingMusic());
          if (Mix_PlayingMusic() == 0) {
            music.play(50);
          } else {
            // pause music
            if (Mix_PausedMusic() == 1) {
              Mix_ResumeMusic();
            } else {
              fmt::print("Mix_PausedMusic() = {}\n", Mix_PausedMusic());
              Mix_PauseMusic();
            }
          }
        } else if (key == SDLK_0) {
          Mix_HaltMusic();
        }
      });

  sdl->LoopAndWaitEvent();
  return 0;
}