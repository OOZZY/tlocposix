set(tlocposix_test_headers tlocposix_test.h)
set(tlocposix_test_sources socket_test.c thread_test.c tlocposix_test.c)
add_executable(tlocposix_test ${tlocposix_test_headers} ${tlocposix_test_sources})
set_target_properties(tlocposix_test PROPERTIES C_EXTENSIONS OFF)
target_compile_options(tlocposix_test PRIVATE ${global_compile_options})
target_include_directories(tlocposix_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tlocposix_test PRIVATE tloc tlocposix)

add_test(NAME tlocposix_test COMMAND tlocposix_test)
