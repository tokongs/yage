#include "yage.h"
namespace yage{
    MeshLoader* yage::meshLoader = new MeshLoader();
    ShaderLoader* yage::shaderLoader = new ShaderLoader();
    ScriptLoader* yage::scriptLoader = new ScriptLoader();
    MaterialLoader* yage::materialLoader = new MaterialLoader();

    void yage::InitYage(){
        Logger::Init();
        Input::Init();
        SceneManager::Init();
        ScriptingEngine::Init();
        Renderer::Init();

        ResourceManager::getInstance().registerResourceLoader("mesh", meshLoader);
        ResourceManager::getInstance().registerResourceLoader("shader", shaderLoader);
        ResourceManager::getInstance().registerResourceLoader("script", scriptLoader);
        ResourceManager::getInstance().registerResourceLoader("material", materialLoader);

    }

    void yage::ShutdownYage(){
        delete meshLoader;
        delete shaderLoader;
        delete scriptLoader;
        delete materialLoader;
    }
}
