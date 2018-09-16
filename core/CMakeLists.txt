project(yage_core)

add_library(yage_core STATIC src/Window.cpp src/GLDevice.cpp)

target_include_directories(yage_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(glfw3 REQUIRED)
if(glfw3_FOUND)
    target_include_directories(yage_core PUBLIC ${GLFW_INCLUDE_DIRS})
    target_link_libraries(yage_core glfw)
else()
    message([ERROR] "Failed to find GLFW3")
endif()

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
    target_include_directories(yage_core PUBLIC ${GLEW_INCLUDE_DIRS})
    target_link_libraries(yage_core ${GLEW_LIBRARIES})
else()
    message([ERROR] "Failed to find GLEW")
endif()

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
    target_include_directories(yage_core PUBLIC ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(yage_core ${OPENGL_LIBRARIES})
else()
    message([ERROR] "Failed to find OpenGL")
endif()

find_package(spdlog REQUIRED)
if(spdlog_FOUND)
    target_include_directories(yage_core PUBLIC ${spdlog_INCLUDE_DIRS})
    target_link_libraries(yage_core ${spdlog_LIBRARIES})

else()
    message([ERROR] "Failed to find spdlog")
endif()
