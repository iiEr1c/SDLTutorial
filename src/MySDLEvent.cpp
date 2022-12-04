#include "MySDLEvent.hpp"
#include "MySDL.hpp"

#include <utility>

namespace HF {
MySDLEvent::MySDLEvent(const std::shared_ptr<MySDL> &ptr,
                       MySDLEventCallbackType func)
    : m_weak_sdl(ptr), m_callback(std::move(func)) {}

MySDLEvent::~MySDLEvent() {}

MySDLEvent::MySDLEvent(MySDLEvent &&rhs)
    : m_weak_sdl(std::move(rhs.m_weak_sdl)),
      m_callback(std::move(rhs.m_callback)) {}

MySDLEvent &MySDLEvent::operator=(MySDLEvent &&rhs) {
  m_weak_sdl = std::move(rhs.m_weak_sdl);
  m_callback = std::move(rhs.m_callback);
  return *this;
}

}; // namespace HF