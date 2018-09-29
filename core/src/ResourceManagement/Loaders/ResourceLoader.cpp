#include "ResourceLoader.h"
namespace yage
{

ResourceLoader::ResourceLoader(std::string type)
    : m_type(type)
{
}

ResourceLoader::ResourceLoader(){
}

ResourceLoader::~ResourceLoader()
{
}

std::string ResourceLoader::getType(){
    return m_type;
}


} // namespace yage