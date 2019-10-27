#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include "Logger.h"
#include "Script.h"
#include "Input.h"
#include "GameObject.h"

namespace yage{
class ScriptingEngine {
public:
    static void Init();
    static void OpenLibs();
    static void SetupInputAPI();
    static void SetupGameObjectsAPI();
    static void ExecuteScript(Script* script);

private:
    static sol::state mLuaState;
};

}