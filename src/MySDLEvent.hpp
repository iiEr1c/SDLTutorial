#pragma once

#include "SDL.h"
#include <fmt/core.h>

#include <functional>
#include <memory>

namespace HF {
class MySDL;

class MySDLEvent {
public:
  using MySDLEventCallbackType =
      std::function<void(const std::shared_ptr<MySDL> &, const SDL_Event &)>;

private:
  std::weak_ptr<MySDL> m_weak_sdl;
  MySDLEventCallbackType m_callback;

public:
  MySDLEvent(const std::shared_ptr<MySDL> &, MySDLEventCallbackType);
  ~MySDLEvent();
  MySDLEvent(const MySDLEvent &) = delete;
  MySDLEvent &operator=(const MySDLEvent &) = delete;

  MySDLEvent(MySDLEvent &&) noexcept;
  MySDLEvent &operator=(MySDLEvent &&) noexcept;

  /* 函数对象 */
  inline void operator()(const SDL_Event &event) {
    auto ptr = m_weak_sdl.lock();
    if (ptr != nullptr) {
      m_callback(ptr, event);
    } else {
      fmt::print("sdl object has released.\n");
    }
  }
};
}; // namespace HF