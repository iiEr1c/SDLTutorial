#pragma once

#include "MySDLRender.hpp"
#include "MySDLTTFFont.hpp"

#include <memory>
#include <string>
#include <tuple>

namespace HF {
class TTFFontTexture {
  std::weak_ptr<MySDLRender> m_weak_render;
  SDL_Texture *m_texture = nullptr;

public:
  TTFFontTexture(const std::shared_ptr<MySDLRender> &, const std::string &);

  /* with ColorKey */
  TTFFontTexture(const std::shared_ptr<MySDLRender> &, const std::string &,
                 std::tuple<int, int, int>);
  ~TTFFontTexture();
};
}; // namespace HF