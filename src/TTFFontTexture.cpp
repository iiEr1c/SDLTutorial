#include "TTFFontTexture.hpp"
#include "MySDLSurface.hpp"
#include "fmt/core.h"

#include <utility>

namespace HF {
TTFFontTexture::TTFFontTexture() {}

TTFFontTexture::TTFFontTexture(const std::shared_ptr<MySDLRender> &render,
                               const std::shared_ptr<MySDLTTFFont> &ttf,
                               const std::string &text, SDL_Color textColor)
    : m_weak_render{render}, m_weak_ttffont{ttf}, m_text{text}, m_text_color{
                                                                    textColor} {
  if (render != nullptr && render->available() && ttf != nullptr &&
      ttf->available()) {
    auto surface = MySDLSurface(
        TTF_RenderText_Solid(ttf->getTTFPtr(), text.c_str(), textColor));
    if (!surface.available()) [[unlikely]] {
      fmt::print("Unable to render text surface! SDL_ttf Error:{}\n",
                 TTF_GetError());
    } else {
      m_texture = SDL_CreateTextureFromSurface(render->getRendererPtr(),
                                               surface.getSurfacePtr());
      if (m_texture != nullptr) [[likely]] {
        m_width = surface.getSurfacePtr()->w;
        m_height = surface.getSurfacePtr()->h;
      } else {
        fmt::print(
            "Unable to create texture from rendered text! SDL Error:{}\n",
            SDL_GetError());
      }
    }
  }
}

TTFFontTexture::~TTFFontTexture() {
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
  }
}

TTFFontTexture::TTFFontTexture(TTFFontTexture &&rhs) noexcept
    : m_weak_render(std::move(rhs.m_weak_render)),
      m_weak_ttffont(std::move(rhs.m_weak_ttffont)),
      m_text(std::move(rhs.m_text)), m_text_color(rhs.m_text_color),
      m_texture(std::exchange(rhs.m_texture, nullptr)), m_width(rhs.m_width),
      m_height(rhs.m_height) {}

TTFFontTexture &TTFFontTexture::operator=(TTFFontTexture &&rhs) noexcept {
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
  }
  m_weak_render = std::move(rhs.m_weak_render);
  m_weak_ttffont = std::move(rhs.m_weak_ttffont);
  m_text = std::move(rhs.m_text);
  m_text_color = rhs.m_text_color;
  m_texture = std::exchange(rhs.m_texture, nullptr);
  m_width = rhs.m_width;
  m_height = rhs.m_height;
  return *this;
}

void TTFFontTexture::render(int xPos, int yPos, SDL_Rect *clip /* = nullptr*/,
                            double angle /* = 0.0*/,
                            SDL_Point *center /* = nullptr*/,
                            SDL_RendererFlip flip /* = SDL_FLIP_NONE*/) {
  auto render = m_weak_render.lock();
  if (render != nullptr) {
    SDL_Rect renderQuad{.x = xPos, .y = yPos, .w = m_width, .h = m_height};
    if (clip != nullptr) {
      /*  */
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(render->getRendererPtr(), m_texture, clip,
                     std::addressof(renderQuad), angle, center, flip);
  }
}
}; // namespace HF