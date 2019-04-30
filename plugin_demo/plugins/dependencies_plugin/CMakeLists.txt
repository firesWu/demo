file(GLOB HEADERS "include/dependencies_plugin/*.hpp")

add_library(dependencies_plugin
        dependencies_plugin.cpp
        ${HEADERS}
        )

target_link_libraries( dependencies_plugin libraries )
target_include_directories( dependencies_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )