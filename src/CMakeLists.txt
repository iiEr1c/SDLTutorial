SET(MYSDL_HEAD
    "MySDL.hpp"
    "MySDLWindow.hpp"
    )

SET(MYSDL_SRC
    "MySDL.cpp"
    "MySDLWindow.cpp"
    )

add_library(MySDL ${MYSDL_HEAD} ${MYSDL_SRC})

target_include_directories(MySDL PUBLIC ./ ${SDL2_INCLUDE_DIRS})

target_link_libraries(MySDL PRIVATE ${SDL2_LIBRARIES} fmt::fmt)
