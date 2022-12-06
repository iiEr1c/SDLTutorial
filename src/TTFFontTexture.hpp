#pragma once

#include "MySDLRender.hpp"
#include "MySDLTTFFont.hpp"

#include <memory>
#include <string>
#include <tuple>

namespace HF {
class TTFFontTexture {
  std::weak_ptr<MySDLRender> m_weak_render;
  std::weak_ptr<MySDLTTFFont> m_weak_ttffont;
  std::string m_text;
  SDL_Color m_text_color = {};
  SDL_Texture *m_texture = nullptr;
  int m_width = 0;
  int m_height = 0;

public:
  TTFFontTexture();
  TTFFontTexture(const std::shared_ptr<MySDLRender> &,
                 const std::shared_ptr<MySDLTTFFont> &, const std::string &,
                 SDL_Color);
  ~TTFFontTexture();

  TTFFontTexture(const TTFFontTexture &) = delete;
  TTFFontTexture &operator=(const TTFFontTexture &) = delete;

  TTFFontTexture(TTFFontTexture &&) noexcept;
  TTFFontTexture &operator=(TTFFontTexture &&) noexcept;

  /* 带有旋转/翻转的render */
  void render(int xPos, int yPos, SDL_Rect *clip = nullptr, double angle = 0.0,
              SDL_Point *center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE);
};
}; // namespace HF