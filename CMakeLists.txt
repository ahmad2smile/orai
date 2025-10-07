cmake_minimum_required(VERSION 3.28)
project(orai LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER=clang)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /experimental:module /std:c++latest")
endif ()

include_directories(.)
include(~/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(SFML 3 COMPONENTS System Window Network Graphics CONFIG REQUIRED)
find_package(SQLite3 REQUIRED)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

link_directories(${SFML_LIBRARY_DIRS})

file(GLOB_RECURSE SRCMODULES src/**/*.ixx)
file(GLOB_RECURSE SOURCES src/**/*.cpp)
file(GLOB_RECURSE TESTS tests/**/*.cpp)
file(GLOB_RECURSE HEADERS src/**/*.h)
file(COPY assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/assets)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})
target_sources(${PROJECT_NAME} PUBLIC FILE_SET cxx_modules TYPE CXX_MODULES FILES ${SRCMODULES})

target_link_libraries(${PROJECT_NAME} PRIVATE SQLite::SQLite3 SFML::Network SFML::Graphics SFML::Window SFML::System)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
include(CPack)

enable_testing()

add_executable(test_target ${TESTS} ${SOURCES} ${HEADERS} ${SRCMODULES})

target_include_directories(test_target PRIVATE ${SFML_INCLUDE_DIRS})
target_link_libraries(test_target PRIVATE GTest::gtest GTest::gtest_main SQLite::SQLite3 SFML::Network SFML::Graphics SFML::Window SFML::System)

include(GoogleTest)

gtest_discover_tests(test_target)