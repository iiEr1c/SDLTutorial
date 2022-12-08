#include "MySDLMixer.hpp"

#include <utility>

namespace HF {
MySDLMixer::MySDLMixer() {}

MySDLMixer::~MySDLMixer() {
  if (m_chunk != nullptr) {
    Mix_FreeChunk(m_chunk);
  }
}

MySDLMixer::MySDLMixer(const std::string &path)
    : m_chunk(Mix_LoadWAV(path.c_str())) {}

MySDLMixer::MySDLMixer(MySDLMixer &&rhs) noexcept
    : m_chunk(std::exchange(rhs.m_chunk, nullptr)) {}

MySDLMixer &MySDLMixer::operator=(MySDLMixer &&rhs) noexcept {
  if (m_chunk != nullptr) {
    Mix_FreeChunk(m_chunk);
  }
  m_chunk = std::exchange(rhs.m_chunk, nullptr);
  return *this;
}

bool MySDLMixer::available() const { return m_chunk != nullptr; }

void MySDLMixer::play() const {
  if (m_chunk != nullptr) {
    Mix_PlayChannel(-1, m_chunk, 0);
  }
}
}; // namespace HF