#pragma once
#include <vector>
#include "GameObject.h"
namespace yage {
    typedef std::vector<GameObject*> GameObjectList;
    class Scene {

    public:
        Scene(const std::string name);
        ~Scene();

        void addGameObject(GameObject* object);
        GameObject* getGameObject(std::string name);
        GameObject* getGameObject(int id);

        GameObjectList getGameObjects() const;
        std::string getName() const;

    private:
        const std::string mName;
        GameObjectList mGameObjects;
    };
}