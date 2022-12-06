#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

#include <string>

namespace HF {
class MySDLTTFFont {
  TTF_Font *m_font = nullptr;

public:
  MySDLTTFFont();
  MySDLTTFFont(const std::string &, int);

  ~MySDLTTFFont();

  MySDLTTFFont(const MySDLTTFFont &) = delete;
  MySDLTTFFont &operator=(const MySDLTTFFont &) = delete;

  MySDLTTFFont(MySDLTTFFont &&) noexcept;
  MySDLTTFFont &operator=(MySDLTTFFont &&) noexcept;
};
}; // namespace HF