//
// Created by tokongs on 24.10.2019.
//

#include "ScriptingEngine.h"
namespace yage{
sol::state ScriptingEngine::m_lua_state = sol::state();

void ScriptingEngine::Init() {
    OpenLibs();
    SetupInputAPI();
}

void ScriptingEngine::OpenLibs() {
    m_lua_state.open_libraries(sol::lib::base, sol::lib::package);
}

void ScriptingEngine::ExecuteScript(yage::ScriptPtr script) {
    m_lua_state.script(script->getContent());
}

void ScriptingEngine::SetupInputAPI() {

    m_lua_state.new_usertype<MouseState>("MouseState",
            "x", &MouseState::x,
            "y", &MouseState::y,
            "MouseButton1", &MouseState::mouse_button_1,
            "MouseButton2", &MouseState::mouse_button_2,
            "MouseButton3", &MouseState::mouse_button_3);

    auto input = m_lua_state["Input"].get_or_create<sol::table>();
    input.set_function("GetKeyState", &Input::GetKeyState);
    input.set_function("GetMouseState", &Input::GetMouseState);
}
}