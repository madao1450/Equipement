cmake_minimum_required(VERSION 3.5)

project(EquipmentManagement VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Xml Xlsx Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Xml Xlsx Core Gui)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        enroll.cpp
        enroll.h
        enroll.ui
        findpassword.cpp
        findpassword.h
        findpassword.ui
       administratorinterface.cpp
       administratorinterface.h
       administratorinterface.ui
       userinterface.cpp
       userinterface.h
       userinterface.ui
       accountinfo.cpp
       accountinfo.h
       accountinfo.ui
       globle.cpp
       globle.h
       personnelinformation.cpp
       personnelinformation.h
       personnelinformation.ui
       equipmentinfo.cpp
       equipmentinfo.h
       equipmentinfo.ui
       equipmentnews.cpp
       equipmentnews.h
       equipmentnews.ui
       equipmentstorage.cpp
       equipmentstorage.h
       equipmentstorage.ui
       equipmentoutbound.h
       equipmentoutbound.cpp
       equipmentoutbound.ui
       equipmentstorageinterface.cpp
       equipmentstorageinterface.h
       equipmentstorageinterface.ui
       queryinterface.cpp
       queryinterface.h
       queryinterface.ui
     equipmentoutboundinterface.cpp
     equipmentoutboundinterface.h
     equipmentoutboundinterface.ui
     equipmentalarms.cpp
     equipmentalarms.h
     equipmentalarms.ui
 picture.qrc
photo.cpp
photo.h
photo.ui
       )


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(EquipmentManagement
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET EquipmentManagement APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(EquipmentManagement SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(EquipmentManagement
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(EquipmentManagement PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql  Qt${QT_VERSION_MAJOR}::Xml Qt${QT_VERSION_MAJOR}::Xlsx  Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.EquipmentManagement)
endif()
set_target_properties(EquipmentManagement PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS EquipmentManagement
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(EquipmentManagement)
endif()
