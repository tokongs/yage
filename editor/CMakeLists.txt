cmake_minimum_required(VERSION 3.9)
project(yage_editor)
subdirs(3rd-party)
set(GUI_SOURCE src/gui/Gui.cpp src/gui/ResourceBrowser.cpp src/gui/GuiElement.cpp src/gui/ResourceGui.cpp)

add_executable(yage_editor src/main.cpp ${GUI_SOURCE})
target_link_libraries(yage_editor yage_core imgui)
target_include_directories(yage_editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/gui)