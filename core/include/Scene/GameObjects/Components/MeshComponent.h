#pragma once
#include "Component.h"
#include "Reference.h"
#include "Mesh.h"

namespace yage {
    class MeshComponent : public Component{
    public:
        MeshComponent() {};

        ~MeshComponent() {
            YAGE_INFO("{}",  mMesh->getRefCount())
        }
        COMPONENT_CLASS_TYPE(MeshComponent);

        Ref<Mesh> mMesh;
    };
}