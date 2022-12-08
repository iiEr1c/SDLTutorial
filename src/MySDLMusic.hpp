#pragma once

#include "SDL_mixer.h"

#include <string>

namespace HF {
class MySDLMusic {
  Mix_Music *m_music = nullptr;

public:
  MySDLMusic();
  ~MySDLMusic();
  MySDLMusic(const std::string &path);

  MySDLMusic(const MySDLMusic &) = delete;
  MySDLMusic &operator=(const MySDLMusic &) = delete;

  MySDLMusic(MySDLMusic &&) noexcept;
  MySDLMusic &operator=(MySDLMusic &&) noexcept;

  bool available() const;

  void play(int loops = -1) const;
};
}; // namespace HF