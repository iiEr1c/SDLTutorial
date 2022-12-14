#include "SDL.h"
#include <fmt/core.h>

#include "MySDLWindow.hpp"

#include <utility>

namespace HF {
MySDLWindow::MySDLWindow() {}

MySDLWindow::MySDLWindow(const char *title, int xPos, int yPos, int width,
                         int height, uint32_t flags)
    : m_window(SDL_CreateWindow(title, xPos, yPos, width, height, flags)) {
  if (m_window == nullptr) [[unlikely]] {
    fmt::print("create window error. reason: {}\n", SDL_GetError());
    std::abort();
  }
}

MySDLWindow::~MySDLWindow() {
  if (m_window != nullptr) {
    SDL_DestroyWindow(m_window);
  }
}

MySDLWindow::MySDLWindow(MySDLWindow &&rhs) noexcept
    : m_window{std::exchange(rhs.m_window, nullptr)} {}

MySDLWindow &MySDLWindow::operator=(MySDLWindow &&rhs) noexcept {
  if (m_window != nullptr) {
    SDL_DestroyWindow(m_window);
  }
  m_window = std::exchange(rhs.m_window, nullptr);
  return *this;
}

SDL_Window *MySDLWindow::getWindowPtr() const { return m_window; }

SDL_Surface *MySDLWindow::getWindowSurfacePtr() const {
  return SDL_GetWindowSurface(getWindowPtr());
}

bool MySDLWindow::available() const { return m_window != nullptr; }
} // namespace HF