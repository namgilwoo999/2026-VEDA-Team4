cmake_minimum_required(VERSION 3.16)

project(CustomerManagementSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        shopwidget.cpp
        shopwidget.h
        shopwidget.ui

        item.cpp
        item.h

        databasemanager.cpp
        databasemanager.h

        loginwidget.h loginwidget.cpp loginwidget.ui
        signupwidget.h signupwidget.cpp signupwidget.ui
        user.h user.cpp
        userdb.h userdb.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CustomerManagementSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        mypage.h mypage.cpp mypage.ui
        resources.qrc
    )
else()
    if(ANDROID)
        add_library(CustomerManagementSystem SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(CustomerManagementSystem
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CustomerManagementSystem
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE Qt${QT_VERSION_MAJOR}::Sql
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CustomerManagementSystem)
endif()

set_target_properties(CustomerManagementSystem PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

install(TARGETS CustomerManagementSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CustomerManagementSystem)
endif()
