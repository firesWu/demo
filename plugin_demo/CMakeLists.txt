cmake_minimum_required(VERSION 3.13)
project(plugin_demo)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libraries)
add_subdirectory(plugins)


add_executable(plugin_demo main.cpp)

if(UNIX)
    if(APPLE)
        set(whole_archive_flag "-force_load")
        set(no_whole_archive_flag "")
        set(build_id_flag "")
    else()
        set(whole_archive_flag "--whole-archive")
        set(no_whole_archive_flag "--no-whole-archive")
        set(build_id_flag "--build-id")
    endif()
else()
    set(whole_archive_flag "--whole-archive")
    set(no_whole_archive_flag "--no-whole-archive")
    set(build_id_flag "")
endif()

target_link_libraries( plugin_demo
        PRIVATE -Wl,${whole_archive_flag} default_plugin -Wl,${no_whole_archive_flag}
        PRIVATE -Wl,${whole_archive_flag} dependencies_plugin -Wl,${no_whole_archive_flag}
        PRIVATE -Wl,${whole_archive_flag} test_plugin -Wl,${no_whole_archive_flag})