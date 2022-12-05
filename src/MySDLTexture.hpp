#pragma once

#include "MySDLRender.hpp"
#include "MySDLSurface.hpp"

#include <memory>
#include <tuple>

namespace HF {
class MySDLTexture {
  std::weak_ptr<MySDLRender> m_weak_render;
  SDL_Texture *m_texture = nullptr;
  int m_weight = 0;
  int m_height = 0;

public:
  MySDLTexture();

  MySDLTexture(const std::shared_ptr<MySDLRender> &);

  MySDLTexture(const std::shared_ptr<MySDLRender> &, MySDLSurface);

  MySDLTexture(const std::shared_ptr<MySDLRender> &, MySDLSurface,
               std::tuple<int, int, int>);

  ~MySDLTexture();

  MySDLTexture(const MySDLTexture &) = delete;
  MySDLTexture &operator=(const MySDLTexture &) = delete;

  MySDLTexture(MySDLTexture &&) noexcept;
  MySDLTexture &operator=(MySDLTexture &&) noexcept;

  bool available() const;
  SDL_Texture *getTexturePtr() const;

  void render(int xPos, int yPos); // 在(xPos, yPos)处渲染texture
};
}; // namespace HF