include_directories(code/headers)

add_library(
    kijetesantakaluplugin
    SHARED

    ${kSources} ${kHeaders} ${qrcFile}
    ${pluginData}
)

target_compile_options(
    kijetesantakaluplugin
    PRIVATE
    -Wall -Werror
)

target_link_libraries(
    kijetesantakaluplugin
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
)

add_custom_command(
    TARGET kijetesantakaluplugin
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_LIST_DIR}/resources/qmldir
        $<TARGET_FILE_DIR:kijetesantakaluplugin>/resources/qmldir
)

install(FILES resources/qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/kijetesantakalu)
install(DIRECTORY resources/controls DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/kijetesantakalu)