#pragma once
#include "Components/Component.h"
#include <memory>
#include <typeindex>
#include <unordered_map>


namespace yage{
class GameObject {
public:
    GameObject(int id, std::string name);

    int getId();
    std::string getName();

    void setName(std::string name);

    template<typename T>
    void attachComponent(T *component){
        mComponents[typeid(T)] = component;
    }

    template<typename T>
    T *getComponent() {
        auto result = mComponents.find(typeid(T));
        if(result != mComponents.end())
            return (T*)result->second;
        else
            return nullptr;
    }

private:
    int mId;
    std::string mName;
    std::unordered_map<std::type_index, Component*> mComponents;
};
}