file(GLOB HEADERS "include/default_plugin/*.hpp")

add_library(default_plugin
        default_plugin.cpp
        ${HEADERS}
        )

target_link_libraries( default_plugin libraries )
target_include_directories( default_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )