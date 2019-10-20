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
#include <ResourceManagement/Loaders/AngelScriptLoader.h>
#include "Input.h"
#include "Camera.h"
#include "Configuration.h"
#include "MovingCamera.h"

int main(int argc, char **argv)
{

    Configuration::Load(argc, argv);

    //Set up window
    yage::WindowDesc desc;
    desc.floating = true;
    desc.decorated = true;
    desc.height = 768;
    desc.width = 1024;
    desc.resizable = true;
    desc.title = "Test";
    std::shared_ptr<yage::Window> window = std::make_shared<yage::Window>(desc);
    std::shared_ptr<yage::GLDevice> device = window->getGraphicsDevice();
    /////////////////////////////////////////////////////////////////////
    std::shared_ptr<MovingCamera> cam = std::make_shared<MovingCamera>();

    //Set up Input
    yage::Input::eventBus.subscribe(cam.get(), EventType::KeyPressEvent);
    yage::Input::eventBus.subscribe(cam.get(), EventType::KeyRepeatEvent);
    yage::Input::eventBus.subscribe(cam.get(), EventType::MouseScrollEvent);

    auto zoomIm =  [](double x, double y){ if(y > 0) std::cout << "resr";};
    std::function<void(double s, double)> cameraZoom = std::function<void(double, double)>(std::bind(zoomIm, 1, 1));
    yage::Input::getInstance().registerMouseScrollCallback(std::function<void(double, double)>(zoomIm));
    /////////////////////////////////////////////////////////////
    //Set resource dir and load resources
    yage::ResourceManager::getInstance().setResourceDir(Configuration::getAssetsFolderPath() + "/");
    std::shared_ptr<yage::MeshLoader> mesh_loader = std::make_shared<yage::MeshLoader>();
    std::shared_ptr<yage::ShaderLoader> shader_loader = std::make_shared<yage::ShaderLoader>();
    std::shared_ptr<yage::AngelScriptLoader> script_loader = std::make_shared<yage::AngelScriptLoader>();

    yage::ResourceManager::getInstance().registerResourceLoader<yage::Mesh>(mesh_loader);
    yage::ResourceManager::getInstance().registerResourceLoader<yage::Shader>(shader_loader);
    yage::ResourceManager::getInstance().registerResourceLoader<yage::Script>(script_loader);

    int mesh = yage::ResourceManager::getInstance().getHandle<yage::Mesh>("lego");
    int vertex = yage::ResourceManager::getInstance().getHandle<yage::Shader>("basic_vertex_shader");
    int fragment = yage::ResourceManager::getInstance().getHandle<yage::Shader>("basic_fragment_shader");
    int script = yage::ResourceManager::getInstance().getHandle<yage::Script>("test");

    yage::ScriptingEngine engine;
    engine.addScript("MyModule", yage::ResourceManager::getInstance().getResource<yage::Script>(script));
    engine.execute();

    //////////////////////////////////////////////////////////////////////7

    yage::Renderer renderer;

    //Set up shaders
    yage::ProgramPtr program = std::make_shared<yage::Program>();

    std::vector<int> shaders;
    shaders.push_back(vertex);
    shaders.push_back(fragment);
    program->attachShaders(shaders);
    //////////////////////////////////////////////////

    //Set up gui
    yage::Gui gui(window->getWindowHandle(), 460);
    std::unique_ptr<yage::ResourceBrowser> resource_browser = std::make_unique<yage::ResourceBrowser>();

    resource_browser->addResourceView<yage::Mesh>(std::make_unique<yage::MeshResourceView>());
    resource_browser->addResourceView<yage::Shader>(std::make_unique<yage::ShaderResourceView>());

    std::function<void()> func(std::bind(&yage::ResourceBrowser::open, resource_browser.get())); // maybe(probably) bad i guess?
    func();
    std::unique_ptr<yage::MainMenu> main_menu = std::make_unique<yage::MainMenu>();
    std::unique_ptr<yage::MenuElement> view_rb = std::make_unique<yage::MenuElement>("Resource Browser", func);
    main_menu->addMenuItem("View", std::move(view_rb));
    gui.addGuiElement(std::move(main_menu));
    gui.addGuiElement(std::move(resource_browser));
    ///////////////////////////////////////////////////////////

    device->setClearColor(glm::vec4(1, 0.5, 0.25, 1));

    while (!window->shouldClose())
    {
        glfwPollEvents();
        yage::Input::getInstance().handleInputs();
        device->clearBuffers();
        renderer.setCamera(*cam);
        renderer.render(yage::ResourceManager::getInstance().getResource<yage::Mesh>(mesh)->getVertexBuffer(), program);
        gui.constructFrame();

        window->update();
    }
    return 0;
}
