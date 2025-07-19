cmake_minimum_required(VERSION 3.20)
project(core_cpp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(pybind11 REQUIRED)



include_directories(${CMAKE_SOURCE_DIR}/include)


add_library(engine
    src/engine/engine.cpp
)
target_include_directories(engine PUBLIC include)


pybind11_add_module(core_cpp bindings/pybind.cpp)
target_link_libraries(core_cpp PRIVATE engine)

target_include_directories(core_cpp PRIVATE ${CMAKE_SOURCE_DIR}/include)





