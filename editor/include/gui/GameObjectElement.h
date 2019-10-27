#pragma once

#pragma once

#include <memory>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "GameObject.h"
#include "GuiElement.h"

namespace yage {
/**
 * @brief Constructs a gui from a MeshPtr.
 *
 */
    class GameObjectElement: public GuiElement {
    public:
        GameObjectElement(GameObject* object);

        void constructFrame(bool independent) override;

    private:
        GameObject *mObject;
    };
} // namespace yage