#include "GameObject.h"

namespace yage{
GameObject::GameObject(int id, std::string name)
 : m_id(id), m_name(name){

}

void GameObject::attachComponent(yage::Component* component) {
    m_components[component->getComponentType()] = component;
    component->setGameObject(this);
}

Component* GameObject::getComponentOfType(yage::ComponentType type) {
    if(m_components.find(type) != m_components.end()){
        return m_components.at(type);
    }else{
        return nullptr;
    }
}

Component* GameObject::getComponent(int id) {
    for(auto it = m_components.begin(); it != m_components.end(); it++){
        if(it->second->getId() == id)
            return it->second;
    }
    return nullptr;
}

int GameObject::getId(){
    return m_id;
}

}