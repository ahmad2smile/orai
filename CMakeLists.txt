cmake_minimum_required(VERSION 3.25)
project(orai)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

link_directories(${SFML_LIBRARY_DIRS})

configure_file(assets/FiraCodeNerdFont-Light.ttf ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(${PROJECT_NAME} src/main.cpp
        src/UI/App.h
        src/UI/App.cpp
        src/UI/Components/Input.cpp
        src/UI/Components/Input.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
