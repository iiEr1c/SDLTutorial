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

使用的CPU渲染, 而非GPU.

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

# LESSON 06 [SDL_Image]

使用SDL_image加载其他格式(png)图片.

```shell
sudo apt install libsdl2-image-dev
```

CMake需要添加
find_package(SDL2_image REQUIRED)
头文件&链接也需要额外添加
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(Exe ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

## reference
+ [SDL环境配置](https://github.com/trenki2/SDL2Test)

# LESSON 07 [如何使用SDL加载PNG图片]

GPU渲染.

使用SDL_Renderer渲染SDL_Texture.
注意: 使用SDL_Render时, 首先需要初始化```SDL_SetRenderDrawColor(...)```, 其次需要```IMG_Init(IMG_INIT_PNG)```初始化PNG(也许我理解有误). 然后才能正常的渲染.

# LESSON 08 [Geometry Rendering]
几何渲染, 类似于之前学的OpenGL. 和OpenGL类似, 对于屏幕而言, 左上角为起点.

这里简单的使用按键来做图形的渲染.

对于Render来说, 有颜色、形状、甚至可以texture属性, 更新状态然后刷新即可显示出来.

# LESSON 09 [viewpoint]
修改render现实的二维位置, 另外, viewpoint是有状态的, 也就是说当我们前一次render设置viewport时, 如果后续不做调整, 那么仍然是原来的位置. 比如代码里先按其他按键, 此时viewpoint是整个屏幕, 后续按下↑时设置为左上位置, 此时再按其他键, 仍然是在左上角渲染.

对于texture来说, 是否应该添加一个容器存储texture对象, 而非每次都需要从磁盘导入文件.

# LESSON 10 [Color key]
在屏幕上渲染多个图像时, 我们通常需要具有透明背景的图片.API: ```SDL_SetColorKey```.

在render时, 一定要注意render是有状态的, 且是可以叠加的, 因此需要注意渲染的顺序, 比如这里的应该先渲染background, 再渲染前景, 如果反过来则看不到.

# LESSON 11 [渲染部分texture, 而非整个texture]

这一章节的意思是复用texture, 一个texture可以被render到指定的位置&拉伸(通过4元组{xPos, yPos, width, height}).

# LESSON 12 [Color Modulation]
修改texture颜色, 本质是修改rgb三个分量的值以改变颜色, 如果是其他定义?(比如YUV格式, 那么也许有另外的做法, 但原理应该类似?)

# LESSON 13 [透明度]
修改texture的透明度(alpha), 其实就是对API(```SDL_SetTextureAlphaMod```)的使用.

# LESSON 14 [生成动画]
通过短时间内渲染图片让眼睛错认为是动画.教程里提示需要在创建windows时添加flag:```SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC```

本质上其实就是可以custom specify input texture's rectangle.(见MySDLTexture::render函数)

这里遇到一个问题(貌似C++23的std::move_only_function可以解决,~~我也不确定~~:

```C++
#include <functional>

struct Object {
  Object() {}
  ~Object() {}
  Object(const Object &) = delete;
  Object &operator=(const Object &) = delete;
  Object(Object &&) noexcept {}
  Object &operator=(Object &&) noexcept { return *this; }
};

void func(std::function<void()> fn) {
  fn();
  fn();
}

/* g++编译则会报错 */
int main() {
  Object obj;
  auto tmp = std::move(obj); // 编译不会报错
  func([obj = std::move(obj)]() {}); // g++编译则会报错
  return 0;
}
```

解决方案是使用std::shared_ptr做proxy, 因为std::shared_ptr是copyable的, 即可通过编译, 但多复制了一次(当然可以捕获引用, 但目的是构造闭包, 引用捕获则需要考虑悬垂引用的问题)

# LESSON 15 [旋转和翻转]

这一章节主要介绍SDL的api ```SDL_RenderCopyEx```, api包括旋转的角度和是否要翻转, 翻转的选项包括: 不翻转/水平/竖直三种.

```C++
int SDL_RenderCopyEx(SDL_Renderer *renderer, SDL_Texture *texture, const SDL_Rect *srcrect, const SDL_Rect *dstrect, const double angle, const SDL_Point *center, const SDL_RendererFlip flip);
```

# LESSON 16 [True Type Font]
安装SDL2TTF扩展:
```shell
sudo apt -y install libsdl2-ttf-dev
```
更新配置文件:
```shell
# cmake configuration
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
```

在处理本章节时, 重构了MySDLTexture类, 然后增加了对font的显示.

## reference
+ [TrueType](https://en.wikipedia.org/wiki/TrueType)
+ [ubuntu SDLttf cmakelists](https://stackoverflow.com/questions/58107854/cmake-is-unable-to-find-sdl2-ttf-im-trying-to-link-it-the-same-way-i-would-wit)