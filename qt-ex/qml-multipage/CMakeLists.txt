qt_add_executable(qml-multipage main.cpp)

install(
    TARGETS qml-multipage
    RUNTIME DESTINATION pdf-qml/multipage
    BUNDLE DESTINATION pdf-qml/multipage
    LIBRARY DESTINATION pdf-qml/multipage
)
