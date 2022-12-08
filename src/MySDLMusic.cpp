#include "MySDLMusic.hpp"

#include <utility>

namespace HF {
MySDLMusic::MySDLMusic() {}

MySDLMusic::~MySDLMusic() {
  if (m_music != nullptr) {
    Mix_FreeMusic(m_music);
  }
}

MySDLMusic::MySDLMusic(const std::string &path)
    : m_music(Mix_LoadMUS(path.c_str())) {}

MySDLMusic::MySDLMusic(MySDLMusic &&rhs) noexcept
    : m_music(std::exchange(rhs.m_music, nullptr)) {}

MySDLMusic &MySDLMusic::operator=(MySDLMusic &&rhs) noexcept {
  if (m_music != nullptr) {
    Mix_FreeMusic(m_music);
  }
  m_music = std::exchange(rhs.m_music, nullptr);
  return *this;
}

bool MySDLMusic::available() const { return m_music != nullptr; }

void MySDLMusic::play(int loops) const {
  if (m_music != nullptr) {
    Mix_PlayMusic(m_music, loops);
  }
}
}; // namespace HF