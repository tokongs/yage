cmake_minimum_required(VERSION 3.9)
project(yage_editor)
subdirs(3rd-party)
file(GLOB GUI_SRC src/gui/*.cpp)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS program_options)



add_executable(yage_editor src/main.cpp src/MovingCamera.cpp ${GUI_SRC} include/Configuration.h src/Configuration.cpp)
target_link_libraries(yage_editor yage_core imgui)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(yage_editor ${Boost_LIBRARIES})
endif()

target_include_directories(yage_editor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/gui)
