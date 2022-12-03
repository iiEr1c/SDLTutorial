#include "SDL.h"
#include <fmt/core.h>

#include "MySDL.hpp"

namespace HF {
MySDL::MySDL(uint32_t initType) { SDL_Init(initType); }

MySDL::~MySDL() { SDL_Quit(); }

void MySDL::CreateWindow(const char *title, int x, int y, int w, int h,
                         uint32_t flags) {
  m_window = MySDLWindow(title, x, y, w, h, flags);
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

}; // namespace HF