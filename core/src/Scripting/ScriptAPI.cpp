#include "ScriptAPI.h"

namespace yage {
    void OpenLuaLibs(sol::state *luaState) {
        luaState->open_libraries(sol::lib::base, sol::lib::package);
    }

    void SetupInputAPI(sol::state *luaState) {
        luaState->new_usertype<MouseState>("MouseState",
                                           "x", &MouseState::x,
                                           "y", &MouseState::y,
                                           "MouseButton1", &MouseState::mouse_button_1,
                                           "MouseButton2", &MouseState::mouse_button_2,
                                           "MouseButton3", &MouseState::mouse_button_3);
        auto input = (*luaState)["Input"].get_or_create<sol::table>();

        input.set_function("GetKeyState", &Input::GetKeyState);
        input.set_function("GetMouseState", &Input::GetMouseState);
    }

    void SetupGameObjectsAPI(sol::state *luaState) {
        luaState->new_usertype<GameObject>("GameObject",
                                           "new", sol::no_constructor,
                                           "getName", &GameObject::getName,
                                           "setName", &GameObject::setName);
        REGISTER_COMPONENT_TO_SCRIPTING_API(luaState, ScriptComponent);
        REGISTER_COMPONENT_TO_SCRIPTING_API(luaState, CameraComponent);
        REGISTER_COMPONENT_TO_SCRIPTING_API(luaState, MeshComponent);
        REGISTER_COMPONENT_TO_SCRIPTING_API(luaState, MaterialComponent);
    }

    void SetupSceneAPI(sol::state *luaState) {
        luaState->new_usertype<Scene>("Scene",
                                      "new", sol::no_constructor,
                                      "getName", &Scene::getName);
        luaState->new_usertype<Camera>("Camera",
                                       "new", sol::no_constructor,
                                       "getPosition", &Camera::getPosition,
                                       "setPosition", &Camera::setPosition,
                                       "moveRelative", &Camera::moveRelative,
                                       "setTarget", &Camera::setTarget,
                                       "moveTarget", &Camera::moveTarget,
                                       "rotate", &Camera::rotate);
    }

    void SetupMathAPI(sol::state *luaState) {
        luaState->new_usertype<glm::vec3>("Vec3",
                                          "x", &glm::vec3::x,
                                          "y", &glm::vec3::y,
                                          "z", &glm::vec3::z);
    }
}