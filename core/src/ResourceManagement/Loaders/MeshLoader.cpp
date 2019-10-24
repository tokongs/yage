#include "MeshLoader.h"

namespace yage
{
MeshLoader::MeshLoader()
{
}

MeshLoader::~MeshLoader(){

}

ResourcePtr MeshLoader::load(int id, std::string name, std::string file_path){
    std::string file = m_file_reader.readAsString(file_path);
    YAGE_INFO("Loading mesh from file: " + file_path);
    if(file.empty()){
        YAGE_INFO("Trying to load empty mesh from: " + file_path);
        return nullptr;
    }
    
    
    VertexBufferPtr buffer = m_wavefront_loader.loadWavefront(file);
    MeshPtr result = std::make_shared<Mesh>(id, name, file_path, buffer);

    return std::dynamic_pointer_cast<Resource>(result);
}

} // namespace yage