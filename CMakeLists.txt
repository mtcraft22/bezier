cmake_minimum_required(VERSION 3.26.4)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-12")
project(Curvas DESCRIPTION "curvas bezier" LANGUAGES CXX)
find_package(SDL2 REQUIRED)
add_executable(${PROJECT_NAME} 
    ${PROJECT_SOURCE_DIR}/src/Rectangle.cpp
    ${PROJECT_SOURCE_DIR}/src/Triangle.cpp
    ${PROJECT_SOURCE_DIR}/src/curve.cpp
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/circle.cpp
    ${PROJECT_SOURCE_DIR}/src/Node.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 )