enable_testing()


add_executable(Frontier.Engine.Bundler main.cpp)

target_include_directories(Frontier.Engine.Bundler PRIVATE
        Source
        ${FRONTIER_ENGINE_INCLUDES}
        )

TARGET_LINK_LIBRARIES(Frontier.Engine.Bundler
        Frontier
        ${FRONTIER_ENGINE_LIBS}
        )