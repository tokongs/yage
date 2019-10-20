project(yage_core)

add_subdirectory(test)
subdirs(3rd_party)

file(GLOB SRC src/*.cpp)
file(GLOB EVENTS_SRC src/Events/*.cpp include/Events/*.h)
file(GLOB GRAPHICS_SRC src/Graphics/*.cpp inlclude/Graphics/*.h src/Graphics/OpenGL/*.cpp)
file(GLOB UTIL_SRC src/Util/*.cpp inlclude/Util/*.h)
file(GLOB RESOURCE_MANAGEMENT_SRC src/ResourceManagement/*.cpp include/ResourceManagement/*.h src/ResourceManagement/Loaders/*.cpp)
file(GLOB SCRIPTING_SRC src/Scripting/*.cpp)

file(GLOB_RECURSE ANGEL_SCRIPT_ADDON_SRC 3rd_party/angelscript/add_on *.cpp)

add_library(yage_core STATIC ${SRC} ${GRAPHICS_SRC} ${UTIL_SRC} ${RESOURCE_MANAGEMENT_SRC} ${EVENTS_SRC} ${SCRIPTING_SRC} ${ANGEL_SCRIPT_ADDON_SRC})

target_include_directories(yage_core PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/Graphics
${CMAKE_CURRENT_SOURCE_DIR}/include/Graphics/OpenGL ${CMAKE_CURRENT_SOURCE_DIR}/include/Util ${CMAKE_CURRENT_SOURCE_DIR}/include/ResourceManagement
${CMAKE_CURRENT_SOURCE_DIR}/include/ResourceManagement/Loaders ${CMAKE_CURRENT_SOURCE_DIR}/include/Scripting ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/angelscript/add_on)

target_link_libraries(yage_core angelscript)

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

find_package(glm REQUIRED)
if(spdlog_FOUND)
    target_include_directories(yage_core PUBLIC ${GLM_INCLUDE_DIRS})
    target_link_libraries(yage_core ${GLM_LIBRARY_DIRS})

else()
    message([ERROR] "Failed to find spdlog")
endif()
