#include "ResourceLoader.h"
namespace yage
{

ResourceLoader::ResourceLoader(std::string type)
    : m_type(type)
{
}

ResourceLoader::~ResourceLoader()
{
}

ResourcePtr ResourceLoader::load(){

}

} // namespace yage