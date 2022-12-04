#include "MySDLTexture.hpp"
#include <fmt/core.h>

#include <utility>

namespace HF {
MySDLTexture::MySDLTexture() {}

MySDLTexture::MySDLTexture(const std::shared_ptr<MySDLRender> &render)
    : m_weak_render{render} {}

MySDLTexture::MySDLTexture(const std::shared_ptr<MySDLRender> &render,
                           MySDLSurface surface)
    : m_weak_render{render} {
  if (render->available() && surface.available()) [[likely]] {
    m_texture = SDL_CreateTextureFromSurface(render->getRendererPtr(),
                                             surface.getSurfacePtr());
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
                                                       rhs.m_texture,
                                                       nullptr)} {}

MySDLTexture &MySDLTexture::operator=(MySDLTexture &&rhs) noexcept {
  m_weak_render = std::move(rhs.m_weak_render);
  m_texture = std::exchange(rhs.m_texture, nullptr);
  return *this;
}

bool MySDLTexture::available() const { return m_texture != nullptr; }

SDL_Texture *MySDLTexture::getTexturePtr() const { return m_texture; }
}; // namespace HF