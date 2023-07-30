cmake_minimum_required(VERSION 3.2)

project(MetaLib VERSION 3.7.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(ENABLE_TEST ON CACHE BOOL "Enable the test")
#file(GLOB META_SRC_FILES
#     "src/*.cpp" 
#     "include/*.hpp"
#)

if(ENABLE_TEST)
    message("Testing enabled!!!")
    add_subdirectory(test)
endif()

include_directories(include)
add_compile_options(-Wall -Wextra -Wpedantic)


#add_executable(${PROJECT_NAME} ${META_SRC_FILES})
#target_include_directories(${PROJECT_NAME} PUBLIC include)
