#include "ScriptingEngine.h"

namespace yage {
    sol::state ScriptingEngine::mLuaState = sol::state();

    void ScriptingEngine::Init() {
        OpenLuaLibs(&mLuaState);
        SetupInputAPI(&mLuaState);
        SetupGameObjectsAPI(&mLuaState);
        SetupSceneAPI(&mLuaState);
        SetupMathAPI(&mLuaState);
    }

    void ScriptingEngine::ExecuteScript(GameObject *object, yage::Script *script) {
        if (!object) {
            YAGE_ERROR("Trying to bin null object to script! Skipping...");
            return;
        }
        mLuaState["this"] = object;
        ExecuteScript(script);
    }

    void ScriptingEngine::ExecuteOnUpdate(yage::GameObject *object, yage::Script *script) {
        if (!object) {
            YAGE_ERROR("Trying to bin null object to script! Skipping...");
            return;
        }
        if (!script) {
            YAGE_ERROR("Trying to exexute null script! Skipping...");
            return;
        }
        (*script->getLuaState())["this"] = object;
        script->onUpdate();
    }

    void ScriptingEngine::ExecuteScript(yage::Script *script) {
        if (!script) {
            YAGE_ERROR("Trying to exexute null script! Skipping...");
            return;
        }
        mLuaState.script(script->getContent());
    }


}