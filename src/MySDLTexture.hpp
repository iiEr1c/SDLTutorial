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

  MySDLTexture(const std::shared_ptr<MySDLRender> &, const std::string &);

  /* with ColorKey */
  MySDLTexture(const std::shared_ptr<MySDLRender> &, const std::string &,
               std::tuple<int, int, int>);

  ~MySDLTexture();

  MySDLTexture(const MySDLTexture &) = delete;
  MySDLTexture &operator=(const MySDLTexture &) = delete;

  MySDLTexture(MySDLTexture &&) noexcept;
  MySDLTexture &operator=(MySDLTexture &&) noexcept;

  bool available() const;
  SDL_Texture *getTexturePtr() const;

  /* 带有旋转/翻转的render */
  void render(int xPos, int yPos, SDL_Rect *clip = nullptr, double angle = 0.0,
              SDL_Point *center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  /* 调节rgb三个通道的分量 */
  void setColor(std::tuple<uint8_t, uint8_t, uint8_t>);

  /* 透明 */
  void setAlpha(uint8_t);
};
}; // namespace HF