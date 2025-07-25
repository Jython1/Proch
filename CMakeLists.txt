cmake_minimum_required(VERSION 3.16)

project(ProchApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp

    categorytree.cpp
)

set(HEADERS
    mainwindow.h

    categorytree.h
)


add_executable(ProchApp ${SOURCES} ${HEADERS}
    tabsystem.h tabsystem.cpp
    Themes/DefaultDark.qss
    productsWindow.h productsWindow.cpp
    categorywindow.h categorywindow.cpp)

target_link_libraries(ProchApp Qt5::Widgets Qt5::Sql)


