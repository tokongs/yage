#include "GameObjectElement.h"
namespace yage
{
    GameObjectElement::GameObjectElement(GameObject* object)
    : mObject(object)
    {
    }

    void GameObjectElement::constructFrame(bool independent)
    {
        if(!mObject){
            yage::YAGE_WARN("Trying to show a game object gui with no game object.");
        }
        if(independent){
            ImGui::Begin("Resource View", &mOpen);
        }
        ImGui::LabelText("Name:", mObject->getName().c_str());
        ImGui::LabelText("ID:", std::to_string(mObject->getId()).c_str());

        if(independent){
            ImGui::End();
        }

    }
} // namespace yage