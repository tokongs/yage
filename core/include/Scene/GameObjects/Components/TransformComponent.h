#pragma once

#include <Transform.h>

namespace yage{
    struct TransformComponent : public Component {
        TransformComponent(){};
        COMPONENT_CLASS_TYPE(TransformComponent);
        Transform mData;
    };
}