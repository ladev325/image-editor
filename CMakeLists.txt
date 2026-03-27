cmake_minimum_required(VERSION 4.2)
project(image_editor 
    LANGUAGES CXX
    VERSION 1.0
    )
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(dependencies)
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(app ${SOURCE_FILES})
target_link_libraries(app PRIVATE ImGui-SFML::ImGui-SFML)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/constants)