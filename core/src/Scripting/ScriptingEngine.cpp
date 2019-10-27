//
// Created by tokongs on 24.10.2019.
//

#include "ScriptingEngine.h"

namespace yage {
    sol::state ScriptingEngine::mLuaState = sol::state();

    void ScriptingEngine::Init() {
        OpenLibs();
        SetupInputAPI();
        SetupGameObjectsAPI();
    }

    void ScriptingEngine::OpenLibs() {
        mLuaState.open_libraries(sol::lib::base, sol::lib::package);
    }

    void ScriptingEngine::ExecuteScript(yage::Script* script) {
        mLuaState.script(script->getContent());
    }

    void ScriptingEngine::SetupInputAPI() {


        mLuaState.new_usertype<MouseState>("MouseState",
                                           "x", &MouseState::x,
                                           "y", &MouseState::y,
                                           "MouseButton1", &MouseState::mouse_button_1,
                                           "MouseButton2", &MouseState::mouse_button_2,
                                           "MouseButton3", &MouseState::mouse_button_3);
        auto input = mLuaState["Input"].get_or_create<sol::table>();

        input.set_function("GetKeyState", &Input::GetKeyState);
        input.set_function("GetMouseState", &Input::GetMouseState);
    }

    void ScriptingEngine::SetupGameObjectsAPI() {
        mLuaState.new_usertype<GameObject>("GameObject",
                                           "new", sol::no_constructor,
                                           "getName", &GameObject::getName);
        mLuaState.new_usertype<Component>("Component",
                                          "new", sol::no_constructor);
    }
}