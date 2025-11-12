qt_add_executable(qml-paint
    main.cpp
    #
)

target_sources(
    qml-paint
    PRIVATE
        FILE_SET HEADERS
        FILES
            #
)

qt_add_qml_module(
    qml-paint
    URI paint
    QML_FILES
        ColorSquare.qml
        viewer.qml
)

set_target_properties(
    qml-paint
    PROPERTIES
        AUTORCC ON
)

target_link_libraries(
    qml-paint
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Qml
)

install(
    TARGETS qml-paint
    RUNTIME DESTINATION canvas-qml/paint
    BUNDLE DESTINATION canvas-qml/paint
    LIBRARY DESTINATION canvas-qml/paint
)
