#include "yage.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include "GLDevice.h"
#include <memory>
#include "Shader.h"
#include "Util.h"
#include "ResourceManager.h"
#include "MeshLoader.h"
#include "Renderer.h"
#include "Gui.h"
#include "ResourceBrowser.h"
#include "MeshResourceView.h"
#include "ShaderResourceView.h"
#include <GameObjects/GameObject.h>
#include <gui/SceneView.h>
#include "Input.h"
#include "Camera.h"
#include "Configuration.h"
#include "MovingCamera.h"


int main(int argc, char **argv) {

    yage::yage::InitYage();
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
    yage::GLDevice *device = window.getGraphicsDevice();
    /////////////////////////////////////////////////////////////////////
    std::shared_ptr<MovingCamera> cam = std::make_shared<MovingCamera>();

    //Set up Input
    yage::Input::eventBus.subscribe(cam.get(), EventType::KeyPressEvent);
    yage::Input::eventBus.subscribe(cam.get(), EventType::KeyRepeatEvent);
    yage::Input::eventBus.subscribe(cam.get(), EventType::MouseScrollEvent);

    /////////////////////////////////////////////////////////////
    //Set resource dir and load resources
    yage::ResourceManager::getInstance().setResourceDir(Configuration::getAssetsFolderPath() + "/");
    yage::ResourceManager::getInstance().loadAllResources();


    //////////////////////////////////////////////////

    yage::Scene *scene = new yage::Scene("My Scene");
    yage::GameObject *object = scene->createGameObject("MyObject");
    yage::MeshComponent *meshComp = scene->createComponent<yage::MeshComponent>(object);
    yage::MaterialComponent *materialComp = scene->createComponent<yage::MaterialComponent>(object);
    meshComp->mMesh = yage::ResourceManager::getInstance().getResource<yage::Mesh>("Lego");
    materialComp->mMaterial = yage::ResourceManager::getInstance().getResource<yage::Material>("TestMaterial");

    //Set up gui
    yage::Gui gui(window.getWindowHandle(), 460);
    yage::ResourceBrowser *resourceBrowser = new yage::ResourceBrowser();
    resourceBrowser->addResourceView<yage::Mesh>(yage::MeshResourceView());
    resourceBrowser->addResourceView<yage::Shader>(yage::ShaderResourceView());

    yage::SceneView *sceneView = new yage::SceneView(scene);

    gui.addGuiElement(resourceBrowser);
    gui.addGuiElement(sceneView);
    ///////////////////////////////////////////////////////////

    device->setClearColor(glm::vec4(1, 0.5, 0.25, 1));

    while (!window.shouldClose()) {
        glfwPollEvents();
        yage::Input::handleInputs();
        device->clearBuffers();
        yage::Renderer::SetCamera(*cam);
        scene->render();
        gui.constructFrame();

        window.update();
    }

    delete resourceBrowser;
    delete sceneView;
    delete scene;
    yage::yage::ShutdownYage();
    return 0;
}
