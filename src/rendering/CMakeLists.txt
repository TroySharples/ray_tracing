find_package(Threads REQUIRED)

add_library(rendering STATIC 
    render.cpp render.hpp
    camera.hpp)
target_include_directories(rendering PUBLIC ../ PRIVATE .)
target_compile_features(rendering PUBLIC cxx_std_20)
target_link_libraries(rendering PUBLIC utils PRIVATE ${CMAKE_THREAD_LIBS_INIT})