cmake_minimum_required(VERSION 3.16)

set(Scouter_APP_NAME QFRCScouter)
set(Scouter_EXEC_NAME Scouter)
set(Scouter_ORG_NAME "Q-FRC")
set(Scouter_GIT_REPO https://github.com/${Scouter_ORG_NAME}/${Scouter_EXEC_NAME})

if(NOT EMSCRIPTEN)
    option(TBA_AUTH_KEY "TBA authentication key." "")
endif()

project(${Scouter_APP_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTORCC ON)

option(USE_SYSTEM_NTCORE OFF "Use the system NTCore (Linux only)")
option(USE_SYSTEM_PROTOBUF OFF "Use the system protobuf (Linux only)")

if(EMSCRIPTEN)
    find_package(Qt6 6.6 REQUIRED COMPONENTS Quick QuickControls2 Svg)
else()
    find_package(Qt6 6.6 REQUIRED COMPONENTS Quick QuickControls2 Network Svg)
endif()

qt_standard_project_setup(REQUIRES 6.6)

if(WIN32)
    set(RCS_FILE ${CMAKE_CURRENT_BINARY_DIR}/program_info/${Scouter_APP_NAME}.rc)
endif()

if(ANDROID)
    set(ANDROID_GUI ON)
    set(MANIFEST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/android/AndroidManifest.xml)
endif()

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

# Git
include(GetGitRevisionDescription)
git_get_exact_tag(Scouter_GIT_TAG)
get_git_head_revision(Scouter_GIT_REFSPEC Scouter_GIT_COMMIT)

message(STATUS "Git commit: ${Scouter_GIT_COMMIT}")
message(STATUS "Git tag: ${Scouter_GIT_TAG}")
message(STATUS "Git refspec: ${Scouter_GIT_REFSPEC}")

string(REPLACE "-beta" "." Scouter_GIT_TAG_NUMERO ${Scouter_GIT_TAG})
string(REPLACE "-rc" "." Scouter_GIT_TAG_NUMERO ${Scouter_GIT_TAG_NUMERO})

string(REPLACE "." " " Scouter_SPLIT_VERSION ${Scouter_GIT_TAG_NUMERO})

separate_arguments(Scouter_SPLIT_VERSION)

list(GET Scouter_SPLIT_VERSION 0 Scouter_VERSION_MAJOR)
list(GET Scouter_SPLIT_VERSION 1 Scouter_VERSION_MINOR)
list(GET Scouter_SPLIT_VERSION 2 Scouter_VERSION_HOTFIX)

project(${Scouter_APP_NAME} VERSION ${Scouter_GIT_TAG_NUMERO} LANGUAGES CXX)

# Build Date
string(TIMESTAMP TODAY "%Y-%m-%d")
set(Scouter_BUILD_TIMESTAMP "${TODAY}")

add_subdirectory("program_info")

set(QRC_FILES
    config.qrc
    Schedule.qrc
)

qt_add_executable(${Scouter_EXEC_NAME}
    main.cpp
    ${MANIFEST_FILE}
    ${QRC_FILES}
    ${RCS_FILE}
)

set_source_files_properties(Constants.qml
    PROPERTIES
    QT_QML_SINGLETON_TYPE true
)

set(QML_ELEMENTS
    Main
    Constants

    screen/MainScreen
    screen/NavButton

    pages/WelcomePage
    pages/MatchInfo
    pages/PhasePage
    pages/NotesPage
    pages/ScalesPage

    items/TitleBanner
    items/LabeledSpinBox
    items/MatchSpinBox
    items/LabeledTextField
    items/LabeledComboBox
    items/LabeledCheckbox
    items/ScaleCheckbox
    items/ScaleItem

    dialogs/AnimatedDialog
    dialogs/ErrorDialog
)

set(ELEMENTS
    Config
    MatchData
    PlatformHelper

    models/PhaseDataModel
    models/ScalesModel
)

foreach(ELEMENT ${ELEMENTS})
    set(HEADERS ${HEADERS} include/${ELEMENT}.h)
    set(SOURCES ${SOURCES} src/${ELEMENT}.cpp)
endforeach()

foreach(QML ${QML_ELEMENTS})
    set(QML_FILES ${QML_FILES} ${QML}.qml)
endforeach()

set(HEADERS
    ${HEADERS}

    tba/Match.h
    tba/Schedule.h
)

set(SOURCES
    ${SOURCES}

    tba/Match.cpp
    tba/Schedule.cpp
)

add_subdirectory(buildconfig)

set(QZXING_USE_QML ON)
set(QZXING_USE_ENCODER ON)
add_subdirectory(qzxing/src/)

qt_add_qml_module(${Scouter_EXEC_NAME}
    URI ${Scouter_APP_NAME}
    VERSION 1.0
    QML_FILES ${QML_FILES}

    SOURCES ${SOURCES} ${HEADERS}
    QML_FILES pages/QRCode.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${Scouter_EXEC_NAME} PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${Scouter_EXEC_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${Scouter_EXEC_NAME}
    PRIVATE Qt6::Quick
    Qt6::QuickControls2
    Qt6::Network
    qzxing
    BuildConfig
)

target_include_directories(${Scouter_EXEC_NAME} PRIVATE include/)
target_include_directories(${Scouter_EXEC_NAME} PRIVATE tba/)

if(NOT EMSCRIPTEN)
    add_compile_definitions(TBA_AUTH_KEY="${TBA_AUTH_KEY}")
endif()

include(GNUInstallDirs)
install(TARGETS ${Scouter_EXEC_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set_target_properties(${Scouter_EXEC_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
)

if (ANDROID)
    set_target_properties(${Scouter_EXEC_NAME} PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/android
        COMPILE_DEFINITIONS "${COMPILE_DEFINITIONS} MOBILE")

    include(FetchContent)
    FetchContent_Declare(
        android_openssl
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip
    )
    FetchContent_MakeAvailable(android_openssl)
    include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)

    add_android_openssl_libraries(${Scouter_EXEC_NAME})
endif()

if(UNIX AND APPLE)
    # Mac bundle settings
    set(MACOSX_BUNDLE_BUNDLE_NAME "${Scouter_APP_NAME}")
    set(MACOSX_BUNDLE_INFO_STRING "${Scouter_APP_NAME}: An offline, QR-Based scouter for FRC use.")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "org.${Scouter_ORG_NAME}.${Scouter_APP_NAME}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${Scouter_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${Scouter_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${Scouter_GIT_TAG_NUMERO}")
    set(MACOSX_BUNDLE_ICON_FILE ${Scouter_APP_NAME}.icns)
    set(MACOSX_BUNDLE_COPYRIGHT "Copyleft 2024 ${Scouter_ORG_NAME}")

    # install as bundle
    set(INSTALL_BUNDLE "full")
endif()
