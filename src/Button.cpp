#include "Button.hpp"
#include <fmt/core.h>

#include <utility>

namespace HF {

Button::Button() {}

Button::~Button() {}

Button::Button(const std::shared_ptr<MySDLRender> &render,
               const std::string &path)
    : m_button_texture(render, path) {}

Button::Button(const std::shared_ptr<MySDLRender> &render,
               const std::string &path, int posX, int posY)
    : m_button_texture(render, path), m_topLeftPosX(posX), m_topLeftPosY(posY) {
}

Button::Button(Button &&rhs) noexcept
    : m_button_texture(std::move(rhs.m_button_texture)),
      m_topLeftPosX(rhs.m_topLeftPosX), m_topLeftPosY(rhs.m_topLeftPosY) {}

Button &Button::operator=(Button &&rhs) noexcept {
  m_button_texture = std::move(rhs.m_button_texture);
  m_topLeftPosX = rhs.m_topLeftPosX;
  m_topLeftPosY = rhs.m_topLeftPosY;
  return *this;
}

void Button::setPosition(int posX, int posY) {
  m_topLeftPosX = posX;
  m_topLeftPosY = posY;
}

void Button::render() {
  if (m_button_texture.available()) {
    m_button_texture.render(m_topLeftPosX, m_topLeftPosY);
  }
}

std::pair<int, int> Button::getPosition() const {
  return {m_topLeftPosX, m_topLeftPosY};
}

std::pair<int, int> Button::getButtonImgAttr() const {
  return m_button_texture.getImageAttr();
}
}; // namespace HF