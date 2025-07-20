cmake_minimum_required(VERSION 3.20)
project(core_cpp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

find_package(pybind11 REQUIRED)



include_directories(${CMAKE_SOURCE_DIR}/include)


add_library(engine
    src/engine/engine.cpp
)
target_include_directories(engine PUBLIC include)
target_link_libraries(engine PRIVATE pybind11::pybind11)

add_library(ops
    src/ops/ops.cpp
)
target_include_directories(ops PUBLIC include)
target_link_libraries(ops PRIVATE pybind11::pybind11)

add_library(tensor
    src/tensor/tensor.cpp
    src/tensor/dtype.cpp
)
target_include_directories(tensor PUBLIC include)
target_link_libraries(tensor PRIVATE pybind11::pybind11)

add_library(graph
  src/graph/graph.cpp
  src/graph/ir.cpp
  src/graph/fusion.cpp
)
target_include_directories(graph PUBLIC include)
target_link_libraries(graph PRIVATE pybind11::pybind11)


pybind11_add_module(core_cpp bindings/pybind.cpp)
target_link_libraries(core_cpp PRIVATE engine)
target_link_libraries(core_cpp PRIVATE graph)
target_link_libraries(core_cpp PRIVATE ops)
target_link_libraries(core_cpp PRIVATE tensor)

target_include_directories(core_cpp PRIVATE ${CMAKE_SOURCE_DIR}/include)





