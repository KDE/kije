#
#  SPDX-FileCopyrightText: 2020 Carson Black <uhhadd@gmail.com>
#
#  SPDX-License-Identifier: LGPL-2.0-or-later
#

add_library(
    kijeplugin
    SHARED

    ${kSources} ${kHeaders} ${qrcFile}
    ${pluginData}
)

target_compile_options(
    kijeplugin
    PRIVATE
    -Wall -Werror
)

target_link_libraries(
    kijeplugin
    PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::GuiPrivate
        Qt5::Quick
        Qt5::Qml
        KF5::ConfigCore
)

add_custom_command(
    TARGET kijeplugin
    POST_BUILD
    COMMAND
        ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_LIST_DIR}/resources/qmldir
        $<TARGET_FILE_DIR:kijeplugin>/resources/qmldir
)

install(FILES resources/qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/kije)
install(DIRECTORY resources/controls DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/kije)