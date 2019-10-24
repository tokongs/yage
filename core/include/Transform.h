#pragma once

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <memory>
#include <vector>

namespace yage{

    class Transform{
        typedef std::shared_ptr<Transform> TransformPtr;
    public:
        Transform();

        glm::vec3 getPosition();
        glm::vec3 getScale();
        glm::vec3 getDirection();

        void setPosition(glm::vec3 position);
        void setScale(glm::vec3 scale);

        TransformPtr getParent();
        std::vector<TransformPtr> getChildren();

    private:
        glm::vec3 m_position;
        glm::vec3 m_right_dir;
        glm::vec3 m_up_dir;

        glm::vec3 m_scale;

        TransformPtr m_parent;
        std::vector<TransformPtr> m_children;
    };

    typedef std::shared_ptr<Transform> TransformPtr;
}