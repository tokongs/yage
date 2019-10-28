#pragma once

#include "ResourceLoader.h"
#include "pugixml/pugixml.hpp"
#include "FileReader.h"
#include "Material.h"

namespace yage {

    class MaterialLoader : public ResourceLoader {
    public:
        MaterialLoader();

        Resource *load(std::string filePath) override;

    private:
        FileReader mFileReader;

    };
}