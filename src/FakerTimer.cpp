#include "FakerTimer.hpp"

#include "SDL.h"

namespace HF {
FakerTimer::FakerTimer() {}

FakerTimer::~FakerTimer() {}

FakerTimer::FakerTimer(FakerTimer &&rhs) noexcept
    : m_startTicks(rhs.m_startTicks), m_pausedTicks(rhs.m_pausedTicks),
      m_isPaused(rhs.m_isPaused), m_isStarted(rhs.m_isStarted) {}

FakerTimer &FakerTimer::operator=(FakerTimer &&rhs) noexcept {
  m_startTicks = rhs.m_startTicks;
  m_pausedTicks = rhs.m_pausedTicks;
  m_isPaused = rhs.m_isPaused;
  m_isStarted = rhs.m_isStarted;
  return *this;
}

void FakerTimer::start() {
  m_startTicks = SDL_GetTicks64();
  m_pausedTicks = 0;
  m_isStarted = true;
  m_isPaused = false;
}

void FakerTimer::stop() {
  m_startTicks = 0;
  m_pausedTicks = 0;
  m_isStarted = false;
  m_isPaused = true;
}

void FakerTimer::pause() {
  if (isStarted() && !isPaused()) {
    m_isPaused = true;
    m_pausedTicks = SDL_GetTicks64() - m_startTicks;
    m_startTicks = 0;
  }
}

void FakerTimer::unpause() {
  if (isStarted() && isPaused()) {
    m_isPaused = false;
    m_startTicks = SDL_GetTicks64() - m_pausedTicks;
    m_pausedTicks = 0;
  }
}

uint64_t FakerTimer::getTicks() const {
  uint64_t time = 0;
  if (isStarted()) {
    if (isPaused()) {
      return m_pausedTicks;
    } else {
      return SDL_GetTicks64() - m_startTicks;
    }
  }
  return time;
}

bool FakerTimer::isStarted() const { return m_isStarted; }

bool FakerTimer::isPaused() const { return m_isPaused; }
}; // namespace HF