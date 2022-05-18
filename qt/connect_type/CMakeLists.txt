cmake_minimum_required(VERSION 3.16.0)

set(PRJ_NAME connect_type_test)

project(${PRJ_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

aux_source_directory(. SRCS)
add_executable(${PRJ_NAME} ${SRCS})
target_link_libraries(${PRJ_NAME} PRIVATE Qt5::Widgets)
target_include_directories(${PRJ_NAME} PRIVATE .)