#include "SDL.h"
#include <fmt/core.h>

#include "MySDLWindow.hpp"

#include <utility>

namespace HF {
MySDLWindow::MySDLWindow() : m_window{nullptr} {}

MySDLWindow::MySDLWindow(const char *title, int x, int y, int w, int h,
                         uint32_t flags)
    : m_window(SDL_CreateWindow(title, x, y, w, h, flags)) {
  if (m_window == nullptr) [[unlikely]] {
    fmt::print("create window error. reason: {}\n", SDL_GetError());
    std::abort();
  }
}

MySDLWindow::~MySDLWindow() {
  if (m_window != nullptr) {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
  }
}

MySDLWindow::MySDLWindow(MySDLWindow &&rhs)
    : m_window(std::exchange(rhs.m_window, nullptr)) {}

MySDLWindow &MySDLWindow::operator=(MySDLWindow &&rhs) {
  m_window = std::exchange(rhs.m_window, nullptr);
  return *this;
}
} // namespace HF