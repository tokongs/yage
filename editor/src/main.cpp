#include "yage.h"
#include <GL/glew.h>
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
#include <Scene/GameObjects/Components/ScriptComponent.h>
#include "Input.h"
#include "Camera.h"
#include "Configuration.h"


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
   yage::Camera cam;

    /////////////////////////////////////////////////////////////
    //Set resource dir and load resources
    yage::ResourceManager::getInstance().setResourceDir(Configuration::getAssetsFolderPath() + "/");
    yage::ResourceManager::getInstance().loadAllResources();


    //////////////////////////////////////////////////

    yage::Scene *scene = new yage::Scene("My Scene");
    yage::GameObject *object = scene->createGameObject("MyObject");
    yage::MeshComponent *meshComp = scene->createComponent<yage::MeshComponent>(object);
    yage::MaterialComponent *materialComp = scene->createComponent<yage::MaterialComponent>(object);
    yage::ScriptComponent *scriptComp = scene->createComponent<yage::ScriptComponent>(object);
    yage::CameraComponent *cameraComp = scene->createComponent<yage::CameraComponent>(object);

    meshComp->mData = yage::ResourceManager::getInstance().getResource<yage::Mesh>("DefaultMesh");
    materialComp->mData = yage::ResourceManager::getInstance().getResource<yage::Material>("DefaultMaterial");
    scriptComp->mData = yage::ResourceManager::getInstance().getResource<yage::Script>("CameraScript");
    cameraComp->mData = cam;

    scene->setActiveCameraComponent(cameraComp);
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
        scene->render();
        scene->executeScripts();
        gui.constructFrame();
        window.update();
    }

    delete resourceBrowser;
    delete sceneView;
    delete scene;
    yage::yage::ShutdownYage();
    return 0;
}
