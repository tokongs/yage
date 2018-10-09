#include "Window.h"
#include "GLDevice.h"
#include <glm/vec4.hpp>
#include <memory>
#include "VertexBuffer.h"
#include "Shader.h"
#include "Window.h"
#include <iostream>
#include "Util.h"
#include "FileReader.h"
#include "ResourceManager.h"
#include "MeshLoader.h"
#include "ShaderLoader.h"
#include "Program.h"
#include "Renderer.h"
#include "Gui.h"
#include "ResourceBrowser.h"
#include "MeshResourceView.h"
#include "ShaderResourceView.h"

int main(int argc, char **argv)
{

    std::cout << getCurrentWorkingDir() << std::endl;

    yage::WindowDesc desc;
    desc.floating = true;
    desc.decorated = true;
    desc.height = 768;
    desc.width = 1024;
    desc.resizable = true;
    desc.title = "Test";
    std::shared_ptr<yage::Window> window = std::make_shared<yage::Window>(desc);
    std::shared_ptr<yage::GLDevice> device = window->getGraphicsDevice();

    yage::Gui gui(window->getWindowHandle(), 460);
   

    yage::ResourceManager::getInstance().setResourceDir("/home/tokongs/projects/personal/yage/assets/");
    std::shared_ptr<yage::MeshLoader> mesh_loader = std::make_shared<yage::MeshLoader>();
    std::shared_ptr<yage::ShaderLoader> shader_loader = std::make_shared<yage::ShaderLoader>();

    yage::ResourceManager::getInstance().registerResourceLoader<yage::Mesh>(mesh_loader);
    yage::ResourceManager::getInstance().registerResourceLoader<yage::Shader>(shader_loader);

    int mesh = yage::ResourceManager::getInstance().getHandle<yage::Mesh>("box");
    int vertex = yage::ResourceManager::getInstance().getHandle<yage::Shader>("basic_vertex_shader");
    int fragment = yage::ResourceManager::getInstance().getHandle<yage::Shader>("basic_fragment_shader");

    yage::ProgramPtr program = std::make_shared<yage::Program>();

    yage::Renderer renderer;

    std::vector<int> shaders;
    shaders.push_back(vertex);
    shaders.push_back(fragment);

    program->attachShaders(shaders);

    device->setClearColor(glm::vec4(1, 0.5, 0.25, 1));

    std::unique_ptr<yage::ResourceBrowser> resource_browser = std::make_unique<yage::ResourceBrowser>();
    resource_browser->addResourceView("mesh", std::make_unique<yage::MeshResourceView>());
    resource_browser->addResourceView("shader", std::make_unique<yage::ShaderResourceView>());
    gui.addGuiElement(std::move(resource_browser));

    while (!window->shouldClose())
    {

        device->clearBuffers();
        renderer.render(yage::ResourceManager::getInstance().getResource<yage::Mesh>(mesh)->getVertexBuffer(), program);
        gui.constructFrame();
        window->update();
    }

    return 0;
}
