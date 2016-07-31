project(Frontier.Engine)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(MSVC)
    message(STATUS "Warning: MSVC's C++11 support is incomplete and this engine may therefore not compile correctly")
else()
    message(FATAL "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

cmake_minimum_required(VERSION 3.2)
SET( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules"
                       "${CMAKE_MODULE_PATH}" )

# Change default options
option( GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option( glew-cmake_BUILD_SHARED "Build the shared glew library" OFF)
option( glew-cmake_BUILD_STATIC "Build the static glew library" ON)
option( freetype-gl_BUILD_DEMOS "Build the freetype-gl example programs" OFF)
option( freetype-gl_BUILD_APIDOC "Build the freetype-gl API documentation" OFF)
option( GLFW_INSTALL "Generate Installation Target" OFF)
option( GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option( GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(gtest_force_shared_crt "Use shared (DLL) run-time lib even when Google Test is built as static lib." ON)
option(gtest_disable_pthreads "" ON)

add_definitions(-DGLEW_STATIC)

# Visual Studio misbehaves unless you set all of these
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# Set variables for freetype-gl
set(GLEW_LIBRARY libglew_static)
set(GLEW_INCLUDE_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew/include)
set(FREETYPE_LIBRARY freetype)
set(FREETYPE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/freetype2/include)

add_subdirectory(Source)

# Dependencies
add_subdirectory(ThirdParty/freetype2)
add_subdirectory(ThirdParty/glew)
add_subdirectory(ThirdParty/freetype-gl)
add_subdirectory(ThirdParty/glfw)
add_subdirectory(ThirdParty/glmock)

# We disable this project as it doesn't build correctly on windows
set_target_properties(makefont PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

add_library(Frontier.Engine STATIC ${SOURCES} ${HEADERS} ${CMAKELISTS})

SET (FRONTIER_ENGINE_INCLUDES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/freetype2/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/freetype-gl
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw/include/GLFW
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm
    CACHE INTERNAL "Include Directories for Frontier.Engine"
)

SET (FRONTIER_ENGINE_LIBS
    Frontier.Engine
    glfw
    freetype-gl
    freetype
    libglew_static
    ${GLFW_LIBRARIES}
    CACHE INTERNAL "Dependencies of Frontier.Engine")

target_include_directories ( Frontier.Engine PUBLIC
    ${FRONTIER_ENGINE_INCLUDES}
)

# Testing
add_subdirectory(ThirdParty/googletest/googlemock)

add_subdirectory(Tests)
