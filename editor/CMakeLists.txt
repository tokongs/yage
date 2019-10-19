cmake_minimum_required(VERSION 3.9)
project(yage_editor)
subdirs(3rd-party)
set(GUI_SOURCE src/gui/Gui.cpp src/gui/ResourceBrowser.cpp src/gui/GuiElement.cpp src/gui/ResourceView.cpp src/gui/MeshResourceView.cpp
src/gui/ShaderResourceView.cpp src/gui/MainMenu.cpp src/gui/MenuElement.cpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS program_options)



add_executable(yage_editor src/main.cpp ${GUI_SOURCE} include/Configuration.h src/Configuration.cpp)
target_link_libraries(yage_editor yage_core imgui)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(yage_editor ${Boost_LIBRARIES})
endif()
target_include_directories(yage_editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/gui)