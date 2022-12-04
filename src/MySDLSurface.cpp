#include "MySDLSurface.hpp"

#include <utility>

namespace HF {
MySDLSurface::MySDLSurface() {}

MySDLSurface::MySDLSurface(SDL_Surface *surface) : m_surface{surface} {}

MySDLSurface::MySDLSurface(const std::string &path)
    : m_surface(SDL_LoadBMP(path.c_str())) {}

MySDLSurface::~MySDLSurface() {
  if (m_surface != nullptr) {
    SDL_FreeSurface(m_surface);
  }
  m_surface = nullptr;
}

MySDLSurface::MySDLSurface(MySDLSurface &&rhs) : m_surface{rhs.m_surface} {}

MySDLSurface &MySDLSurface::operator=(MySDLSurface &&rhs) {
  if (m_surface != nullptr) {
    SDL_FreeSurface(m_surface);
  }
  m_surface = std::exchange(rhs.m_surface, nullptr);
  return *this;
}

SDL_Surface *MySDLSurface::getSurfacePtr() const { return m_surface; }

bool MySDLSurface::available() const { return m_surface != nullptr; }
}; // namespace HF