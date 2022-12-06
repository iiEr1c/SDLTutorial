#pragma once

#include "SDL.h"

#include <functional>

namespace HF {
// https://github.com/IFeelBloated/Type-System-Zoo/blob/master/existential%20type.cxx
struct TextureMessenger {
  using QuantificationBound = auto(int, int, SDL_Rect *, double, SDL_Point *,
                                   SDL_RendererFlip) -> void;
  std::move_only_function<QuantificationBound> m_func = {};

  TextureMessenger() = default;
  TextureMessenger(auto x) {
    m_func = [x = std::move(x)](int xPos, int yPos, SDL_Rect *clip,
                                double angle, SDL_Point *center,
                                SDL_RendererFlip flip) mutable {
      x.render(xPos, yPos, clip, angle, center, flip);
    };
  }

  auto render(int xPos, int yPos, SDL_Rect *clip = nullptr, double angle = 0.0,
              SDL_Point *center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE) -> void {
    m_func(xPos, yPos, clip, angle, center, flip);
  }

  TextureMessenger(const TextureMessenger &) = delete;
  TextureMessenger &operator=(const TextureMessenger &) = delete;

  TextureMessenger(TextureMessenger &&rhs) noexcept
      : m_func(std::move(rhs.m_func)) {}

  TextureMessenger &operator=(TextureMessenger &&rhs) {
    m_func = std::move(rhs.m_func);
    return *this;
  }
};
}; // namespace HF