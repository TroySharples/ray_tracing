add_library(utils STATIC 
    timer.cpp timer.hpp
    line.hpp
    logging.hpp
    matrix.hpp
    utils.hpp
    vector.hpp)
target_include_directories(utils PUBLIC ../ PRIVATE .)
target_compile_features(utils PUBLIC cxx_std_20)