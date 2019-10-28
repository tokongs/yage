#pragma once
#include "rapidxml/rapidxml.hpp"
#include "config.h"
#include "Mesh.h"
#include "ResourceLoader.h"
#include "FileReader.h"
#include <memory>
#include <string>
#include <WavefrontLoader.h>
#include "Logger.h"
#include "pugixml/pugixml.hpp"

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
        Resource* load(std::string filePath) override;

        private:
        FileReader mFileReader;

        //Loaders
        WavefrontLoader mWavefrontLoader;
    };
}