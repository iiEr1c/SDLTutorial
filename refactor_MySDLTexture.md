# 重构MySDLTexture

最开始的MySDLTexture可以加载png图片然后生成texture, 因为在跟着教程实现ttf texture时, 发现这两个texture之间的细节是不一样的, 然后一开始想着直接使用继承的方式实现, 一开始没有将render定义为virtual function, 但是如果是非虚的render函数, 那么就没法将texture对象放入容器中从而实现运行时的多态了(因为我们可以有多个texture, 比如从背景开始, 已知往上叠加图层, 就像ps里头那样.).除了虚函数外, 也可以使用std::variant来实现, 但是每当我们增加新的类时, 需要向std::variant中添加, 否则会编译出错. 当然也可以使用std::any接口.

这里尝试使用reference[1]中的方案. 以下是一个小demo.

```C++
#include <functional>
#include <iostream>
#include <memory>

struct TextureMessenger {
  using QuantificationBound = auto(int, int) -> void;
  std::move_only_function<QuantificationBound> m_func = {};

  TextureMessenger() = default;
  TextureMessenger(auto x) {
    m_func = [x = std::move(x)](int xPos, int yPos) mutable {
      x.render(xPos, yPos);
    };
  }

  auto render(int xPos, int yPos) -> void { m_func(xPos, yPos); }
};

struct A {
  std::unique_ptr<int> ptr;
  A() {}
  A(int a) : ptr(std::make_unique<int>(a)) {}
  ~A() {}
  A(const A &) = delete;
  A &operator=(const A &) = delete;
  A(A &&rhs) : ptr(std::move(rhs.ptr)) {}
  A &operator=(A &&rhs) {
    ptr = std::move(rhs.ptr);
    return *this;
  }

  void render(int a, int b) const {
    std::cout << "A::render, ";
    std::cout << *ptr << ", ";
    std::cout << a << '\t' << b << '\n';
  }
};

struct B {
  std::unique_ptr<int> ptr;
  B() {}
  B(int b) : ptr(std::make_unique<int>(b)) {}
  ~B() {}
  B(const B &) = delete;
  B &operator=(const B &) = delete;
  B(B &&rhs) : ptr(std::move(rhs.ptr)) {}
  B &operator=(B &&rhs) {
    ptr = std::move(rhs.ptr);
    return *this;
  }

  void render(int a, int b) const {
    std::cout << "B::render, ";
    std::cout << *ptr << ", ";
    std::cout << a << '\t' << b << '\n';
  }
};

// g++ test.cpp -std=c++23
int main() {
  A a(1);
  B b(2);
  TextureMessenger adot(std::move(a));
  TextureMessenger bdot(std::move(b));
  for (int i = 0; i < 16; ++i) {
    adot.render(i, i + 1);
    bdot.render(i * i, i * i + 1);
  }
}
```

# reference
+ [existential type.cxx](https://github.com/IFeelBloated/Type-System-Zoo/blob/master/existential%20type.cxx)