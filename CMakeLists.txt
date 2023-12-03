cmake_minimum_required(VERSION 3.21)

project(LuaTest)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "-std=c++20")
else()
    set(CXX_STANDARD 20)
    set(CXX_STANDARD_REQUIRED ON)
endif()

add_executable(${PROJECT_NAME} main.cpp)

include(FetchContent)

message(STATUS "Fetching Selene...")

FetchContent_Declare(
    Selene
    GIT_REPOSITORY https://github.com/razerx100/Selene.git
    GIT_TAG master
)

FetchContent_MakeAvailable(Selene)
message("Fetched Selene.")

target_link_libraries(${PROJECT_NAME} PRIVATE Selene)
target_include_directories(${PROJECT_NAME} PUBLIC Selene)