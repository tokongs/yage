#include "Window.h"
#include <GLFW/glfw3.h>
#include "GLDevice.h"
#include <memory>
#include "Shader.h"
#include <iostream>
#include "Util.h"
#include "ResourceManager.h"
#include "MeshLoader.h"
#include "ShaderLoader.h"
#include "Program.h"
#include "Renderer.h"
#include "Gui.h"
#include "ResourceBrowser.h"
#include "MeshResourceView.h"
#include "ShaderResourceView.h"
#include "MainMenu.h"
#include "MenuElement.h"
#include <functional>
#include <Events/EventBus.h>
#include <ResourceManagement/Loaders/ScriptLoader.h>
#include <GameObjects/GameObject.h>
#include "Input.h"
#include "Camera.h"
#include "Configuration.h"
#include "MovingCamera.h"
#include "Components/TransformComponent.h"
#include "Script.h"
#include "yage.h"

int main(int argc, char **argv)
{

    yage::InitYage();
    Configuration::Load(argc, argv);


    //Set up window
    yage::WindowDesc desc;
    desc.floating = true;
    desc.decorated = true;
    desc.height = 768;
    desc.width = 1024;
    desc.resizable = true;
    desc.title = "Test";
    yage::Window window(desc);
    yage::GLDevice* device = window.getGraphicsDevice();
    /////////////////////////////////////////////////////////////////////
    std::shared_ptr<MovingCamera> cam = std::make_shared<MovingCamera>();

    //Set up Input
    yage::Input::eventBus.subscribe(cam.get(), EventType::KeyPressEvent);
    yage::Input::eventBus.subscribe(cam.get(), EventType::KeyRepeatEvent);
    yage::Input::eventBus.subscribe(cam.get(), EventType::MouseScrollEvent);

    /////////////////////////////////////////////////////////////
    //Set resource dir and load resources
    yage::ResourceManager::getInstance().setResourceDir(Configuration::getAssetsFolderPath() + "/");
    yage::MeshLoader* meshLoader = new yage::MeshLoader();
    yage::ShaderLoader* shaderLoader = new yage::ShaderLoader();
   yage::ScriptLoader* scriptLoader = new yage::ScriptLoader();

    yage::ResourceManager::getInstance().registerResourceLoader<yage::Mesh>(meshLoader);
    yage::ResourceManager::getInstance().registerResourceLoader<yage::Shader>(shaderLoader);
    yage::ResourceManager::getInstance().registerResourceLoader<yage::Script>(scriptLoader);

    int mesh = yage::ResourceManager::getInstance().getHandle<yage::Mesh>("lego");
    int vertex = yage::ResourceManager::getInstance().getHandle<yage::Shader>("basic_vertex_shader");
    int fragment = yage::ResourceManager::getInstance().getHandle<yage::Shader>("basic_fragment_shader");
   int script = yage::ResourceManager::getInstance().getHandle<yage::Script>("test");
    //////////////////////////////////////////////////////////////////////7


    yage::Renderer renderer;

    //Set up shaders
    yage::Program* program = new yage::Program();

    std::vector<int> shaders;
    shaders.push_back(vertex);
    shaders.push_back(fragment);
    program->attachShaders(shaders);
    //////////////////////////////////////////////////

    //Set up gui
    yage::Gui gui(window.getWindowHandle(), 460);
    yage::ResourceBrowser* resourceBrowser = new yage::ResourceBrowser();
    resourceBrowser->addResourceView<yage::Mesh>(yage::MeshResourceView());
    resourceBrowser->addResourceView<yage::Shader>(yage::ShaderResourceView());
    gui.addGuiElement(resourceBrowser);
    ///////////////////////////////////////////////////////////

    device->setClearColor(glm::vec4(1, 0.5, 0.25, 1));


    while (!window.shouldClose())
    {
        glfwPollEvents();
        yage::Input::handleInputs();
        device->clearBuffers();
        renderer.setCamera(*cam);
        yage::ScriptingEngine::ExecuteScript(yage::ResourceManager::getInstance().getResource<yage::Script>(script));
        renderer.render(yage::ResourceManager::getInstance().getResource<yage::Mesh>(mesh)->getVertexBuffer(), program);
        gui.constructFrame();

        window.update();
    }
    delete resourceBrowser;
    delete program;
    delete meshLoader;
    delete shaderLoader;
    delete scriptLoader;
    return 0;
}
