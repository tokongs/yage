#pragma once

#include "ResourceLoader.h"
#include "FileReader.h"
#include "Script.h"

namespace yage {
class ScriptLoader : public ResourceLoader {
public:
    ScriptLoader();
    ~ScriptLoader();

    ResourcePtr load(int id, std::string name, std::string file_path) override;

};


}