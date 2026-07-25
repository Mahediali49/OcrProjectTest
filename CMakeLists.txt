cmake_minimum_required(VERSION 3.16)

project(OcrProjectTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_add_executable(OcrProjectTest
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
)

# ==========================
# Daheng Galaxy SDK
# ==========================

set(GALAXY_SDK "C:/Program Files/Daheng Imaging/GalaxySDK/Development/C++ SDK")

target_include_directories(OcrProjectTest PRIVATE
    "${GALAXY_SDK}/inc"
)

target_link_libraries(OcrProjectTest PRIVATE
    Qt6::Widgets
    "${GALAXY_SDK}/lib/x64/GxIAPICPPEx.lib"
)

# Copy Daheng runtime DLL automatically after build
add_custom_command(TARGET OcrProjectTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "C:/Program Files/Daheng Imaging/GalaxySDK/APIDll/Win64/GxIAPICPPEx.dll"
    $<TARGET_FILE_DIR:OcrProjectTest>

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "C:/Program Files/Daheng Imaging/GalaxySDK/APIDll/Win64/GxIAPICPP.dll"
    $<TARGET_FILE_DIR:OcrProjectTest>
)