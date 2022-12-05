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

  void render(int xPos, int yPos,
              SDL_Rect *clip = nullptr); // 在(xPos, yPos)处渲染texture

  /* 调节rgb三个通道的分量 */
  void setColor(std::tuple<uint8_t, uint8_t, uint8_t>);

  /* 透明 */
  void setAlpha(uint8_t);
};
}; // namespace HF