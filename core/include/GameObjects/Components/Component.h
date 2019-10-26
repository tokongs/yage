#pragma once
#include <memory>
namespace yage{
enum class ComponentType {
    None = 0,
    TransformComponent
};

#define COMPONENT_CLASS_TYPE(type) static ComponentType GetStaticType() {return ComponentType::type;}\
                                virtual ComponentType getComponentType() const override {return GetStaticType(); }\
                                virtual const char* getName() const override { return #type; }
class GameObject;
typedef std::shared_ptr<GameObject> GameObjectPtr;
struct Component {
    Component(int id) : m_id(id){};

    int getId() {return m_id;};

    void setGameObject(GameObject *object) {mGameObject = object;};
    GameObject *getGameObject() {return mGameObject;};

    virtual ComponentType getComponentType() const = 0;
    virtual const char* getName() const = 0;
    virtual std::string toString() const {return getName(); }
private:
    int m_id;
    GameObject *mGameObject;
};
}