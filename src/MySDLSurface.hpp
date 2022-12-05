#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <string>

namespace HF {
class MySDLSurface {
  SDL_Surface *m_surface = nullptr;

public:
  MySDLSurface();

  MySDLSurface(const std::string &);

  MySDLSurface(SDL_Surface *);

  ~MySDLSurface();

  MySDLSurface(const MySDLSurface &) = delete;

  MySDLSurface &operator=(const MySDLSurface &) = delete;

  MySDLSurface(MySDLSurface &&) noexcept;

  MySDLSurface &operator=(MySDLSurface &&) noexcept;

  SDL_Surface *getSurfacePtr() const;

  bool available() const;
};
} // namespace HF