#pragma once

#include <scriptbuilder/scriptbuilder.h>
#include <Scripting/ScriptingEngine.h>
#include "ResourceLoader.h"

namespace yage {
class AngelScriptLoader : public ResourceLoader {
public:
    AngelScriptLoader();
    ~AngelScriptLoader();

    ResourcePtr load(std::string file_path) override;

};


}