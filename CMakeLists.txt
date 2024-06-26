cmake_minimum_required(VERSION 3.19)
project(orai)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER=clang)

include(./vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

link_directories(${SFML_LIBRARY_DIRS})

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE TESTS tests/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

configure_file(assets/FiraCodeNerdFont-Light.ttf ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERs}
        src/UI/Components/Scrollable.cpp
        src/UI/Components/Scrollable.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

enable_testing()

#add_subdirectory(libs/fuzztest)

find_package(SFML REQUIRED COMPONENTS system window graphics)

#fuzztest_setup_fuzzing_flags()

add_executable(test_target ${TESTS} ${SOURCES} ${HEADERs})

target_include_directories(test_target PRIVATE ${SFML_INCLUDE_DIRS})
target_link_libraries(test_target PRIVATE GTest::gtest GTest::gtest_main sfml-system sfml-window sfml-graphics)

include(GoogleTest)

gtest_discover_tests(test_target)