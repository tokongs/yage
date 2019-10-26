#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <memory>
#include <vector>

namespace yage{

    class Transform{
    public:
        Transform();

        glm::vec3 getPosition();
        glm::vec3 getScale();
        glm::vec3 getDirection();

        void setPosition(glm::vec3 position);
        void setScale(glm::vec3 scale);

        Transform* getParent();
        std::vector<Transform*> getChildren();

    private:
        glm::vec3 mPosition;
        glm::vec3 mRightDir;
        glm::vec3 mUpDir;

        glm::vec3 mScale;

        Transform* mParent;
        std::vector<Transform*> mChildren;
    };
}