#include "yage.h"
namespace yage{
    MeshLoader* yage::meshLoader = new MeshLoader();
    ShaderLoader* yage::shaderLoader = new ShaderLoader();
    ScriptLoader* yage::scriptLoader = new ScriptLoader();
    MaterialLoader* yage::materialLoader = new MaterialLoader();
    TextureLoader* yage::textureLoader = new TextureLoader();

    void yage::InitYage(){
        Logger::Init();
        Input::Init();
        SceneManager::Init();
        ScriptingEngine::Init();
        Renderer::Init();

        ResourceManager::getInstance().registerResourceLoader("Mesh", meshLoader);
        ResourceManager::getInstance().registerResourceLoader("Texture", textureLoader);
        ResourceManager::getInstance().registerResourceLoader("Shader", shaderLoader);
        ResourceManager::getInstance().registerResourceLoader("Script", scriptLoader);
        ResourceManager::getInstance().registerResourceLoader("Material", materialLoader);

    }

    void yage::ShutdownYage(){
        delete textureLoader;
        delete meshLoader;
        delete shaderLoader;
        delete scriptLoader;
        delete materialLoader;
    }
}
