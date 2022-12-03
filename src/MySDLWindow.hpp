#pragma once

class SDL_Window;

namespace HF {
class MySDLWindow {
  SDL_Window *m_window;

public:
  MySDLWindow();
  MySDLWindow(const char *title, int x, int y, int w, int h, uint32_t flags);

  ~MySDLWindow();

  MySDLWindow(const MySDLWindow &) = delete;

  MySDLWindow &operator=(const MySDLWindow &) = delete;

  MySDLWindow(MySDLWindow &&);

  MySDLWindow &operator=(MySDLWindow &&);
};
} // namespace HF