cmake_minimum_required(VERSION 3.19)
project(Tarea3 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Tarea3
    WIN32 MACOSX_BUNDLE
    main.cpp
    Stage3.cpp
    Stage3.h
    Stage3.ui
    equipo.h Equipo.cpp
    cellular.h cellular.cpp
    cellularview.h cellularview.cpp
    eloteltag.h eloteltag.cpp
    etnube.h etnube.cpp
    tablet.h tablet.cpp
    eloteltagview.h eloteltagview.cpp
    tabletview.h tabletview.cpp
)

target_link_libraries(Tarea3
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Tarea3
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Tarea3
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
