qt_add_executable(
    music-stand
    main.cpp
    music_stand/Application.cpp
)

target_sources(
    music-stand
    PRIVATE
        FILE_SET HEADERS
        FILES
            music_stand/Application.hpp
)

qt_add_qml_module(
    music-stand
    URI music-stand
    QML_FILES
        application.qml
)

set_target_properties(
    music-stand
    PROPERTIES
        AUTORCC ON
)

target_link_libraries(
    music-stand
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Qml
)

install(
    TARGETS music-stand
    RUNTIME DESTINATION music-stand
    BUNDLE DESTINATION music-stand
    LIBRARY DESTINATION music-stand
)
