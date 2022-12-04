#include "MySDLSurface.hpp"

#include <string_view>
#include <utility>

namespace HF {
MySDLSurface::MySDLSurface() {}

MySDLSurface::MySDLSurface(SDL_Surface *surface) : m_surface{surface} {}

MySDLSurface::MySDLSurface(const std::string &path) : m_surface{nullptr} {
  /* 根据后缀分流 */
  std::string_view pathSV = path;
  if (pathSV.ends_with(".bmp")) {
    m_surface = SDL_LoadBMP(path.c_str());
  } else if (pathSV.ends_with(".png")) {
    m_surface = IMG_Load(path.c_str());
  }
}

MySDLSurface::~MySDLSurface() {
  if (m_surface != nullptr) {
    SDL_FreeSurface(m_surface);
  }
}

MySDLSurface::MySDLSurface(MySDLSurface &&rhs) noexcept
    : m_surface{std::exchange(rhs.m_surface, nullptr)} {}

MySDLSurface &MySDLSurface::operator=(MySDLSurface &&rhs) noexcept {
  if (m_surface != nullptr) {
    SDL_FreeSurface(m_surface);
  }
  m_surface = std::exchange(rhs.m_surface, nullptr);
  return *this;
}

SDL_Surface *MySDLSurface::getSurfacePtr() const { return m_surface; }

bool MySDLSurface::available() const { return m_surface != nullptr; }
}; // namespace HF