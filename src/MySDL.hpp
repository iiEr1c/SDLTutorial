#pragma once

#include "SDL.h"

#include "MySDLSurface.hpp"
#include "MySDLWindow.hpp"

#include <atomic>
#include <memory>
#include <string>

namespace HF {
class MySDL {
  MySDLWindow m_window;
  MySDLSurface m_surface;
  
  std::atomic_flag quit = false;

public:
  MySDL(uint32_t initType = SDL_INIT_VIDEO);
  ~MySDL();

  MySDL(const MySDL &) = delete;
  MySDL &operator=(const MySDL &) = delete;

  void CreateWindow(const char *title, int xPos, int yPos, int weight,
                    int height, uint32_t flags);

  /* 依赖于内部的m_window != nullptr */
  void LoadMediaToWindowSurface(const std::string &);

  static void Delay(int timeMS);

  void loopAndWaitEvent();
};
}; // namespace HF