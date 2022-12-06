#include "PictureTexture.hpp"
#include <fmt/core.h>

#include <utility>

namespace HF {
PictureTexture::PictureTexture() {}

PictureTexture::PictureTexture(const std::shared_ptr<MySDLRender> &render)
    : m_weak_render{render} {}

PictureTexture::PictureTexture(const std::shared_ptr<MySDLRender> &render,
                           const std::string &path)
    : m_weak_render{render} {
  if (render->available()) [[likely]] {
    auto surface = MySDLSurface(path);
    if (!surface.available()) [[unlikely]] {
      fmt::print("cann't load {} file\n", path);
      return;
    }
    m_texture = SDL_CreateTextureFromSurface(render->getRendererPtr(),
                                             surface.getSurfacePtr());
    m_width = surface.getSurfacePtr()->w;
    m_height = surface.getSurfacePtr()->h;
    if (m_texture == nullptr) [[unlikely]] {
      fmt::print("SDL_CreateTextureFromSurface error: {}\n", SDL_GetError());
    }
  }
}

/* with ColorKey */
PictureTexture::PictureTexture(const std::shared_ptr<MySDLRender> &render,
                           const std::string &path,
                           std::tuple<int, int, int> color)
    : m_weak_render{render} {
  if (render->available()) [[likely]] {
    auto surface = MySDLSurface(path);
    if (!surface.available()) [[unlikely]] {
      fmt::print("cann't load {} file\n", path);
      return;
    }

    int ret = SDL_SetColorKey(surface.getSurfacePtr(), SDL_TRUE,
                              SDL_MapRGB(surface.getSurfacePtr()->format,
                                         std::get<0>(color), std::get<1>(color),
                                         std::get<2>(color)));
    if (ret != 0) {
      fmt::print("SDL_SetColorKey error: {}\n", SDL_GetError());
      return;
    }

    m_texture = SDL_CreateTextureFromSurface(render->getRendererPtr(),
                                             surface.getSurfacePtr());
    m_width = surface.getSurfacePtr()->w;
    m_height = surface.getSurfacePtr()->h;
    if (m_texture == nullptr) [[unlikely]] {
      fmt::print("SDL_CreateTextureFromSurface error: {}\n", SDL_GetError());
    }
  }
}

PictureTexture::~PictureTexture() {
  if (m_texture != nullptr) {
    SDL_DestroyTexture(m_texture);
  }
}

PictureTexture::PictureTexture(PictureTexture &&rhs) noexcept
    : m_weak_render{std::move(rhs.m_weak_render)}, m_texture{std::exchange(
                                                       rhs.m_texture, nullptr)},
      m_width{rhs.m_width}, m_height{rhs.m_height} {}

PictureTexture &PictureTexture::operator=(PictureTexture &&rhs) noexcept {
  m_weak_render = std::move(rhs.m_weak_render);
  m_texture = std::exchange(rhs.m_texture, nullptr);
  m_width = rhs.m_width;
  m_height = rhs.m_height;
  return *this;
}

bool PictureTexture::available() const { return m_texture != nullptr; }

SDL_Texture *PictureTexture::getTexturePtr() const { return m_texture; }

void PictureTexture::render(int xPos, int yPos, SDL_Rect *clip /*= nullptr*/,
                          double angle /* = 0.0*/,
                          SDL_Point *center /*= nullptr*/,
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

void PictureTexture::setColor(std::tuple<uint8_t, uint8_t, uint8_t> rgb) {
  if (m_texture != nullptr) {
    SDL_SetTextureColorMod(m_texture, std::get<0>(rgb), std::get<1>(rgb),
                           std::get<2>(rgb));
  }
}

void PictureTexture::setAlpha(uint8_t alpha) {
  if (m_texture != nullptr) {
    SDL_SetTextureAlphaMod(m_texture, alpha);
  }
}
}; // namespace HF