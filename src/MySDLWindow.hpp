#pragma once

class SDL_Window;

namespace HF {
class MySDLWindow {
  SDL_Window *m_window = nullptr;

public:
  MySDLWindow();
  MySDLWindow(const char *title, int xPos, int yPos, int weight, int height,
              uint32_t flags);

  ~MySDLWindow();

  MySDLWindow(const MySDLWindow &) = delete;

  MySDLWindow &operator=(const MySDLWindow &) = delete;

  MySDLWindow(MySDLWindow &&);

  MySDLWindow &operator=(MySDLWindow &&);

  SDL_Window *getWindowPtr() const;

  bool available() const;
};
} // namespace HF