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

# LESSON 17 [mouse event]

在最初的设计时, 对于事件处理的抽象是naive的, 具体的做法是: 具体的事件类型 -> 处理对应的回调. 这样的抽象方式有个问题, 就是如果不同的对象, 在相同的事件类型时, 需要有不同的回调, 从接口上, 则需要变成: 事件: 对象类型 -> 回调, 而非之前的那种包装方式: 事件类型 -> 一个将具体对象塞进function中的闭包(如果有n多个对象都需要这么做应该怎么办?). 那么应该如何处理呢? 变成这样的接口```std::unordered_map<uint32_t, std::vector<MySDLEvent>>```? 然后每当需要处理的事件时, 去遍历std::list中的所有闭包, 然后执行一遍. 然后在逻辑上则需要每个对象内部能够分辨该事件是来自本对象的触发. 比如我们定义了n个button, 那么当鼠标事件发生时, 根据鼠标的位置判断这个事件是否是作用在自己这个button上, 如果不是则跳过. 这样做的事件复杂度是O(n). 有没有更好的方案呢?

重新思考这个问题: 对于SDL来说, 它监听的是键盘/鼠标等事件, 官方的api接口是否存在类似的派发机制呢? 如果没有, 那么我们也许可以模仿epoll的做法, 如果SDL Event可以传入一个ptr, 那么我们在外部添加一个O(1)或者O(log(n))的容器记录ptr, 然后当事件发生时, 我们能够快速的找到对应的事件所需要执行的回调, 这一切的前提在于SDL Event是否可以传入一个ptr作为后续的判断, 但是目前没有找到类似的资料.

**todo: 尝试解决这个问题.**

现在暂时将接口修改为```std::unordered_map<uint32_t, std::vector<MySDLEvent>>```, 然后为为每一个对象都创一个闭包.

这里还得提供接口: 如何将具体对象从事件链表中剔除出去, 也许这里可以使用observer? 因为vector的有序性, 其实可以返回vector中的下标给用户, 如果需要解注册那么用这个下标即可. 这么一想是不是应该使用vector了, 毕竟动态性不是那么友好. 而是使用std::list, 将迭代器返回给用户, 因为迭代器也不会失效. 考虑到每次事件触发都要遍历, 先使用std::vector吧, 毕竟cache友好.

鼠标检测时, API ```SDL_GetMouseState```对于鼠标位置是基于对应window的相对位置(即相对于窗口左上角(0, 0)的相对位置).

鼠标事件包括:

+ SDL_MOUSEMOTION: 鼠标移动
+ SDL_MOUSEBUTTONDOWN: Mouse button pressed
+ SDL_MOUSEBUTTONUP: Mouse button released
+ SDL_MOUSEWHEEL: 滚轮事件

该章节其实介绍的是button的检测. button类应定义: 位置(矩形的话左上角到右下角)、贴图、对应的事件.

在渲染时, 不同的texture有先后顺序, 是否应该定义一个类似有向图的东西, 每次按照顺序render.

# LESSON 18 [Key States]

~~todo:~~ 处理Key combination, 无论是用之前的事件处理或者这里的Key States写法. => SDL_TextInputEvent(应该是这个). 这里设计上直接定义一个回调赛入loop循环中, 然后每次loop都扫描一次, 这样子做的问题是每次loop都会执行一次, 所以这是有问题的.

能否这么处理:

+ 每次将任务取出来, 执行一次, 然后塞回去? => 但是下一次loop仍然有问题.
+ 应该得加一个类似延时的功能?

## reference
+ [stackoverflow answer SDL_GetKeyboardState](https://stackoverflow.com/questions/1252976/how-to-handle-multiple-keypresses-at-once-with-sdl)

# LESSON 21 [Sound Effects and Music]

环境配置, 和SDL_Image类似. 具体配置更新在README.md中.

在输出声音时, 需要解决多种声音一起输出的问 => 

```
原因：主要是Mix_Music、Mix_LoadMUS()和Mix_Chunk、Mix_LoadWAV()的问题、播放一种声音用Mix_LoadMUS()即可，但是两种声音时可能会导致通道channel混乱问题导致声音混乱；

解决：将背景音乐用Mix_LoadMUS()加载和用Mix_PlayMusic播放；  其他动态声音用Mix_LoadWAV()加载和用Mix_PlayChannel播放，分开就好。
```

这里其实有一大堆的ifelse的问题, 应该考虑类似ioc的容器来处理, 即在其他地方注册 对应的按键->播放对应的音乐. 这里的带啊吗不方便维护, 其实可以类似之前的事件处理的方式, 增加一个register接口即可.

## reference
+ [Mix_PauseMusic api](https://wiki.libsdl.org/SDL_mixer/Mix_PauseMusic)

# LESSON 22 [Timer]

这一节其实就是```SDL_GetTicks```接口.
从之前的LESSON到现在的LESSON, 是否应该将texture组织成有向无环图, 然后每一次loop时渲染.