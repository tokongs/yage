#include "Window.h"
#include <GLFW/glfw3.h>
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
#include "TextureLoader.h"
#include "Program.h"
#include "Texture.h"
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
using namespace yage;
using namespace std;
int main(int argc, char **argv)
{

    //Set up window
    WindowDesc desc;
    desc.floating = true;
    desc.decorated = true;
    desc.height = 768;
    desc.width = 1024;
    desc.resizable = true;
    desc.title = "Test";
    shared_ptr<Window> window = make_shared<Window>(desc);
    shared_ptr<GLDevice> device = window->getGraphicsDevice();
    /////////////////////////////////////////////////////////////////////
    Camera cam;

    //Set up Input
    Input *input = &Input::getInstance();
    input->mapKey(GLFW_KEY_SPACE, "test");
    input->registerKeyCallBack(KEY_ACTION::PRESS,
                               "test", function<void()>([]() { cout << "test" << endl; }));
    input->registerMouseButtonCallBack(KEY_ACTION::PRESS,
                                       GLFW_MOUSE_BUTTON_1,
                                       function<void()>(bind(&Camera::move, &cam, glm::vec3(1, 0, 0))));
    /////////////////////////////////////////////////////////////
    //Set resource dir and load resources
    ResourceManager *res_manager = &ResourceManager::getInstance();
    res_manager->setResourceDir("/home/tokongs/projects/personal/yage/assets/");
    shared_ptr<MeshLoader> mesh_loader = make_shared<MeshLoader>();
    shared_ptr<ShaderLoader> shader_loader = make_shared<ShaderLoader>();
    shared_ptr<TextureLoader> texture_loader = make_shared<TextureLoader>();

    res_manager->registerResourceLoader<Mesh>(mesh_loader);
    res_manager->registerResourceLoader<Shader>(shader_loader);
    res_manager->registerResourceLoader<Texture>(texture_loader);

    int mesh = res_manager->getHandle<Mesh>("box");
    int vertex = res_manager->getHandle<Shader>("basic_vertex_shader");
    int fragment = res_manager->getHandle<Shader>("basic_fragment_shader");
    //////////////////////////////////////////////////////////////////////7

    Renderer renderer;

    //Set up shaders
    ProgramPtr program = make_shared<Program>();

    vector<ShaderPtr> shaders;
    shaders.push_back(res_manager->getResource<Shader>(vertex));
    shaders.push_back(res_manager->getResource<Shader>(fragment));
    program->attachShaders(shaders);
    //////////////////////////////////////////////////

    //Set up gui
    Gui gui(window->getWindowHandle(), 460);
    unique_ptr<ResourceBrowser> resource_browser = make_unique<ResourceBrowser>();

    resource_browser->addResourceView(std::type_index(typeid(Mesh)), make_unique<MeshResourceView>());
    resource_browser->addResourceView(std::type_index(typeid(Shader)), make_unique<ShaderResourceView>());

    function<void()> func(bind(&ResourceBrowser::open, resource_browser.get())); // maybe(probably) bad i guess?
    func();
    unique_ptr<MainMenu> main_menu = make_unique<MainMenu>();
    unique_ptr<MenuElement> view_rb = make_unique<MenuElement>("Resource Browser", func);
    main_menu->addMenuItem("View", move(view_rb));
    gui.addGuiElement(move(main_menu));
    gui.addGuiElement(move(resource_browser));
    ///////////////////////////////////////////////////////////

    device->setClearColor(glm::vec4(1, 0.5, 0.25, 1));

    while (!window->shouldClose())
    {
        glfwPollEvents();
        device->clearBuffers();
        renderer.setCamera(cam);
        renderer.render(res_manager->getResource<Mesh>(mesh)->getVertexBuffer(), program);
        gui.constructFrame();

        window->update();
    }

    return 0;
}