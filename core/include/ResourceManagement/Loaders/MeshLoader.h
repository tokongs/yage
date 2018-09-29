#pragma once
#include "config.h"
#include "Mesh.h"
#include "ResourceLoader.h"
#include "FileReader.h"
#include <memory>
#include <string>
#include <WavefrontLoader.h>

namespace yage{
    class MeshLoader : public ResourceLoader{
        public:
        MeshLoader(std::string type);
        ~MeshLoader();

        ResourcePtr load(std::string file_path) override;

        private:
        FileReader m_file_reader;

        //Loaders
        WavefrontLoader m_wavefront_loader;

        DECLARE_LOGGERS;
    };
}