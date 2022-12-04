#pragma once

#include "MySDLRender.hpp"
#include "MySDLSurface.hpp"

#include <memory>

namespace HF {
class MySDLTexture {
  std::weak_ptr<MySDLRender> m_weak_render;
  SDL_Texture *m_texture = nullptr;

public:
  MySDLTexture();

  MySDLTexture(const std::shared_ptr<MySDLRender> &);

  MySDLTexture(const std::shared_ptr<MySDLRender> &, MySDLSurface);

  ~MySDLTexture();

  MySDLTexture(const MySDLTexture &) = delete;
  MySDLTexture &operator=(const MySDLTexture &) = delete;

  MySDLTexture(MySDLTexture &&) noexcept;
  MySDLTexture &operator=(MySDLTexture &&) noexcept;

  bool available() const;
  SDL_Texture *getTexturePtr() const;
};
}; // namespace HF