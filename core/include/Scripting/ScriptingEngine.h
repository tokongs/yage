#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol.hpp>
#include "Logger.h"
#include "Script.h"

namespace yage{
class ScriptingEngine {
public:
    static void Init();
    static void OpenLibs();
    static void ExecuteScript(ScriptPtr script);

private:
    static sol::state m_lua_state;
};

}