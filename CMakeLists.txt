cmake_minimum_required (VERSION 3.8)

project ("sdltest")

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable (sdltest "main.cpp"    "engine/Vec.h"  "engine/App.h"  "engine/App.cpp" "engine/Render.h" "engine/Render.cpp" "engine/Color.h" "engine/Color.cpp"  "engine/Run.cpp"   "engine/RenderEngine.h" "engine/RenderEngine.cpp")
target_link_libraries(sdltest ${SDL2_LIBRARIES})
