project(Frontier.Engine)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if (COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif (MSVC)
    message(ERROR "MSVC is not supported")
else ()
    message(FATAL "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif ()

cmake_minimum_required(VERSION 3.2)
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules"
        "${CMAKE_MODULE_PATH}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(freetype-gl_BUILD_DEMOS "Build the freetype-gl example programs" OFF)
option(freetype-gl_BUILD_APIDOC "Build the freetype-gl API documentation" OFF)
option(freetype-gl_BUILD_TESTS "Build the freetype-gl Tests" OFF)

if (WIN32)
    option(gtest_disable_pthreads "" ON)
endif ()

find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(GLM REQUIRED)
find_package(RapidJSON REQUIRED)
find_package(Boost COMPONENTS filesystem)

add_subdirectory(Source)

# Dependencies
add_subdirectory(ThirdParty/freetype-gl)
add_subdirectory(ThirdParty/ttvfs)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Enable warnings
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -Werror -Wno-unused-local-typedefs")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -Werror -Wno-unused-local-typedefs")
endif ()

add_library(Frontier.Engine STATIC ${SOURCES} ${HEADERS} Source/Util/Serialization/Serialization.h)

SET(FRONTIER_ENGINE_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/Source
        ${FREETYPE_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/freetype-gl
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIR}
        ${GLM_INCLUDE_DIRS}
        ${RAPIDJSON_INCLUDE_DIRS}
        ${TTVFS_INCLUDE_DIRS}
        ${Boost_INCLUDE_DIRS}
        CACHE INTERNAL "Include Directories for Frontier.Engine"
        )

SET(FRONTIER_ENGINE_TEST_LIBS
        Frontier.Engine
        freetype-gl
        ${GLEW_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${Boost_LIBRARIES}
        ttvfs
        ttvfs_zip
        CACHE INTERNAL "Dependencies of Frontier.Engine")

SET(FRONTIER_ENGINE_LIBS
        ${FRONTIER_ENGINE_TEST_LIBS}
        ${GLFW_LIBRARIES}
        CACHE INTERNAL "Dependencies of Frontier.Engine")

target_include_directories(Frontier.Engine PUBLIC
        ${FRONTIER_ENGINE_INCLUDES}
        )


FUNCTION(NewResourceBundle TARGET DIRECTORY)
    add_custom_target(${TARGET}.${DIRECTORY}.zip DEPENDS Frontier.Engine.Bundler "${DIRECTORY} Bundle for ${TARGET}")

    add_custom_command(OUTPUT "${DIRECTORY} Bundle for ${TARGET}"
            COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Frontier.Engine.Bundler
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY} ${CMAKE_CURRENT_BINARY_DIR}
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TARGET}.${DIRECTORY}.zip
            )

    add_dependencies(${TARGET} ${TARGET}.${DIRECTORY}.zip)
ENDFUNCTION()

add_subdirectory(Tools)

# Testing
add_subdirectory(ThirdParty/googletest/googlemock)

add_subdirectory(Tests)