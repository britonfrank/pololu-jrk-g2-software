use_cxx11()

# Find includes in corresponding build directories
set (CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories (
  "${CMAKE_CURRENT_SOURCE_DIR}/qt"
)

# Run Qt's moc automatically.
set (CMAKE_AUTOMOC ON)

find_package (Qt5Widgets)

configure_file (gui_info.rc.in gui_info.rc)

if (POLOLU_BUILD)
  if (APPLE)
    # Embed app.icns in the executable.
    qt5_add_resources(ICON_QRC qt/app_icns.qrc)
  else ()
    # Embed app.ico in the executable.
    qt5_add_resources(ICON_QRC qt/app_ico.qrc)
  endif ()
endif ()

qt5_add_resources(RESOURCES_QRC qt/resources.qrc)

add_executable (gui
  qt/target_slider.cpp
  qt/popout_window.cpp
  qt/main_window.cpp
  main.cpp
  main_controller.cpp
  qt/graph_window.cpp
  qt/graph_widget.cpp
  qt/input_wizard.cpp
  qt/feedback_wizard.cpp
  qt/elided_label.cpp
  qt/pid_constant_control.cpp
  qt/nice_spin_box.cpp
  qt/bootloader_window.cpp
  qt/qcustomplot.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/gui_info.rc
  ${ICON_QRC}
  ${RESOURCES_QRC}
  ${ICON_FILE}
)

set_target_properties (gui PROPERTIES
  OUTPUT_NAME ${GUI_NAME}
)

if (WIN32)
  set_target_properties (gui PROPERTIES
    LINK_FLAGS "-mwindows"
  )
endif ()

target_link_libraries (gui Qt5::Widgets lib bootloader)

install(TARGETS gui DESTINATION bin)
