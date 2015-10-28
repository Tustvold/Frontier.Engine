# This is a shared library so that it can provide the definitions for the opengl functions
# Which are declared as belonging to a shared library
add_library(glmock SHARED iglmock.hpp iglmock.cpp)


target_include_directories(glmock PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../googletest/googlemock/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/)

target_compile_features(glmock PRIVATE cxx_auto_type)
