qt_add_executable(qml-multipage
    main.cpp
    viewer.qrc
    PdfApplication.cpp
)

target_sources(
    qml-multipage
    PRIVATE
        FILE_SET HEADERS
        FILES
            PdfApplication.hpp
)

target_link_libraries(
    qml-multipage
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Qml
        Qt::Svg  # Needed to decode icon SVG files.
)

set_target_properties(
    qml-multipage
    PROPERTIES
        AUTORCC ON
)

qt_add_qml_module(
    qml-multipage
    URI multipage
    QML_FILES
        viewer.qml
)

install(
    TARGETS qml-multipage
    RUNTIME DESTINATION pdf-qml/multipage
    BUNDLE DESTINATION pdf-qml/multipage
    LIBRARY DESTINATION pdf-qml/multipage
)
