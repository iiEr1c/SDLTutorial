#pragma once

#include "PictureTexture.hpp"

#include <memory>
#include <tuple>

namespace HF {
class Button {
  PictureTexture m_button_texture;
  int m_topLeftPosX = 0;
  int m_topLeftPosY = 0;

public:
  Button();

  Button(const std::shared_ptr<MySDLRender> &, const std::string &);

  Button(const std::shared_ptr<MySDLRender> &, const std::string &, int, int);

  ~Button();

  Button(const Button &) = delete;
  Button &operator=(const Button &) = delete;

  Button(Button &&) noexcept;
  Button &operator=(Button &&) noexcept;

  bool available() const;

  void setPosition(int, int);

  void render();

  std::pair<int, int> getPosition() const;
  
  std::pair<int, int> getButtonImgAttr() const;
};
}; // namespace HF