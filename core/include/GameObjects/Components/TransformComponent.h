#pragma once

#include <Transform.h>

namespace yage{
    struct TransformComponent : public Component {
        TransformComponent(int id) : Component(id){};

        COMPONENT_CLASS_TYPE(TransformComponent);
        Transform transform;

    };

    typedef std::shared_ptr<TransformComponent> TransformComponentPtr;
}