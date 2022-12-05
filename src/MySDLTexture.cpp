#include "MySDLTexture.hpp"
#include <fmt/core.h>

#include <utility>

namespace HF {
MySDLTexture::MySDLTexture() {}

MySDLTexture::MySDLTexture(const std::shared_ptr<MySDLRender> &render)
    : m_weak_render{render} {}

/* non-ColorKey */
MySDLTexture::MySDLTexture(const std::shared_ptr<MySDLRender> &render,
                           MySDLSurface surface)
    : m_weak_render{render} {
  if (render->available() && surface.available()) [[likely]] {
    m_texture = SDL_CreateTextureFromSurface(render->getRendererPtr(),
                                             surface.getSurfacePtr());
    m_weight = surface.getSurfacePtr()->w;
    m_height = surface.getSurfacePtr()->h;
    if (m_texture == nullptr) {
      fmt::print("SDL_CreateTextureFromSurface error: {}\n", SDL_GetError());
    }
  } else {
    if (!render->available()) {
      fmt::print("render isn't available. create texture from surface failed.");
    }

    if (!surface.available()) {
      fmt::print(
          "surface isn't available. create texture from surface failed.");
    }
  }
}

/* enable colorkey color */
MySDLTexture::MySDLTexture(const std::shared_ptr<MySDLRender> &render,
                           MySDLSurface surface,
                           std::tuple<int, int, int> color)
    : m_weak_render{render} {
  if (render->available() && surface.available()) [[likely]] {
    int ret = SDL_SetColorKey(surface.getSurfacePtr(), SDL_TRUE,
                              SDL_MapRGB(surface.getSurfacePtr()->format,
                                         std::get<0>(color), std::get<1>(color),
                                         std::get<2>(color)));
    if (ret > 0) {
      fmt::print("SDL_SetColorKey error: {}\n", SDL_GetError());
    }
    m_texture = SDL_CreateTextureFromSurface(render->getRendererPtr(),
                                             surface.getSurfacePtr());
    m_weight = surface.getSurfacePtr()->w;
    m_height = surface.getSurfacePtr()->h;
    if (m_texture == nullptr) {
      fmt::print("SDL_CreateTextureFromSurface error: {}\n", SDL_GetError());
    }
  } else {
    if (!render->available()) {
      fmt::print("render isn't available. create texture from surface failed.");
    }

    if (!surface.available()) {
      fmt::print(
          "surface isn't available. create texture from surface failed.");
    }
  }
}

MySDLTexture::~MySDLTexture() {
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
  }
}

MySDLTexture::MySDLTexture(MySDLTexture &&rhs) noexcept
    : m_weak_render{std::move(rhs.m_weak_render)}, m_texture{std::exchange(
                                                       rhs.m_texture, nullptr)},
      m_weight{rhs.m_weight}, m_height{rhs.m_height} {}

MySDLTexture &MySDLTexture::operator=(MySDLTexture &&rhs) noexcept {
  m_weak_render = std::move(rhs.m_weak_render);
  m_texture = std::exchange(rhs.m_texture, nullptr);
  m_weight = rhs.m_weight;
  m_height = rhs.m_height;
  return *this;
}

bool MySDLTexture::available() const { return m_texture != nullptr; }

SDL_Texture *MySDLTexture::getTexturePtr() const { return m_texture; }

void MySDLTexture::render(int xPos, int yPos, SDL_Rect *clip /*= nullptr*/,
                          double angle /* = 0.0*/,
                          SDL_Point *center /*= nullptr*/,
                          SDL_RendererFlip flip /* = SDL_FLIP_NONE*/) {
  auto render = m_weak_render.lock();
  if (render != nullptr) {
    SDL_Rect renderQuad{.x = xPos, .y = yPos, .w = m_weight, .h = m_height};
    if (clip != nullptr) {
      /*  */
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(render->getRendererPtr(), m_texture, clip,
                     std::addressof(renderQuad), angle, center, flip);
  }
}

void MySDLTexture::setColor(std::tuple<uint8_t, uint8_t, uint8_t> rgb) {
  if (m_texture != nullptr) {
    SDL_SetTextureColorMod(m_texture, std::get<0>(rgb), std::get<1>(rgb),
                           std::get<2>(rgb));
  }
}

void MySDLTexture::setAlpha(uint8_t alpha) {
  if (m_texture != nullptr) {
    SDL_SetTextureAlphaMod(m_texture, alpha);
  }
}
}; // namespace HF