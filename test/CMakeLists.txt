add_custom_target(tlocposix_test_headers SOURCES tlocposix_test.h)

add_executable(tlocposix_test socket_test.c thread_test.c tlocposix_test.c)
target_include_directories(tlocposix_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tlocposix_test PRIVATE tloc tlocposix)

add_test(NAME tlocposix_test COMMAND tlocposix_test)
