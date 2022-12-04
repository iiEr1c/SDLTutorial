#pragma once

#include <functional>
#include <memory>

namespace HF {
class MySDL;

class MySDLEvent {
  std::weak_ptr<MySDL> m_weak_sdl;
  std::function<void(const std::shared_ptr<MySDL> &)> m_callback;

public:
  MySDLEvent(const std::shared_ptr<MySDL> &,
             std::function<void(const std::shared_ptr<MySDL> &)>);
  ~MySDLEvent();
  MySDLEvent(const MySDLEvent &) = delete;
  MySDLEvent &operator=(const MySDLEvent &) = delete;

  MySDLEvent(MySDLEvent &&);
  MySDLEvent &operator=(MySDLEvent &&);

  /* 函数对象 */
  inline void operator()() {
  auto ptr = m_weak_sdl.lock();
  if (ptr != nullptr) {
    m_callback(ptr);
  }
}
};
}; // namespace HF