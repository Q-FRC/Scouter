# Config stuff
if(UNIX AND NOT(APPLE))
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${Scouter_APP_NAME}.desktop DESTINATION "share/applications")
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${Scouter_APP_NAME}.svg DESTINATION "share/icons/hicolor/scalable/apps")
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${Scouter_APP_NAME}-symbolic.svg DESTINATION "share/icons/hicolor/symbolic/apps" RENAME ${Scouter_APP_NAME}.svg)
endif()

set(Scouter_VERSION_WIN ${Scouter_VERSION_MAJOR}.${Scouter_VERSION_MINOR}.${Scouter_VERSION_HOTFIX}.0)

configure_file(${Scouter_APP_NAME}.rc.in ${Scouter_APP_NAME}.rc @ONLY)
configure_file(${Scouter_APP_NAME}.manifest.in ${Scouter_APP_NAME}.manifest @ONLY)
configure_file(${Scouter_APP_NAME}.desktop.in ${Scouter_APP_NAME}.desktop)
configure_file(${Scouter_APP_NAME}.ico ${Scouter_APP_NAME}.ico COPYONLY)
configure_file(win_install.nsi.in win_install.nsi @ONLY)
configure_file(${Scouter_APP_NAME}.icns ${Scouter_APP_NAME}.icns COPYONLY)
