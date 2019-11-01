#include "Component.h"
#include "Camera.h"

namespace yage{
    struct CameraComponent : public Component {
        CameraComponent() {};
        COMPONENT_CLASS_TYPE(CameraComponent);
        Camera mData;
    };
}