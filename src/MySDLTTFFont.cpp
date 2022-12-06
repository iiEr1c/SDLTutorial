#include "MySDLTTFFont.hpp"
#include "fmt/core.h"

#include <utility>

namespace HF {
MySDLTTFFont::MySDLTTFFont() {}

MySDLTTFFont::~MySDLTTFFont() {
  if (m_font != nullptr) {
    TTF_CloseFont(m_font);
  }
}

MySDLTTFFont::MySDLTTFFont(const std::string &ttfPath, int ptsize) {
  m_font = TTF_OpenFont(ttfPath.c_str(), ptsize);
  if (m_font == nullptr) [[unlikely]] {
    fmt::print("Failed to load lazy font {}, SDL_ttf Error: {}\n", ttfPath,
               TTF_GetError());
  }
}

MySDLTTFFont::MySDLTTFFont(MySDLTTFFont &&rhs) noexcept
    : m_font(std::exchange(rhs.m_font, nullptr)) {}

MySDLTTFFont &MySDLTTFFont::operator=(MySDLTTFFont &&rhs) noexcept {
  m_font = std::exchange(rhs.m_font, nullptr);
  return *this;
}

TTF_Font *MySDLTTFFont::getTTFPtr() const { return m_font; }

bool MySDLTTFFont::available() const { return m_font != nullptr; }
}; // namespace HF