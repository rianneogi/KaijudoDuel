cmake_minimum_required(VERSION 2.6)

project(DuelMasters3D)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# set(CMAKE_CXX_FLAGS "-Wall -Wextra -llua5.3 -lfreetype -lassimp -lSDL2main -lSDL2 -lGLEW -lGLU -lGL")
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3")

SET(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

# findopengl()
# if(OPENGL_FOUND)
#     include_directories(${OPENGL_INCLUDE_DIRS})
# endif()
# 
# find_package(GLEW REQUIRED)
# if(GLEW_FOUND)
#     include_directories(${GLEW_INCLUDE_DIRS})
# endif()
# 
# find_package(SDL2 REQUIRED)
# if(SDL2_FOUND)
#     include_directories(${SDL2_INCLUDE_DIRS})
# endif()
# 
# find_package(ASSIMP REQUIRED)
# if(ASSIMP_FOUND)
#     include_directories(${ASSIMP_INCLUDE_DIR})
# endif() 
# 
# find_package(FREETYPE REQUIRED)
# if(FREETYPE_FOUND)
#     include_directories(${FREETYPE_INCLUDE_DIRS})
# endif() 

include_directories("/home/rian/Code/Libraries/DevIL/DevIL/include")
include_directories("/usr/include/assimp")
include_directories("/usr/include/freetype2")
link_directories("/home/rian/Code/Libraries/DevIL/DevIL/build/lib/x64")

file(GLOB SOURCE_FILES
    Source/*.cpp
)

add_executable(DuelMasters3D ${SOURCE_FILES})
# target_link_libraries(DuelMasters3D ${ASSIMP_LIBRARY})
target_link_libraries(DuelMasters3D libIL.so)
target_link_libraries(DuelMasters3D libILU.so)
target_link_libraries(DuelMasters3D libILUT.so)
target_link_libraries(DuelMasters3D lua5.3)
target_link_libraries(DuelMasters3D freetype)
target_link_libraries(DuelMasters3D assimp)
target_link_libraries(DuelMasters3D SDL2)
target_link_libraries(DuelMasters3D SDL2main)
target_link_libraries(DuelMasters3D GLEW)
target_link_libraries(DuelMasters3D GLU)
target_link_libraries(DuelMasters3D GL)
target_link_libraries(DuelMasters3D pthread)
