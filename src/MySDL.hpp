#pragma once

#include "SDL.h"

#include "MySDLWindow.hpp"

#include <memory>

namespace HF {
class MySDL {
  std::unique_ptr<MySDLWindow> m_window;

public:
  MySDL(uint32_t initType = SDL_INIT_VIDEO);
  ~MySDL();

  MySDL(const MySDL &) = delete;
  MySDL &operator=(const MySDL &) = delete;

  void CreateWindow(const char *title, int x, int y, int w, int h,
                    uint32_t flags);

  static void Delay(int timeMS);
};
}; // namespace HF