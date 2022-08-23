add_library(objects STATIC 
    object.hpp
    scene.cpp scene.hpp
    polygon.cpp polygon.hpp
    parallelepiped.cpp parallelepiped.hpp
    fundamental/fundamental_object.cpp fundamental/fundamental_object.hpp
    fundamental/parallelogram.cpp fundamental/parallelogram.hpp
    fundamental/sphere.cpp fundamental/sphere.hpp
    fundamental/triangle.cpp fundamental/triangle.hpp)
target_include_directories(objects PUBLIC ../ PRIVATE .)
target_compile_features(objects PUBLIC cxx_std_20)
target_link_libraries(objects PUBLIC utils)
