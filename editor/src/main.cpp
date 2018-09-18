#include <Window.h>
#include <GLDevice.h>
#include <glm/vec4.hpp>
#include <memory>
#include <VertexBuffer.h>

int main(){

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

    while(!window.shouldClose()){
        gld->clearBuffers();
        buffer->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        buffer->unbind();
        window.update();
    }


    return 0;
}
