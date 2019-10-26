#pragma once
#include "config.h"
#include "Logger.h"
#include "ScriptingEngine.h"
#include "SceneManager.h"

namespace yage{
    void InitYage(){
        Logger::Init();
        Input::Init();
        SceneManager::Init();
        ScriptingEngine::Init();
    }
}
