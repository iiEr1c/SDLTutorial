#pragma once

#include "SDL_mixer.h"

#include <string>

namespace HF {
class MySDLMixer {
  Mix_Chunk *m_chunk = nullptr;

public:
  MySDLMixer();
  ~MySDLMixer();
  MySDLMixer(const std::string &path);

  MySDLMixer(MySDLMixer &&) noexcept;
  MySDLMixer &operator=(MySDLMixer &&) noexcept;

  bool available() const;

  void play() const;
};
}; // namespace HF