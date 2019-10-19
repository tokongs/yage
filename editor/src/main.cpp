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
#include "Input.h"
#include "Camera.h"
#include "Configuration.h"

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
    yage::Camera cam;

    //Set up Input
    yage::Input::getInstance().mapKey(GLFW_KEY_SPACE, "test");
    yage::Input::getInstance().registerKeyCallBack(yage::KEY_ACTION::PRESS,
                                                   "test", std::function<void()>([]() { std::cout << "test" << std::endl; }));
    yage::Input::getInstance().registerMouseButtonCallBack(yage::KEY_ACTION::PRESS,
                                                           GLFW_MOUSE_BUTTON_1,
                                                           std::function<void()>(std::bind(&yage::Camera::move, &cam, glm::vec3(1, 0, 0))));
    /////////////////////////////////////////////////////////////
    //Set resource dir and load resources
    yage::ResourceManager::getInstance().setResourceDir(Configuration::getAssetsFolderPath() + "/");
    std::shared_ptr<yage::MeshLoader> mesh_loader = std::make_shared<yage::MeshLoader>();
    std::shared_ptr<yage::ShaderLoader> shader_loader = std::make_shared<yage::ShaderLoader>();

    yage::ResourceManager::getInstance().registerResourceLoader<yage::Mesh>(mesh_loader);
    yage::ResourceManager::getInstance().registerResourceLoader<yage::Shader>(shader_loader);

    int mesh = yage::ResourceManager::getInstance().getHandle<yage::Mesh>("box");
    int vertex = yage::ResourceManager::getInstance().getHandle<yage::Shader>("basic_vertex_shader");
    int fragment = yage::ResourceManager::getInstance().getHandle<yage::Shader>("basic_fragment_shader");
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

    resource_browser->addResourceView("mesh", std::make_unique<yage::MeshResourceView>());
    resource_browser->addResourceView("shader", std::make_unique<yage::ShaderResourceView>());

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
        device->clearBuffers();
        renderer.setCamera(cam);
        renderer.render(yage::ResourceManager::getInstance().getResource<yage::Mesh>(mesh)->getVertexBuffer(), program);
        gui.constructFrame();

        window->update();
    }

    return 0;
}
