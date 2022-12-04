#include "SDL.h"
#include <fmt/core.h>

#include "MySDL.hpp"

namespace HF {
MySDL::MySDL(uint32_t initType) { SDL_Init(initType); }

MySDL::~MySDL() { SDL_Quit(); }

void MySDL::CreateWindow(const char *title, int xPos, int yPos, int weight,
                         int height, uint32_t flags) {
  m_window = MySDLWindow(title, xPos, yPos, weight, height, flags);
}

void MySDL::Delay(int timeMS) { SDL_Delay(timeMS); }

void MySDL::LoadMediaToWindowSurface(const std::string &path) {
  m_surface = MySDLSurface(path);
  if (!m_surface.available()) {
    fmt::print("cann't load {} file\n", path);
  }

  if (m_window.available()) [[likely]] {
    SDL_BlitSurface(m_surface.getSurfacePtr(), nullptr,
                    SDL_GetWindowSurface(m_window.getWindowPtr()), nullptr);
    SDL_UpdateWindowSurface(m_window.getWindowPtr());
  } else {
    fmt::print("SDL window isn't initial\n");
  }
}

void MySDL::loopAndWaitEvent() {
  while (!quit.test()) {
    
  }
}

}; // namespace HF