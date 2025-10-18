qt_add_executable(qml-multipage
    main.cpp
    viewer.qrc
)

set_target_properties(
    qml-multipage
    PROPERTIES
        AUTORCC ON
)

install(
    TARGETS qml-multipage
    RUNTIME DESTINATION pdf-qml/multipage
    BUNDLE DESTINATION pdf-qml/multipage
    LIBRARY DESTINATION pdf-qml/multipage
)
