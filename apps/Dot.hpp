#pragma once

#include "MySDLRender.hpp"
#include "PictureTexture.hpp"

#include <memory>
#include <string>

struct Dot {
  static inline int DOT_WIDTH = 20;
  static inline int DOT_HEIGHT = 20;
  static inline int DOT_VEL = 1;

  Dot();
  Dot(const std::shared_ptr<HF::MySDLRender> &, const std::string &);
  ~Dot();

  Dot(const Dot &) = delete;
  Dot &operator=(const Dot &) = delete;

  Dot(Dot &&) noexcept;
  Dot &operator=(Dot &&) noexcept;

  /* 每一帧更新一次位置 */
  void move();

  void render();

  void replaceTexture(HF::PictureTexture);

  void up();
  void down();
  void left();
  void right();

private:
  int m_posX = 0;
  int m_posY = 0;
  int m_velX = 0;
  int m_velY = 0;

  HF::PictureTexture m_dotTexture;
};