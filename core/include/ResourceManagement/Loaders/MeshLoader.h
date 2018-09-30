#pragma once
#include "config.h"
#include "Mesh.h"
#include "ResourceLoader.h"
#include "FileReader.h"
#include <memory>
#include <string>
#include <WavefrontLoader.h>

namespace yage{
    /**
     * @brief Loader class for meshes
     * 
     */
    class MeshLoader : public ResourceLoader{
        public:
        MeshLoader();
        ~MeshLoader();

        /**
         * @brief reads contnetn from a file path and return a MeshPtr casted to a ResourcePtr
         * 
         * @param file_path 
         * @return ResourcePtr 
         */
        ResourcePtr load(std::string file_path) override;

        private:
        FileReader m_file_reader;

        //Loaders
        WavefrontLoader m_wavefront_loader;

        DECLARE_LOGGERS;
    };
}