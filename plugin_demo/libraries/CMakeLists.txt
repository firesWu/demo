file(GLOB HEADERS "include/*.hpp")

add_library(libraries
        application.cpp
        ${HEADERS}
        )

target_include_directories( libraries
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")