cmake_minimum_required(VERSION 3.15)
project(Pinecone VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# SDL2 and OpenGL as before
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ASSIMP REQUIRED)

# Include GLM headers from extern/glm
include_directories(extern/glm)

include_directories(${SDL2_INCLUDE_DIRS} include)

add_subdirectory(extern/glad)

add_executable(Pinecone
  pinecone/main.cpp
)

target_link_libraries(Pinecone
  ${SDL2_LIBRARIES}
  OpenGL::GL
  glad
)

target_include_directories(Pinecone PRIVATE extern/glad/include)
