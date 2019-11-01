#pragma once
#include "ResourceLoader.h"
#include "FileReader.h"
#include "Texture.h"
#include <pugixml/pugixml.hpp>


namespace yage {

    class TextureLoader : public ResourceLoader {
    public:
        TextureLoader();
        ~TextureLoader();
        Resource *load(std::string filePath) override;

    private:
        FileReader mFileReader;
    };
}