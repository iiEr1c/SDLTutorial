#pragma once

#include "MySDLEvent.hpp"
#include "MySDLRender.hpp"
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
  std::shared_ptr<MySDLRender> m_render;

  std::unordered_map<uint32_t, MySDLEvent> m_events;

  std::atomic_flag quit = false;

public:
  MySDL(uint32_t initType = SDL_INIT_VIDEO);
  ~MySDL();

  MySDL(const MySDL &) = delete;
  MySDL &operator=(const MySDL &) = delete;

  void CreateWindow(const char *title, int xPos, int yPos, int weight,
                    int height, uint32_t flags);

  void CreateRenderer();

  /* 依赖于内部的m_window != nullptr */
  void LoadOrChangeMediaSurface(const std::string &);

  void LoadOrChangeMediaSurfaceWithConvert(const std::string &);

  /* display surface, src = m_surface, 即上下文在MySDL这个类中定义了,
   * 是否有更好的方案 */
  void UpdateSurface() const;

  void DisplayRender() const;

  /* 目前提供修改dst surface的stretch rect接口 */
  void ScaledSurface(int xPos, int yPos, int weight, int height) const;

  static void Delay(int timeMS);

  void LoopAndWaitEvent();

  void StopLoop();

  void Display() const;

  void RegisterEvent(uint32_t, MySDLEvent::MySDLEventCallbackType);

  void UnRegisterEvent(uint32_t);

  SDL_Renderer *getRendererPtr() const;

  std::shared_ptr<MySDLRender> getRendererSharedPtr() const;
};
}; // namespace HF