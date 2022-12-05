#include "SDL.h"
#include <fmt/core.h>
#include <fmt/format.h>

#include "MySDL.hpp"

namespace HF {
MySDL::MySDL(uint32_t initType) { SDL_Init(initType); }

MySDL::~MySDL() { SDL_Quit(); }

void MySDL::CreateWindow(const char *title, int xPos, int yPos, int weight,
                         int height, uint32_t flags) {
  m_window = MySDLWindow(title, xPos, yPos, weight, height, flags);
}

void MySDL::CreateRenderer() {
  if (m_window.available()) {
    m_render = std::make_shared<MySDLRender>(m_window.getWindowPtr());
  } else {
    fmt::print("please create window before create render.\n");
  }
}

void MySDL::Delay(int timeMS) { SDL_Delay(timeMS); }

void MySDL::LoadOrChangeMediaSurface(const std::string &path) {
  m_surface = MySDLSurface(path);
  if (!m_surface.available()) {
    fmt::print("cann't load {} file\n", path);
  }
}

void MySDL::LoadOrChangeMediaSurfaceWithConvert(const std::string &path) {
  auto tmp = MySDLSurface(path);
  if (!tmp.available()) {
    fmt::print("cann't load {} file\n", path);
    return;
  }

  if (m_window.available()) {
    SDL_Surface *window_surface = SDL_ConvertSurface(
        tmp.getSurfacePtr(), m_window.getWindowSurfacePtr()->format, 0);
    if (window_surface != nullptr) {
      m_surface = MySDLSurface(window_surface);
    }
  }
}

void MySDL::UpdateSurface() const {
  if (m_window.available() && m_surface.available()) {
    SDL_BlitSurface(m_surface.getSurfacePtr(), nullptr,
                    m_window.getWindowSurfacePtr(), nullptr);
  }
}

void MySDL::DisplayRender() const {
  if (m_render != nullptr && m_render->available()) {
    SDL_RenderPresent(m_render->getRendererPtr());
  }
}

void MySDL::ScaledSurface(int xPos, int yPos, int weight, int height) const {
  if (m_window.available() && m_surface.available()) {
    SDL_Rect stretchRect{.x = xPos, .y = yPos, .w = weight, .h = height};
    SDL_BlitScaled(m_surface.getSurfacePtr(), nullptr,
                   m_window.getWindowSurfacePtr(), std::addressof(stretchRect));
  }
}

void MySDL::Display() const {
  SDL_UpdateWindowSurface(m_window.getWindowPtr());
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

    // SDL_RenderPresent(m_render->getRendererPtr());
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

SDL_Renderer *MySDL::getRendererPtr() const {
  return m_render->getRendererPtr();
}

std::shared_ptr<MySDLRender> MySDL::getRendererSharedPtr() const {
  return m_render;
}
}; // namespace HF