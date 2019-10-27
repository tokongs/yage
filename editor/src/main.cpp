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
#include <gui/SceneView.h>
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

    //Set up shaders
    yage::Program* program = new yage::Program(yage::ResourceManager::getInstance().getResource<yage::Shader>(vertex), yage::ResourceManager::getInstance().getResource<yage::Shader>(fragment));
    yage::Material* material = new yage::Material(program);
    //////////////////////////////////////////////////

    yage::Scene* scene = new yage::Scene("My Scene");
    yage::GameObject* object = scene->createGameObject("MyObject");
    yage::MeshComponent* meshComp = scene->createComponent<yage::MeshComponent>(object);
    yage::MaterialComponent* materialComp = scene->createComponent<yage::MaterialComponent>(object);
    meshComp->mMesh = yage::ResourceManager::getInstance().getResource<yage::Mesh>(mesh);
    materialComp->mMaterial = yage::Ref<yage::Material>(material);

    //Set up gui
    yage::Gui gui(window.getWindowHandle(), 460);
    yage::ResourceBrowser* resourceBrowser = new yage::ResourceBrowser();
    resourceBrowser->addResourceView<yage::Mesh>(yage::MeshResourceView());
    resourceBrowser->addResourceView<yage::Shader>(yage::ShaderResourceView());

    yage::SceneView* sceneView = new yage::SceneView(scene);

    gui.addGuiElement(resourceBrowser);
    gui.addGuiElement(sceneView);
    ///////////////////////////////////////////////////////////

    device->setClearColor(glm::vec4(1, 0.5, 0.25, 1));

    for(int i = 0; i < 10; i++){
        std::unordered_map<int, yage::Ref<yage::Resource>> resource_map = yage::ResourceManager::getInstance().getResourceMap();
    }


    while (!window.shouldClose())
    {
        glfwPollEvents();
        yage::Input::handleInputs();
        device->clearBuffers();
        yage::ScriptingEngine::ExecuteScript(yage::ResourceManager::getInstance().getResource<yage::Script>(script).get());
        yage::Renderer::SetCamera(*cam);
        scene->render();
        gui.constructFrame();

        window.update();
    }

    delete material;
    delete resourceBrowser;
    delete sceneView;
    delete scene;
    delete program;
    delete meshLoader;
    delete shaderLoader;
    delete scriptLoader;
    return 0;
}
