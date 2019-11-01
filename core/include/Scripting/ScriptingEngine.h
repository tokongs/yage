#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include "Logger.h"
#include "Script.h"
#include "Input.h"
#include "GameObject.h"
#include "Scene.h"
#include "ScriptAPI.h"

namespace yage{

class ScriptingEngine {
public:
    static void Init();
    static void ExecuteOnUpdate(GameObject* object, Script* script);
    static void ExecuteScript(GameObject* object, Script* script);
    static void ExecuteScript(Script* script);

private:


    static sol::state mLuaState;
};
}