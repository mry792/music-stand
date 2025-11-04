qt_add_executable(qml-paint main.cpp)

install(
    TARGETS qml-paint
    RUNTIME DESTINATION canvas-qml/paint
    BUNDLE DESTINATION canvas-qml/paint
    LIBRARY DESTINATION canvas-qml/paint
)
