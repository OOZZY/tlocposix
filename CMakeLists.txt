cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project("tlocposix")
enable_testing()

# - pthreads required
# - see https://cmake.org/cmake/help/v3.6/module/FindThreads.html
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# - tloc required
add_subdirectory(tloc)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  set(warning_compile_options -pedantic -Wall -Wextra -Werror)
endif()

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  set(warning_compile_options ${warning_compile_options} -Weverything)
endif()

add_subdirectory(src)
add_subdirectory(test)
