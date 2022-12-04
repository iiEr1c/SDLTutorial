#include "MySDLRender.hpp"
#include <fmt/core.h>

#include <utility>

namespace HF {
MySDLRender::MySDLRender() {}

MySDLRender::MySDLRender(SDL_Window *window)
    : m_render{SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)} {
  if (m_render != nullptr) {
    constexpr uint8_t initColor = 0xFF;
    // Initialize renderer color
    SDL_SetRenderDrawColor(m_render, initColor, initColor, initColor,
                           initColor);
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0) {
      fmt::print("render init failed.\n");
      std::abort();
    }
  }
}

MySDLRender::~MySDLRender() {
  if (m_render != nullptr) {
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
}; // namespace HF