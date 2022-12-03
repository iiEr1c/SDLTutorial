#include "SDL.h"

#include "MySDL.hpp"

namespace HF {
MySDL::MySDL(uint32_t initType) : m_window{nullptr} { SDL_Init(initType); }

MySDL::~MySDL() { SDL_Quit(); }

void MySDL::CreateWindow(const char *title, int x, int y, int w, int h,
                         uint32_t flags) {
  m_window = std::make_unique<MySDLWindow>(title, x, y, w, h, flags);
}

void MySDL::Delay(int timeMS) { SDL_Delay(timeMS); }
}; // namespace HF