#pragma once
#include "config.h"
#include "Logger.h"
#include "ScriptingEngine.h"

namespace yage{
    void InitYage(){
        Logger::Init();
        Input::Init();
        ScriptingEngine::Init();
    }
}
