#include <Transform.h>
#include "Scene.h"
#include <Scripting/ScriptingEngine.h>

namespace yage{
    Scene::Scene(const std::string name)
    : mName(name){

    }

    Scene::~Scene() {
        for(auto it : mGameObjects){
            if(it)
                delete it;

        }

        for(auto it : mComponents){
            for(auto pair : it.second){
                Component* t = pair.second;
                YAGE_INFO("Deleting component")
                delete t;
            }
        }
    }

    GameObject* Scene::createGameObject(std::string name) {
        if(!mFreeIds.empty()){
            int id = mFreeIds.front();
            mFreeIds.pop();
            GameObject* result = new GameObject(id, name);
            mGameObjects.push_back(result);
            return result;
        }else
        {
            GameObject* result = new GameObject(mNextId, name);
            mNextId++;
            mGameObjects.push_back(result);
            return result;
        }
    }

    void Scene::render() const{
        for(auto object : mGameObjects){
            TransformComponent* transform = object->getComponent<TransformComponent>();
            MeshComponent*      mesh = object->getComponent<MeshComponent>();
            MaterialComponent*  material = object->getComponent<MaterialComponent>();
            if(mesh && material){
                Renderer::SetCamera(mActiveCameraComponent->mData);
                Renderer::Render(mesh->mData, material->mData);
            }
        }
    }

    void Scene::executeScripts() const {
        for(auto object : mGameObjects){
            ScriptComponent* script = object->getComponent<ScriptComponent>();
            ScriptingEngine::ExecuteOnUpdate(object, script->mData.get());
        }
    }

    CameraComponent* Scene::getActiveCameraComponent() {
        return mActiveCameraComponent;
    }

    void Scene::setActiveCameraComponent(yage::CameraComponent *component) {
        mActiveCameraComponent = component;
    }

    GameObjectList Scene::getGameObjects() const{
        return mGameObjects;
    }

    std::string Scene::getName() const {
        return mName;
    }

    GameObject* Scene::getGameObject(std::string name) {
        for(auto it: mGameObjects){
            if(it->getName() == name){
                return it;
            }
        }
        return nullptr;
    }

    GameObject* Scene::getGameObject(int id) {
        for(auto it: mGameObjects){
            if(it->getId() == id){
                return it;
            }
        }

        return nullptr;
    }
}