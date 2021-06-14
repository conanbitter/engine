cmake_minimum_required(VERSION 3.16)

project(engine VERSION 0.1 LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ./${CMAKE_BUILD_TYPE})

find_package(SDL2 REQUIRED)
find_package(glLoadGen REQUIRED)
find_package(STB REQUIRED)

add_executable(engine
    ${GL_LOAD_GEN_DIR}/gl/gl_core_3_2.cpp
    src/main.cpp
    src/app.hpp
    src/app.cpp
    src/shaders.hpp
    src/shaders.cpp
    src/spritebatch.hpp
    src/spritebatch.cpp
)

target_include_directories(engine
    PUBLIC
        ${GL_LOAD_GEN_DIR}
        ${SDL2_INCLUDE_DIR_64}
        ${STB_INCLUDE_DIR}
)

target_link_directories(engine
    PUBLIC
        ${SDL2_LIBRARY_64}
)

target_link_libraries(engine
    SDL2
    opengl32
)

#target_link_options(engine PRIVATE -mwindows -static -s)
#target_link_options(engine PRIVATE -s)