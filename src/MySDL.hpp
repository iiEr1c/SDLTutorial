#pragma once

#include "SDL.h"

#include "MySDLEvent.hpp"
#include "MySDLSurface.hpp"
#include "MySDLWindow.hpp"

#include <atomic>
#include <memory>
#include <string>
#include <unordered_map>

namespace HF {
class MySDL : public std::enable_shared_from_this<MySDL> {
  MySDLWindow m_window;
  MySDLSurface m_surface;
  std::unordered_map<uint32_t, MySDLEvent> m_events;

  std::atomic_flag quit = false;

public:
  MySDL(uint32_t initType = SDL_INIT_VIDEO);
  ~MySDL();

  MySDL(const MySDL &) = delete;
  MySDL &operator=(const MySDL &) = delete;

  void CreateWindow(const char *title, int xPos, int yPos, int weight,
                    int height, uint32_t flags);

  /* 依赖于内部的m_window != nullptr */
  void LoadOrChangeMediaSurface(const std::string &);

  /* display surface */
  void DisplaySurface() const;

  static void Delay(int timeMS);

  void LoopAndWaitEvent();

  void StopLoop();

  void RegisterEvent(uint32_t, MySDLEvent::MySDLEventCallbackType);

  void UnRegisterEvent(uint32_t);
};
}; // namespace HF