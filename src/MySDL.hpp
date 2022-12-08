#pragma once

#include "MySDLEvent.hpp"
#include "MySDLRender.hpp"
#include "MySDLSurface.hpp"
#include "MySDLTTFFont.hpp"
#include "MySDLWindow.hpp"

#include <atomic>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace HF {
class MySDL : public std::enable_shared_from_this<MySDL> {
  MySDLWindow m_window;
  MySDLSurface m_surface;
  std::shared_ptr<MySDLRender> m_render;
  std::shared_ptr<MySDLTTFFont> m_ttf;

  // std::unordered_map<uint32_t, MySDLEvent> m_events;
  std::unordered_map<uint32_t, std::vector<MySDLEvent>> m_events;

  std::vector<std::move_only_function<void()>> m_task_peerloop;

  std::vector<std::move_only_function<void()>> m_once_task;

  std::atomic_flag quit = false;

  void initAudio();

public:
  MySDL(uint32_t initType = SDL_INIT_VIDEO);
  ~MySDL();

  MySDL(const MySDL &) = delete;
  MySDL &operator=(const MySDL &) = delete;

  void CreateWindow(const char *title, int xPos, int yPos, int width,
                    int height, uint32_t flags);

  void CreateRenderer(uint32_t);

  void CreateTTFFont(const std::string &, int);

  /* 依赖于内部的m_window != nullptr */
  void LoadOrChangeMediaSurface(const std::string &);

  void LoadOrChangeMediaSurfaceWithConvert(const std::string &);

  /* display surface, src = m_surface, 即上下文在MySDL这个类中定义了,
   * 是否有更好的方案 */
  void UpdateSurface() const;

  void DisplayRender() const;

  /* 目前提供修改dst surface的stretch rect接口 */
  void ScaledSurface(int xPos, int yPos, int width, int height) const;

  static void Delay(int timeMS);

  void LoopAndWaitEvent();

  void StopLoop();

  void Display() const;

  size_t RegisterEvent(uint32_t, MySDLEvent::MySDLEventCallbackType);

  void UnRegisterEvent(uint32_t);

  /* 对应事件的第index下标的闭包 */
  void UnRegisterEvent(uint32_t, size_t);

  SDL_Renderer *getRendererPtr() const;

  std::shared_ptr<MySDLRender> getRendererSharedPtr() const;

  std::shared_ptr<MySDLTTFFont> getTTFFontSharedPtr() const;

  void addPeerLoopTask(std::move_only_function<void()>);
};
}; // namespace HF