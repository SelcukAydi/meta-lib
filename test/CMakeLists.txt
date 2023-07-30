project(MetaLibTest VERSION 3.7.1 LANGUAGES CXX)

file(GLOB META_SRC_FILES
     "src/*.cpp" 
     "include/*.hpp"
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include_directories(include, ${CMAKE_SOURCE_DIR}/include)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(${PROJECT_NAME} ${META_SRC_FILES}) 
target_link_libraries(${PROJECT_NAME} GTest::gtest GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PUBLIC include ${CMAKE_SOURCE_DIR}/include)
