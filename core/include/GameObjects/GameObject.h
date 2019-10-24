#pragma once
#include "Components/Component.h"
#include <memory>
#include <unordered_map>


namespace yage{
class GameObject {
public:
    GameObject(int id);

    int getId();
    static void  AttachComponent(GameObjectPtr object, ComponentPtr component);
    ComponentPtr getComponentOfType(ComponentType type);
    ComponentPtr getComponent(int id);
private:
    int m_id;
    std::unordered_map<ComponentType, ComponentPtr> m_components;
};

typedef std::shared_ptr<GameObject> GameObjectPtr;


}