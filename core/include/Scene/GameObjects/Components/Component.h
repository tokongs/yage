#pragma once

#include <memory>

namespace yage {


#define COMPONENT_CLASS_TYPE(type) virtual const char* getName() const override { return #type; }

    class GameObject;

    struct Component {
        Component() {};

        void setGameObject(GameObject *object) { mGameObject = object; };

        GameObject *getGameObject() { return mGameObject; };

        virtual const char *getName() const = 0;

        virtual std::string toString() const { return getName(); }

    private:
        GameObject *mGameObject;
    };
}