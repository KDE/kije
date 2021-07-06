#
#  SPDX-FileCopyrightText: 2021 Carson Black <uhhadd@gmail.com>
#
#  SPDX-License-Identifier: LGPL-2.0-or-later
#

cmake_minimum_required(VERSION 3.5)

set(KF5_VERSION "5.70.0") # handled by release scripts
set(KF5_DEP_VERSION "5.70.0") # handled by release scripts
set(REQUIRED_QT_VERSION 5.15.0)

project(Kije LANGUAGES CXX VERSION ${KF5_VERSION})

include(GNUInstallDirs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ECM ${KF5_VERSION} NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)

find_package(Qt5 COMPONENTS Core Quick Widgets REQUIRED)
find_package(KF5Config)

file (
    GLOB kSources

    main.cpp
)

add_executable(
    kije-widgets-qmlrunner

    ${kSources}
)

target_link_libraries(
    kije-widgets-qmlrunner
    PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
        Qt5::Widgets
)

install( TARGETS kije-widgets-qmlrunner DESTINATION ${KDE_INSTALL_BINDIR} )
