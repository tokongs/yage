#include "Transform.h"
namespace yage{
Transform::Transform(){

}

glm::vec3 Transform::getPosition(){
    return m_position;
}

    glm::vec3 Transform::getScale(){
        return m_scale;
    }

    glm::vec3 Transform::getDirection(){
        return glm::cross(m_up_dir, m_right_dir);
    }

    void Transform::setPosition(glm::vec3 position) {
        m_position = position;
    }

    void Transform::setScale(glm::vec3 scale) {
        m_scale = scale;
    }

    TransformPtr Transform::getParent() {
        return m_parent;
    }

    std::vector<TransformPtr> Transform::getChildren(){
    return m_children;
}
}
