#include "MeshLoader.h"

namespace yage
{
MeshLoader::MeshLoader()
{
}

MeshLoader::~MeshLoader(){

}

Resource* MeshLoader::load(std::string file_path){
    std::string file = mFileReader.readAsString(file_path);
    YAGE_INFO("Loading mesh from file: " + file_path);
    if(file.empty()){
        YAGE_INFO("Trying to load empty mesh from: " + file_path);
        return nullptr;
    }

    VertexBuffer* buffer = mWavefrontLoader.loadWavefront(file);
    Mesh* result = new Mesh(buffer);


    return result;
}

} // namespace yage