set (SOURCES ${SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/ActionManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/IntervalAction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MoveToAction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ActionSequence.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RepeatAction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/CallFuncAction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/RotateToAction.cpp
   PARENT_SCOPE)

set (HEADERS ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/ActionManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Action.h
        ${CMAKE_CURRENT_SOURCE_DIR}/IntervalAction.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MoveToAction.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ActionSequence.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RepeatAction.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CallFuncAction.h
        ${CMAKE_CURRENT_SOURCE_DIR}/CallDelegateAction.h
        ${CMAKE_CURRENT_SOURCE_DIR}/RotateToAction.h
    PARENT_SCOPE)
