add_subdirectory(objects)
add_subdirectory(rendering)
add_subdirectory(utils)

add_library(config STATIC 
    config.cpp config.hpp)
target_include_directories(config PUBLIC ../ PRIVATE .)
target_compile_features(config PUBLIC cxx_std_20)
target_link_libraries(config PUBLIC utils)