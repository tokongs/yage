#include "GameObject.h"

namespace yage{
GameObject::GameObject(int id)
 : m_id(id){

}

void GameObject::AttachComponent(GameObjectPtr object, yage::ComponentPtr component) {
    object->m_components[component->getComponentType()] = component;
    component->setGameObject(object);
}

ComponentPtr GameObject::getComponentOfType(yage::ComponentType type) {
    if(m_components.find(type) != m_components.end()){
        return m_components.at(type);
    }else{
        return nullptr;
    }
}

ComponentPtr GameObject::getComponent(int id) {
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