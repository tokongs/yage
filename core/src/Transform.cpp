#include "Transform.h"
namespace yage{
Transform::Transform(){

}

glm::vec3 Transform::getPosition(){
    return mPosition;
}

    glm::vec3 Transform::getScale(){
        return mScale;
    }

    glm::vec3 Transform::getDirection(){
        return glm::cross(mUpDir, mRightDir);
    }

    void Transform::setPosition(glm::vec3 position) {
        mPosition = position;
    }

    void Transform::setScale(glm::vec3 scale) {
        mScale = scale;
    }

    Transform* Transform::getParent() {
        return mParent;
    }

    std::vector<Transform*> Transform::getChildren(){
    return mChildren;
}
}
