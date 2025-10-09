cmake_minimum_required(VERSION 3.28)

project(music-stand VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(
    Qt6 REQUIRED
    COMPONENTS
        Core
        Gui
        Pdf
        PdfWidgets
        Qml
        Svg
        Widgets
)

qt_standard_project_setup(REQUIRES 6.9)

add_subdirectory(qt-ex/qml-single-page)
add_subdirectory(qt-ex/widget-viewer)
