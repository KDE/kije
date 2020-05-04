cmake_minimum_required(VERSION 3.5)

project(Kijetesantakalu LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

file ( GLOB kSources source/code/*.cpp )
file ( GLOB kHeaders source/code/headers/*.h )

file ( GLOB qrcContent source/resources/* )
list ( FILTER qrcContent EXCLUDE REGEX ".*qrc$" )

file ( GLOB qrcFile source/resources/*.qrc )
file ( GLOB pluginData qrc/qmldir qrc/plugin.qmltypes )

add_subdirectory(source)

install( TARGETS kijetesantakaluPlugin DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt5/qml/org/kde/kijetesantakalu )
install( FILES ${pluginData} DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt5/qml/org/kde/kijetesantakalu )
install( FILES ${qrcContent} DESTINATION ${CMAKE_INSTALL_LIBDIR}/qt5/qml/org/kde/kijetesantakalu )
