#pragma once
#include "Components/Component.h"
#include <memory>
#include <unordered_map>


namespace yage{
class GameObject {
public:
    GameObject(int id, std::string name);

    int getId();
    std::string getName();
    void attachComponent(Component* component);
    Component *getComponentOfType(ComponentType type);
    Component *getComponent(int id);
private:
    int m_id;
    std::string m_name;
    std::unordered_map<ComponentType, Component*> m_components;
};
}