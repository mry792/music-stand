qt_add_executable(widget-viewer main.cpp)

target_sources(
    widget-viewer

    PRIVATE
        MainWindow.cpp
        MainWindow.ui
        SearchResultDelegate.cpp
        ZoomSelector.cpp

    PUBLIC FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
            MainWindow.hpp
            SearchResultDelegate.hpp
            ZoomSelector.hpp
)

target_link_libraries(
    widget-viewer
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Pdf
        Qt6::PdfWidgets
        Qt6::Widgets
)

qt_add_resources(
    widget-viewer
    "resources"
    PREFIX /icons
    FILES
        images/zoom-fit-width.svgz
        images/zoom-in.svgz
        images/go-previous-view-page.svgz
        images/zoom-original.svgz
        images/go-previous-view.svgz
        images/go-next-view-page.svgz
        images/zoom-fit-best.svgz
        images/zoom-out.svgz
        images/zoom-previous.svgz
        images/document-open.svgz
        images/go-next-view.svgz
        images/go-down-search.svgz
        images/go-up-search.svgz
)

install(
    TARGETS widget-viewer
    RUNTIME DESTINATION pdfwidgets/pdfviewer
    BUNDLE DESTINATION pdfwidgets/pdfviewer
    LIBRARY DESTINATION pdfwidgets/pdfviewer
)
