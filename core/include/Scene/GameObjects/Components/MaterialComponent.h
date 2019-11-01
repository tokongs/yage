#pragma once

#include <Graphics/Material.h>

namespace yage {
    struct MaterialComponent : public Component{

        MaterialComponent() {};

        COMPONENT_CLASS_TYPE(MaterialComponent);

        Ref<Material> mData;
    };
}