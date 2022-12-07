#include "MySDLRender.hpp"
#include "SDL_ttf.h"
#include <fmt/core.h>

#include <utility>

namespace HF {
MySDLRender::MySDLRender() {}

MySDLRender::MySDLRender(SDL_Window *window, uint32_t flag)
    : m_render{SDL_CreateRenderer(window, -1, flag)} {
  if (m_render != nullptr) {
    initRenderColor();
    initPNGLoading();
    initTTF();
  }
}

MySDLRender::~MySDLRender() {
  if (m_render != nullptr) {
    IMG_Quit();
    SDL_DestroyRenderer(m_render);
  }
}

bool MySDLRender::available() const { return m_render != nullptr; }

MySDLRender::MySDLRender(MySDLRender &&rhs) noexcept
    : m_render{std::exchange(rhs.m_render, nullptr)} {}

MySDLRender &MySDLRender::operator=(MySDLRender &&rhs) noexcept {
  if (m_render != nullptr) {
    SDL_DestroyRenderer(m_render);
  }
  m_render = std::exchange(rhs.m_render, nullptr);
  return *this;
}

SDL_Renderer *MySDLRender::getRendererPtr() const { return m_render; }

void MySDLRender::initRenderColor() const {
  constexpr uint8_t initColor = 0xFF;
  // Initialize renderer color
  SDL_SetRenderDrawColor(m_render, initColor, initColor, initColor, initColor);
}

void MySDLRender::initPNGLoading() const {
  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0) {
    fmt::print("SDL_image could not initialize! SDL_image Error: {}\n",
               IMG_GetError());
    std::abort();
  }
}

void MySDLRender::initTTF() const {
  if (TTF_Init() == -1) {
    fmt::print("SDL_ttf could not initialize! SDL_ttf Error:{}\n",
               TTF_GetError());
    std::abort();
  }
}
}; // namespace HF