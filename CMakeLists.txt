cmake_minimum_required(VERSION 3.0.0)
project(DoublePendulum VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML REQUIRED COMPONENTS graphics system window)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp sphere.cpp light.cpp pendulum.cpp line.cpp)

target_link_libraries(${PROJECT_NAME}
    imgui::imgui
    sfml-graphics sfml-system sfml-window
    ImGui-SFML::ImGui-SFML
)