#pragma once
#include "Component.h"
#include "Reference.h"
#include "Script.h"

namespace yage {

    class Script;

    struct ScriptComponent : public Component{
        ScriptComponent() {};
        COMPONENT_CLASS_TYPE(ScriptComponent);
        Ref<Script> mData;
    };
}