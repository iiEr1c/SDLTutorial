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
window -> SDL_GetWindowSurface -> (渲染) -> SDL_BlitSurface & SDL_UpdateWindowSurface(刷新屏幕)

图片 -> surface
```