#pragma once
#include "Component.h"
#include "Reference.h"
#include "Mesh.h"

namespace yage {
    class MeshComponent : public Component{
    public:
        MeshComponent() {};
        COMPONENT_CLASS_TYPE(MeshComponent);
        Ref<Mesh> mMesh;
    };
}