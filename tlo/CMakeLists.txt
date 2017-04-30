add_library(tlocposix STATIC socket.c thread.c)
target_link_libraries(tlocposix ${CMAKE_THREAD_LIBS_INIT})
