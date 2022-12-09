#include "Dot.hpp"

Dot::Dot() {}

Dot::~Dot() {}

Dot::Dot(const std::shared_ptr<HF::MySDLRender> &render,
         const std::string &path)
    : m_dotTexture(render, path) {}

Dot::Dot(Dot &&rhs) noexcept
    : m_posX(rhs.m_posX), m_posY(rhs.m_posY), m_velX(rhs.m_velX),
      m_velY(rhs.m_velY), m_dotTexture(std::move(rhs.m_dotTexture)) {}

Dot &Dot::operator=(Dot &&rhs) noexcept {
  m_posX = rhs.m_posX;
  m_posY = rhs.m_posY;
  m_velX = rhs.m_velX;
  m_velY = rhs.m_velY;
  m_dotTexture = std::move(rhs.m_dotTexture);
  return *this;
}

void Dot::move() {
  m_posX += m_velX;
  /* 这里是否应该将屏幕大小设置为全局变量 */
  if ((m_posX < 0) || (m_posX + DOT_WIDTH > 680)) {
    m_posX = 0;
  }

  m_posY += m_velY;
  if ((m_posY < 0) || (m_posY + DOT_HEIGHT > 480)) {
    m_posY = 0;
  }
}

void Dot::render() {
  if (m_dotTexture.available()) {
    m_dotTexture.render(m_posX, m_posY);
  }
}

void Dot::replaceTexture(HF::PictureTexture pictureTexture) {
  m_dotTexture = std::move(pictureTexture);
}

void Dot::up() { m_velY -= DOT_VEL; }
void Dot::down() { m_velY += DOT_VEL; }
void Dot::left() { m_velX -= DOT_VEL; }
void Dot::right() { m_velX += DOT_VEL; }