
# This is a static library so that it can provide the definitions for the glew functions which are
# declared as belonging to a static library
add_library(glewmock STATIC glewmock.cpp glewmock2.cpp)

target_link_libraries(glewmock
    glmock
    gmock
)