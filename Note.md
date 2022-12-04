# 笔记

# LESSON 01 [环境配置]

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


# LESSON 02 [USE SDL SURFACE]
SDL SURFACE是一个图像数据类型, 它包含了所有图像的所有需要渲染的pixel. 这个渲染是通过CPU来做的, 而非GPU. SURFACE依赖于WindowSurface.

```shell
window -> SDL_GetWindowSurface -> (渲染) -> SDL_BlitSurface(surface_ptr, nullptr, window_ptr, nullptr) & SDL_UpdateWindowSurface(刷新屏幕)

图片 -> surface
```

# LESSON 03 [事件驱动编程]
这里, 可以使用SDL为我们封装好的```SDL_Event```结构体来处理类似于**按键**、**鼠标移动**、**joy button press**等事件. 可以参考之前做过的网络编程项目, 里头使用到的epoll和这个非常相似. 该教程可优化的地方在于可以像网络编程项目一样, 额外创建线程去处理对应的事件, 当然, 需要处理好竞争问题. 在事件处理时, 是否应该将事件封装为一个类, 然后将MySDL的弱引用传递到其中, 然后便于更新状态.

这里重新实现了```MySDLEvent```, 使用一个简单的```unordered_map```容器来处理不同的事件和对应的回调, 也许后续会因为事件的复杂&变化重新设计容器, 事件和对应的回调接口暂时使用```std::function<void(const std::shared_ptr<MySDL> &)>```类型.

# LESSON 04 [键盘事件]
键盘事件相对简单, 其实就是处理SDL的```SDL_KEYDOWN```类型的事件, 事件源内附有对应的按键的动作(按下但没松开/松开/重复/长按等). 复用上一章节的代码即可. 这里需要修改上一章节的接口, 应需要额外传入事件源的信息. 这里更新了回调接口```std::function<void(const std::shared_ptr<MySDL> &, const SDL_Event &)>```.

潜在问题: 这里每次切换按键时, 都需要重新从磁盘load文件进内存, 是否应该做一个类似缓存一样的操作, 即只load一次.

# LESSON 05 [surface的拉伸&屏幕适应]
按照Tutorial的样例, 需要队load bmp图片生成的```SDL_Surface *```做一次```SDL_ConvertSurface```转换, 将其转换为适应屏幕的```SDL_Surface *```, 这么做的目的是优化生成的```SDL_Surface *```所指向的对象.

另外, SDL还提供了图片Scale接口.