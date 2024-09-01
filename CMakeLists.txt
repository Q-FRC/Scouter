cmake_minimum_required(VERSION 3.5)

project(QFRCScouter VERSION 0.1 LANGUAGES CXX)
set(CMAKE_AUTOUIC_SEARCH_PATHS "ui/")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT EMSCRIPTEN)
    option(TBA_AUTH_KEY "TBA authentication key." "")
endif()

if(EMSCRIPTEN)
    find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Svg)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg)
else()
    find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Svg Network)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg Network)
endif()

set(QRCODE_SOURCES
    Qt-QrCodeGenerator/src/QrCodeGenerator.cpp
    Qt-QrCodeGenerator/src/QrCodeGenerator.h
    Qt-QrCodeGenerator/src/qrcodegen/qrcodegen.cpp
    Qt-QrCodeGenerator/src/qrcodegen/qrcodegen.h)

set(PROJECT_SOURCES
    src/main.cpp
    src/MainWindow.cpp

    src/WelcomePage.cpp
    src/TeamInfo.cpp
    src/MatchPage.cpp

    # ================== #
    include/MainWindow.h

    include/WelcomePage.h
    include/TeamInfo.h
    include/MatchPage.h

    # ================== #
    ui/MainWindow.ui

    ui/WelcomePage.ui
    ui/MatchPage.ui


    include/QRCode.h src/QRCode.cpp ui/QRCode.ui
    include/BetterSpinBox.h src/BetterSpinBox.cpp ui/BetterSpinBox.ui
    include/Notes.h src/Notes.cpp ui/Notes.ui
    include/SubjectiveScales.h src/SubjectiveScales.cpp ui/SubjectiveScales.ui

    tba/Schedule.h tba/Schedule.cpp
    tba/Match.h tba/Match.cpp

    include/MatchData.h src/MatchData.cpp
    Config.qrc
)

if(WIN32)
    set(RCS_FILE ${CMAKE_CURRENT_BINARY_DIR}/program_info/QFRCScouter.rc)
endif()

if(ANDROID)
    set(ANDROID_GUI ON)
    set(MANIFEST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/android/AndroidManifest.xml)
endif()

if(EMSCRIPTEN)
    set(PROJECT_SOURCES ${PROJECT_SOURCES} ui/WebTeamInfo.ui Schedule.qrc)
else()
    set(PROJECT_SOURCES ${PROJECT_SOURCES} ui/TeamInfo.ui)
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

add_subdirectory(program_info)

qt_add_executable(QFRCScouter
    MANUAL_FINALIZATION
    ${MANIFEST_FILE}
    ${RCS_FILE}
    ${QRCODE_SOURCES}
    ${PROJECT_SOURCES}

    include/Scale.h src/Scale.cpp ui/Scale.ui
)

if (EMSCRIPTEN)
    target_link_libraries(QFRCScouter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Svg)
else()
    target_link_libraries(QFRCScouter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Svg Qt${QT_VERSION_MAJOR}::Network)
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fieed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QFRCScouter)
endif()
set_target_properties(QFRCScouter PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QFRCScouter
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_include_directories(QFRCScouter PRIVATE include/)
target_include_directories(QFRCScouter PRIVATE tba/)
target_include_directories(QFRCScouter PRIVATE Qt-QrCodeGenerator/src)

if(NOT EMSCRIPTEN)
    add_compile_definitions(TBA_AUTH_KEY="${TBA_AUTH_KEY}")
endif()

if (EMSCRIPTEN)
    target_compile_options(QFRCScouter PRIVATE "-sNO_DISABLE_EXCEPTION_CATCHING")
    target_link_options(QFRCScouter PRIVATE "-sNO_DISABLE_EXCEPTION_CATCHING")
endif()

if (ANDROID)
    set_target_properties(QFRCScouter PROPERTIES
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

    add_android_openssl_libraries(QFRCScouter)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QFRCScouter)
endif()
