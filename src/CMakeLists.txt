SET(MYSDL_HEAD
    "MySDL.hpp"
    "MySDLWindow.hpp"
    "MySDLSurface.hpp"
    "MySDLEvent.hpp"
    "MySDLRender.hpp"
    "PictureTexture.hpp"
    "MySDLTTFFont.hpp"
    "TTFFontTexture.hpp"
    "TextureMessenger.hpp"
    "Button.hpp"
    )

SET(MYSDL_SRC
    "MySDL.cpp"
    "MySDLWindow.cpp"
    "MySDLSurface.cpp"
    "MySDLEvent.cpp"
    "MySDLRender.cpp"
    "PictureTexture.cpp"
    "MySDLTTFFont.cpp"
    "TTFFontTexture.cpp"
    "Button.cpp"
    )

add_library(MySDL ${MYSDL_HEAD} ${MYSDL_SRC})

target_include_directories(MySDL PUBLIC ./
    ${SDL2_INCLUDE_DIRS}
    ${SDL2IMAGE_INCLUDE_DIRS}
    ${SDL2TTF_INCLUDE_DIRS}
    ${SDL2MIXER_INCLUDE_DIRS}
    )

target_link_libraries(MySDL PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2IMAGE_LIBRARIES}
    ${SDL2TTF_LIBRARIES}
    ${SDL2MIXER_LIBRARIES}
    fmt::fmt
    )
