cmake_minimum_required(VERSION 3.3)
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

add_definitions(-DGLEW_STATIC)

add_subdirectory(Source)

# Dependencies
add_subdirectory(ThirdParty/freetype2)
add_subdirectory(ThirdParty/glew)
add_subdirectory(ThirdParty/freetype-gl)
add_subdirectory(ThirdParty/glfw)

# We disable this project as it doesn't build correctly on windows
set_target_properties(makefont PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)

# We can use GLOB here as in order for a CMakeList to be used a pre-existing one
# must have been modified and therefore the build system will know to rebuild
FILE(GLOB_RECURSE CMAKELISTS Source/*CMakeLists.txt)

# Rebuild directory structure within Visual Studio
foreach(FILE ${SOURCES} ${HEADERS} ${CMAKELISTS})
  get_filename_component(PARENT_DIR "${FILE}" PATH)

  string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "" GROUP "${PARENT_DIR}")
  string(REPLACE "/" "\\" GROUP "${GROUP}")

  source_group("${GROUP}" FILES "${FILE}")
endforeach()

add_library(Frontier.Engine STATIC ${SOURCES} ${HEADERS} ${CMAKELISTS})

target_include_directories ( Frontier.Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/freetype2/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/freetype-gl
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw/include/GLFW
    ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm
)

target_link_libraries( Frontier.Engine
    freetype
    freetype-gl
    libglew_static
    glfw)


# Testing
option(gtest_force_shared_crt "Use shared (DLL) run-time lib even when Google Test is built as static lib." ON)
add_subdirectory(ThirdParty/googletest/googletest)

add_subdirectory(Tests)
