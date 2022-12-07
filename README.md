# SDLTutorial
learn SDL

# 环境配置

```
# 仅在Ubuntu 22.04环境测试通过
sudo apt -y upgrade # upgrade systemd
sudo apt -y install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
sudo snap install cmake --classic
```

更新gcc版本为gcc12
```shell
sudo apt -y install gcc-12 g++-12
# 设置默认版本
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 100
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-12 100
```

# reference
+ [Beginning Game Programming v2.0](https://lazyfoo.net/tutorials/SDL/)
