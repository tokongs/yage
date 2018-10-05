#include "MeshLoader.h"

namespace yage
{
DEFINE_LOGGERS(MeshLoader);
MeshLoader::MeshLoader()
{
    INIT_LOGGERS(MeshLoader);
}

MeshLoader::~MeshLoader(){

}

ResourcePtr MeshLoader::load(std::string file_path){
    std::string file = m_file_reader.readAsString(file_path);
    LOG(MeshLoader, info, "Loading mesh from file: " + file_path);
    if(file.empty()){
        LOG(MeshLoader, error, "Trying to load empty mesh from: " + file_path);
        return nullptr;
    }
    
    
    VertexBufferPtr buffer = m_wavefront_loader.loadWavefront(file);
    MeshPtr result = std::make_shared<Mesh>(buffer);

    return std::dynamic_pointer_cast<Resource>(result);
}

} // namespace yage