cmake_minimum_required(VERSION 3.5)

set(KF5_VERSION "5.70.0") # handled by release scripts
set(KF5_DEP_VERSION "5.70.0") # handled by release scripts
set(REQUIRED_QT_VERSION 5.12.0)

project(Kijetesantakalu LANGUAGES CXX VERSION ${KF5_VERSION})

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

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

file (
    GLOB kSources
    source/code/kijetesantakalu_plugin.cpp
    source/code/toolbar_private.cpp
)
file ( GLOB kHeaders source/code/headers/*.h )

file ( GLOB qrcContent source/resources/* )
list ( FILTER qrcContent EXCLUDE REGEX ".*qrc$" )

file ( GLOB qrcFile source/resources/*.qrc )
file ( GLOB pluginData qrc/qmldir qrc/plugin.qmltypes )

add_subdirectory(source)

install( TARGETS kijetesantakaluplugin DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/kijetesantakalu )
install( FILES ${pluginData} DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/kijetesantakalu )
