add_executable(ray_tracer ray_tracer.cpp)
target_link_libraries(ray_tracer PRIVATE utils objects rendering config)

add_executable(thread_test thread_test.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(thread_test PRIVATE Threads::Threads)