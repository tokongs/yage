#include "Scene.h"

namespace yage{
    Scene::Scene(const std::string name)
    : mName(name){

    }

    Scene::~Scene() {

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