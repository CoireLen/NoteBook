cmake_minimum_required(VERSION 3.14.0)
project(P2 VERSION 0.1.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include_directories(${CONAN_SRC_DIRS_IMGUI})

add_executable(P2 main.cpp ${CONAN_SRC_DIRS_IMGUI}/imgui_impl_dx9.h ${CONAN_SRC_DIRS_IMGUI}/imgui_impl_dx9.cpp 
${CONAN_SRC_DIRS_IMGUI}/imgui_impl_win32.h ${CONAN_SRC_DIRS_IMGUI}/imgui_impl_win32.cpp)

target_link_libraries(P2  ${CONAN_LIBS} d3d9)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
