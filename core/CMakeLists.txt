project(yage_core)

subdirs(3rd_party)

file(GLOB SRC src/*.cpp)
file(GLOB EVENTS_SRC src/Events/*.cpp include/Events/*.h)
file(GLOB GRAPHICS_SRC src/Graphics/*.cpp inlclude/Graphics/*.h src/Graphics/OpenGL/*.cpp)
file(GLOB UTIL_SRC src/Util/*.cpp inlclude/Util/*.h)
file(GLOB RESOURCE_MANAGEMENT_SRC src/ResourceManagement/*.cpp include/ResourceManagement/*.h src/ResourceManagement/Loaders/*.cpp)
file(GLOB SCRIPTING_SRC src/Scripting/*.cpp)
file(GLOB_RECURSE GAME_OBJECTS_SRC src/Scene/GameObjects *.cpp)
file(GLOB_RECURSE SCENE_SRC src/Scene/*.cpp)


add_library(yage_core STATIC ${SRC} ${GRAPHICS_SRC} ${UTIL_SRC} ${RESOURCE_MANAGEMENT_SRC} ${EVENTS_SRC} ${SCRIPTING_SRC} ${GAME_OBJECTS_SRC} ${SCENE_SRC} 3rd_party/pugixml/pugixml.cpp)

file(GLOB_RECURSE INCLUDE include *.h)

target_include_directories(yage_core PUBLIC
        include include/Graphics include/GameObjects
        include/Graphics/OpenGL include/Util include/ResourceManagement
        include/ResourceManagement/Loaders include/Scripting
        include/Scene include/Scene/GameObjects include/Scene/GameObjects/Components
        include/Scene/GameObjects/Systems 3rd_party)


find_package(Lua REQUIRED)
if (LUA_FOUND)
    target_include_directories(yage_core PUBLIC ${LUA_INCLUDE_DIRS})
    target_link_libraries(yage_core ${LUA_LIBRARIES})
endif ()

find_package(glfw3 REQUIRED)
if (glfw3_FOUND)
    target_include_directories(yage_core PUBLIC ${GLFW_INCLUDE_DIRS})
    target_link_libraries(yage_core glfw)
else ()
    message([ERROR] "Failed to find GLFW3")
endif ()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    target_include_directories(yage_core PUBLIC ${GLEW_INCLUDE_DIRS})
    target_link_libraries(yage_core ${GLEW_LIBRARIES})
else ()
    message([ERROR] "Failed to find GLEW")
endif ()
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    target_include_directories(yage_core PUBLIC ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(yage_core ${OPENGL_LIBRARIES})
else ()
    message([ERROR] "Failed to find OpenGL")
endif ()

find_package(spdlog REQUIRED)
if (spdlog_FOUND)
    target_include_directories(yage_core PUBLIC ${spdlog_INCLUDE_DIRS})
    target_link_libraries(yage_core ${spdlog_LIBRARIES})

else ()
    message([ERROR] "Failed to find spdlog")
endif ()

find_package(glm REQUIRED)
if (glm_FOUND)
    target_include_directories(yage_core PUBLIC ${GLM_INCLUDE_DIRS})
    target_link_libraries(yage_core ${GLM_LIBRARY_DIRS})
else ()
    message([ERROR] "Failed to find glm")
endif ()

find_package(assimp REQUIRED)
if (assimp_FOUND)
    find_library(ASSIMP_LIBRARY NAMES ${ASSIMP_LIBRARIES} PATH ${ASSIMP_LIBRARY_DIRS})
    target_include_directories(yage_core PUBLIC ${ASSIMP_INCLUDE_DIRS})
    target_link_libraries(yage_core ${ASSIMP_LIBRARY})
else ()
    message([ERROR] "Failed to find assimp")
endif ()