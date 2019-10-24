//
// Created by tokongs on 24.10.2019.
//

#include "ScriptingEngine.h"
namespace yage{
sol::state ScriptingEngine::m_lua_state = sol::state();

void ScriptingEngine::Init() {
    OpenLibs();
}

void ScriptingEngine::OpenLibs() {
    m_lua_state.open_libraries(sol::lib::base, sol::lib::package);
}

void ScriptingEngine::ExecuteScript(yage::ScriptPtr script) {
    m_lua_state.script(script->getContent());
}
}