qt_add_executable(qml-single-page main.cpp)

target_link_libraries(
    qml-single-page
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Svg  # Needed to decode icon SVG files.
)

qt_add_qml_module(
    qml-single-page
    URI singlepage
    # RESOURCE_PREFIX /singlepage/
    QML_FILES
        viewer.qml
)

qt_add_resources(
    qml-single-page
    "viewer"
    PREFIX "/singlepage"
    FILES
        resources/document-open.svg
        resources/edit-clear.svg
        resources/edit-copy.svg
        resources/edit-select-all.svg
        resources/go-down-search.svg
        resources/go-next-view-page.svg
        resources/go-previous-view-page.svg
        resources/go-up-search.svg
        resources/rotate-left.svg
        resources/rotate-right.svg
        resources/test.pdf
        resources/zoom-fit-best.svg
        resources/zoom-fit-width.svg
        resources/zoom-in.svg
        resources/zoom-original.svg
        resources/zoom-out.svg
)

install(
    TARGETS qml-single-page
    RUNTIME DESTINATION pdf-qml/single-page
    BUNDLE DESTINATION pdf-qml/single-page
    LIBRARY DESTINATION pdf-qml/single-page
)
