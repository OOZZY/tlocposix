cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project("tlocposix")
enable_testing()

# - pthreads required
# - see https://cmake.org/cmake/help/v3.6/module/FindThreads.html
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# - tloc required
add_subdirectory(tloc)
include_directories(tloc)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  set(flags "-std=c11 -pedantic -Wall -Wextra -Werror")
  if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set(flags "${flags} -Weverything -Wno-cast-align")
  endif()
  set(debug_flags "-g")
  #set(debug_flags "-g -fsanitize=address -fsanitize=undefined -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls")
  #set(debug_flags "-g -fsanitize=memory -fsanitize=undefined -O1 -fno-omit-frame-pointer -fno-optimize-sibling-calls")
else()
  set(flags "${CMAKE_C_FLAGS}")
  set(debug_flags "${CMAKE_C_FLAGS_DEBUG}")
endif()

message(STATUS "tlocposix setting flags")
set(CMAKE_C_FLAGS "${flags}" CACHE STRING
    "Flags used by the compiler during all build types." FORCE)
set(CMAKE_C_FLAGS_DEBUG "${debug_flags}" CACHE STRING
    "Flags used by the compiler during debug builds." FORCE)

add_definitions(-D_POSIX_C_SOURCE=200809L)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(tlo)
add_executable(tlocposix_test socket_test.c thread_test.c tlocposix_test.c)
target_link_libraries(tlocposix_test tloc tlocposix)
add_test(tlocposix_test tlocposix_test)
