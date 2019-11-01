#pragma once

#pragma once

#include <memory>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "ResourceView.h"
#include "Scene.h"
#include "GameObjectElement.h"
namespace yage {
/**
 * @brief Constructs a gui from a MeshPtr.
 *
 */
    class SceneView : public GuiElement {
    public:
        SceneView(Scene *scene);

        void constructFrame(bool independent) override;
        void setScene(Scene *scene);

    private:
        Scene *mScene;
        const std::string m_title = "Game Object Browser";
        std::unordered_map<int, bool> mSelectedObjects;
    };
} // namespace yage