#pragma once

#include <vector>
#include "GameObject.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "Renderer.h"
#include "queue"
#include "CameraComponent.h"
#include "ScriptComponent.h"

namespace yage {
    typedef std::vector<GameObject *> GameObjectList;
    typedef std::unordered_map<std::type_index, std::unordered_map<int, Component *>> ComponentMap;

    class Scene {

    public:
        Scene(const std::string name);

        ~Scene();

        GameObject *createGameObject(std::string name);

        GameObject *getGameObject(std::string name);

        GameObject *getGameObject(int id);

        template<typename T>
        T *createComponent(GameObject *object) {
            auto component = mComponents[typeid(T)].find(object->getId());
            if (component != mComponents[typeid(T)].end()) {
                delete component->second;
            }
            T *result = new T();
            mComponents[typeid(T)][object->getId()] = result;
            object->attachComponent(result);
            return result;
        }

        void render() const;
        void executeScripts() const;

        GameObjectList getGameObjects() const;

        CameraComponent* getActiveCameraComponent();
        void setActiveCameraComponent(CameraComponent* component);
        std::string getName() const;

    private:
        const std::string mName;
        GameObjectList mGameObjects;
        ComponentMap mComponents;
        CameraComponent* mActiveCameraComponent = nullptr;
        std::queue<int> mFreeIds;
        int mNextId = 0;
    };
}