find_package(Threads REQUIRED)

add_executable(thread_test thread_test.cpp)
target_link_libraries(thread_test PRIVATE Threads::Threads)

add_executable(ray_tracer ray_tracer.cpp)
target_link_libraries(ray_tracer PRIVATE utils objects rendering config Threads::Threads)
