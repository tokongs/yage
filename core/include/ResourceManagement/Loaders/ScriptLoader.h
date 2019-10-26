#pragma once

#include "ResourceLoader.h"
#include "FileReader.h"
#include "Script.h"

namespace yage {
class ScriptLoader : public ResourceLoader {
public:
    ScriptLoader();
    ~ScriptLoader();

    Resource* load(std::string filePath) override;

};


}