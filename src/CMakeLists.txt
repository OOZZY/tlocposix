add_library(tlocposix STATIC socket.c thread.c)
target_include_directories(tlocposix PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(tlocposix PUBLIC _POSIX_C_SOURCE=200809L)
target_link_libraries(tlocposix PUBLIC Threads::Threads)
