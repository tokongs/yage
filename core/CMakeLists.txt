project(yage_core)

set(GraphicsSource src/Graphics/OpenGL/GLDevice.cpp src/Graphics/OpenGL/VertexBuffer.cpp
src/Graphics/OpenGL/IndexBuffer.cpp src/Graphics/OpenGL/Shader.cpp src/Graphics/Renderer.cpp src/Graphics/Mesh.cpp
src/Graphics/OpenGL/Program.cpp src/Graphics/Camera.cpp)

set(UtilSource src/Util/FileReader.cpp src/Util/Util.cpp)
set(ResourceManagementSource src/ResourceManagement/Resource.cpp src/ResourceManagement/ResourceManager.cpp
src/ResourceManagement/Loaders/ResourceLoader.cpp src/ResourceManagement/Loaders/MeshLoader.cpp src/ResourceManagement/Loaders/WavefrontLoader.cpp
src/ResourceManagement/Loaders/ShaderLoader.cpp)
add_library(yage_core STATIC src/Window.cpp src/Input.cpp ${GraphicsSource} ${UtilSource} ${ResourceManagementSource})

target_include_directories(yage_core PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/Graphics
${CMAKE_CURRENT_SOURCE_DIR}/include/Graphics/OpenGL ${CMAKE_CURRENT_SOURCE_DIR}/include/Util ${CMAKE_CURRENT_SOURCE_DIR}/include/ResourceManagement
${CMAKE_CURRENT_SOURCE_DIR}/include/ResourceManagement/Loaders) 

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
