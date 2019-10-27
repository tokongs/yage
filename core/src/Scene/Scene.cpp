#include <Transform.h>
#include "Scene.h"

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
                delete pair.second;
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
                Renderer::Render(mesh->mMesh, material->mMaterial);
            }
        }
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