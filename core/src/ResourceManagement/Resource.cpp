#include "Resource.h"

namespace yage{
    Resource::Resource(unsigned int id, std::string name, std::string path)
    :m_id(id), m_name(name), m_filepath(path)
    {

    }
}