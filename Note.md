# 笔记

# LESSON 1 [环境配置]

这一小节主要是环境配置以及简单将SDL的一些类(比如SDL_Window)封装为RAII的类.

```
# 仅在Ubuntu20下测试
sudo apt -y upgrade
sudo apt install libsdl2-dev
```
## 1.1 CMake文件
在Ubuntu下比较方便, 直接使用```find_package(SDL2 REQUIRED)```, 然后链接时指定目录即可. 这里的头文件在```/usr/include/SDL2/```, lib文件路径在```/usr/lib/x86_64-linux-gnu```

## 1.2 内存泄漏
直接调用```SDL_Init()```然后调用```SDL_Quit()```是存在内存泄露的, 暂时先不处理.


# LESSON 2 [USE SDL SURFACE]
SDL SURFACE是一个图像数据类型, 它包含了所有图像的所有需要渲染的pixel. 这个渲染是通过CPU来做的, 而非GPU. SURFACE依赖于WindowSurface.

```shell
window -> SDL_GetWindowSurface -> (渲染) -> SDL_BlitSurface(surface_ptr, nullptr, window_ptr, nullptr) & SDL_UpdateWindowSurface(刷新屏幕)

图片 -> surface
```

# LESSON 3 [事件驱动编程]
这里, 可以使用SDL为我们封装好的```SDL_Event```结构体来处理类似于**按键**、**鼠标移动**、**joy button press**等事件. 可以参考之前做过的网络编程项目, 里头使用到的epoll和这个非常相似. 该教程可优化的地方在于可以像网络编程项目一样, 额外创建线程去处理对应的事件, 当然, 需要处理好竞争问题. 在事件处理时, 是否应该将事件封装为一个类, 然后将MySDL的弱引用传递到其中, 然后便于更新状态.

这里重新实现了```MySDLEvent```, 使用一个简单的```unordered_map```容器来处理不同的事件和对应的回调, 也许后续会因为事件的复杂&变化重新设计容器, 事件和对应的回调接口暂时使用```std::function<void(const std::shared_ptr<MySDL> &)>```类型.