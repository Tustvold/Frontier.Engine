project(Frontier.Engine)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(MSVC)
    message(ERROR "MSVC is not supported")
else()
    message(FATAL "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

cmake_minimum_required(VERSION 3.2)
SET( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules"
                       "${CMAKE_MODULE_PATH}" )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option( freetype-gl_BUILD_DEMOS "Build the freetype-gl example programs" OFF)
option( freetype-gl_BUILD_APIDOC "Build the freetype-gl API documentation" OFF)

if (WIN32)
    option(gtest_disable_pthreads "" ON)
endif()

find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(Source)

# Dependencies
add_subdirectory(ThirdParty/freetype-gl)


add_library(Frontier.Engine STATIC ${SOURCES} ${HEADERS})

SET (FRONTIER_ENGINE_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
        ${FREETYPE_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/freetype-gl
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm
        CACHE INTERNAL "Include Directories for Frontier.Engine"
        )

SET (FRONTIER_ENGINE_TEST_INCLUDES
        ${FRONTIER_ENGINE_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/googletest/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/googletest/googlemock/include
        CACHE INTERNAL "Include Directories for Frontier.Engine"
        )

SET (FRONTIER_ENGINE_TEST_LIBS
        Frontier.Engine
        freetype-gl
        ${GLEW_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${OPENGL_LIBRARIES}
        CACHE INTERNAL "Dependencies of Frontier.Engine")

SET (FRONTIER_ENGINE_LIBS
        ${FRONTIER_ENGINE_TEST_LIBS}
        ${GLFW_LIBRARIES}
    CACHE INTERNAL "Dependencies of Frontier.Engine")

target_include_directories ( Frontier.Engine PUBLIC
    ${FRONTIER_ENGINE_INCLUDES}
)

# Testing
add_subdirectory(ThirdParty/googletest/googlemock)

add_subdirectory(Tests)