#include <Window.h>
#include <GLDevice.h>
#include <glm/vec4.hpp>
#include <memory>
#include <VertexBuffer.h>
#include <Shader.h>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>
#include <FileReader.h>
 
std::string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}

int main(){

    std::cout << GetCurrentWorkingDir() << std::endl;

    yage::WindowDesc desc;
    desc.floating = true;

    yage::Window window(desc);
    std::shared_ptr<yage::GLDevice> gld = window.getGraphicsDevice();
    std::vector<yage::Vertex> vertices;

    vertices.push_back(yage::Vertex());
    vertices.push_back(yage::Vertex());
    vertices.push_back(yage::Vertex());
    
    vertices[0].position = glm::vec3(0.0, 1.0, 0.0);
    vertices[1].position = glm::vec3(1.0, 0.0, 0.0);
    vertices[2].position = glm::vec3(-1.0, 0.0, 0.0);

    yage::VertexBufferDesc buffer_desc;
    buffer_desc.has_position = true;
    buffer_desc.keep_shadow_buffer = true;

    std::shared_ptr<yage::VertexBuffer> buffer = std::make_shared<yage::VertexBuffer>(buffer_desc, vertices);
    gld->setClearColor(glm::vec4(1, 0.5, 0.25, 1));
    yage::FileReader reader;
    std::string vs = reader.readAsString("assets/shaders/basic.vs");
    std::string fs = reader.readAsString("assets/shaders/basic.fs");
    yage::Shader shader(vs.c_str(), fs.c_str());

    while(!window.shouldClose()){
        gld->clearBuffers();
        shader.activate();
        buffer->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        buffer->unbind();
        window.update();
    }


    return 0;
}
