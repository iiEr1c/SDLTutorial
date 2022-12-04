#include "SDL.h"
#include <fmt/core.h>

#include "MySDL.hpp"

namespace HF {
MySDL::MySDL(uint32_t initType) { SDL_Init(initType); }

MySDL::~MySDL() { SDL_Quit(); }

void MySDL::CreateWindow(const char *title, int xPos, int yPos, int weight,
                         int height, uint32_t flags) {
  m_window = MySDLWindow(title, xPos, yPos, weight, height, flags);
}

void MySDL::Delay(int timeMS) { SDL_Delay(timeMS); }

void MySDL::LoadOrChangeMediaSurface(const std::string &path) {
  m_surface = MySDLSurface(path);
  if (!m_surface.available()) {
    fmt::print("cann't load {} file\n", path);
  }
}

void MySDL::DisplaySurface() const {
  if (m_window.available() && m_surface.available()) {
    SDL_BlitSurface(m_surface.getSurfacePtr(), nullptr,
                    SDL_GetWindowSurface(m_window.getWindowPtr()), nullptr);
    SDL_UpdateWindowSurface(m_window.getWindowPtr());
  }
}

void MySDL::LoopAndWaitEvent() {
  SDL_Event event;
  while (!quit.test()) {
    while (SDL_PollEvent(&event) != 0) {
      /* handle event */
      if (auto iter = m_events.find(event.type); iter != m_events.end()) {
        iter->second(event);
      }
    }

    DisplaySurface();
  }
}

void MySDL::StopLoop() {
  quit.test_and_set();
  quit.notify_all();
}

void MySDL::RegisterEvent(uint32_t sdlEventType,
                          MySDLEvent::MySDLEventCallbackType callback) {
  MySDLEvent event{shared_from_this(), std::move(callback)};
  m_events.insert_or_assign(sdlEventType, std::move(event));
}

void MySDL::UnRegisterEvent(uint32_t sdlEventType) {
  m_events.erase(sdlEventType);
}

}; // namespace HF