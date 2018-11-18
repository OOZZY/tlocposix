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
  set(global_compile_options -pedantic -Wall -Wextra -Werror)
endif()

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
  set(global_compile_options ${global_compile_options} -Weverything)
endif()

option(COLORED_DIAGNOSTICS "Tell the compiler to use colors in diagnostics (GNU/Clang only)." ON)
if (${COLORED_DIAGNOSTICS})
  if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(global_compile_options ${global_compile_options} -fdiagnostics-color)
  elseif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set(global_compile_options ${global_compile_options} -fcolor-diagnostics)
  endif()
endif()

add_subdirectory(src)
add_subdirectory(test)
