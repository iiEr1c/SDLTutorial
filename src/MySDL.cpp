#include "SDL.h"
#include "SDL_mixer.h"
#include <fmt/core.h>
#include <fmt/format.h>

#include "MySDL.hpp"

namespace HF {
void MySDL::initAudio() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    fmt::print("Failed to Open Audio.\n");
  }
}

MySDL::MySDL(uint32_t initType) {
  SDL_Init(initType);
  if ((initType & SDL_INIT_AUDIO) == SDL_INIT_AUDIO) {
    initAudio();
  }
}

MySDL::~MySDL() {
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}

void MySDL::CreateWindow(const char *title, int xPos, int yPos, int width,
                         int height, uint32_t flags) {
  m_window = MySDLWindow(title, xPos, yPos, width, height, flags);
}

void MySDL::CreateRenderer(uint32_t flag) {
  if (m_window.available()) {
    m_render = std::make_shared<MySDLRender>(m_window.getWindowPtr(), flag);
  } else {
    fmt::print("please create window before create render.\n");
  }
}

void MySDL::CreateTTFFont(const std::string &path, int color) {
  if (m_window.available()) {
    m_ttf = std::make_shared<MySDLTTFFont>(path.c_str(), color);
    if (!m_ttf->available()) [[unlikely]] {
      fmt::print("Failed to open ttf font file {}\n", path);
    }
  } else {
    fmt::print("please create window before create ttf font.\n");
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

void MySDL::ScaledSurface(int xPos, int yPos, int width, int height) const {
  if (m_window.available() && m_surface.available()) {
    SDL_Rect stretchRect{.x = xPos, .y = yPos, .w = width, .h = height};
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
        size_t closureObjSize = iter->second.size();
        for (size_t i = 0; i < closureObjSize; ++i) {
          iter->second[i](event);
        }
      }
    }

    /* execute PeerLoop's task */
    for (auto &func : m_task_peerloop) {
      func();
    }
    // SDL_RenderPresent(m_render->getRendererPtr());
  }
}

void MySDL::StopLoop() {
  quit.test_and_set();
  quit.notify_all();
}

size_t MySDL::RegisterEvent(uint32_t sdlEventType,
                            MySDLEvent::MySDLEventCallbackType callback) {
  MySDLEvent event{shared_from_this(), std::move(callback)};
  auto iter = m_events.find(sdlEventType);
  if (iter != m_events.end()) {
    iter->second.emplace_back(std::move(event));
    return iter->second.size() - 1;
  } else {
    std::vector<MySDLEvent> firstObject;
    firstObject.emplace_back(std::move(event));
    m_events.insert({sdlEventType, std::move(firstObject)});
    return 0;
  }
}

/* 不再关注该事件 */
void MySDL::UnRegisterEvent(uint32_t sdlEventType) {
  m_events.erase(sdlEventType);
}

void MySDL::UnRegisterEvent(uint32_t sdlEventType, size_t index) {
  auto iter = m_events.find(sdlEventType);
  if (iter != m_events.end()) {
    size_t size = iter->second.size();
    if (index < size) {
      iter->second.erase(iter->second.begin() + index);
    }
  }
}

SDL_Renderer *MySDL::getRendererPtr() const {
  return m_render->getRendererPtr();
}

std::shared_ptr<MySDLRender> MySDL::getRendererSharedPtr() const {
  return m_render;
}

std::shared_ptr<MySDLTTFFont> MySDL::getTTFFontSharedPtr() const {
  return m_ttf;
}

void MySDL::addPeerLoopTask(std::move_only_function<void()> task) {
  m_task_peerloop.emplace_back(std::move(task));
}
}; // namespace HF