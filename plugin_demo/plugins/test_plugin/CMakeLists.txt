file(GLOB HEADERS "include/test_plugin/*.hpp")

add_library(test_plugin
        test_plugin.cpp
        ${HEADERS}
        )

target_link_libraries( test_plugin libraries dependencies_plugin)
target_include_directories( test_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )