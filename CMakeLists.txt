cmake_minimum_required(VERSION 3.2)

project(Metawork1 VERSION 3.7.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

file(GLOB META_SRC_FILES
     "src/*.cpp" 
     "include/*.hpp"
)

include_directories(include)
add_compile_options(-Wall -Wextra -Wpedantic -Isystem)

# set(META_SRC_FILES 
#     test.cpp
#     ExtractFirstError.cpp
# )



add_executable(${PROJECT_NAME} ${META_SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
