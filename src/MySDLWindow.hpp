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

  MySDLWindow(MySDLWindow &&) noexcept;

  MySDLWindow &operator=(MySDLWindow &&) noexcept;

  SDL_Window *getWindowPtr() const;

  SDL_Surface *getWindowSurfacePtr() const;

  bool available() const;
};
} // namespace HF