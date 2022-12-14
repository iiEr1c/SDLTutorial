#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <string>

namespace HF {
class MySDLRender {
  SDL_Renderer *m_render = nullptr;

public:
  MySDLRender();

  MySDLRender(SDL_Window *, uint32_t);

  ~MySDLRender();

  MySDLRender(const MySDLRender &) = delete;

  MySDLRender &operator=(const MySDLRender &) = delete;

  MySDLRender(MySDLRender &&) noexcept;
  MySDLRender &operator=(MySDLRender &&) noexcept;

  bool available() const;

  SDL_Renderer *getRendererPtr() const;

  void initRenderColor() const;

  void initPNGLoading() const;

  void initTTF() const;
};
} // namespace HF