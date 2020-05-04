include_directories(code/headers)

add_library(
    kijetesantakaluPlugin
    SHARED

    ${kSources} ${kHeaders} ${qrcFile}
    ${pluginData}
)

target_link_libraries(
    kijetesantakaluPlugin
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
)

add_custom_command(
    TARGET kijetesantakaluPlugin
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_LIST_DIR}/resources/qmldir
        $<TARGET_FILE_DIR:kijetesantakaluPlugin>/resources/qmldir
)
