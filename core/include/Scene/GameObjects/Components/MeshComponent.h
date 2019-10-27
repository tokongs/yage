#pragma once
#include "Component.h"
#include "Reference.h"
#include "Mesh.h"

namespace yage {
    struct MeshComponent : public Component{

        MeshComponent() {};

        COMPONENT_CLASS_TYPE(MeshComponent);

        Ref<Mesh> mMesh;
    };
}