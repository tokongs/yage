#include "Resource.h"

namespace yage
{
Resource::Resource(unsigned int id, std::string name, std::string path)
    : m_id(id), m_name(name), m_file_path(path)
{
}

Resource::Resource(){
    
}
Resource::~Resource(){

}

unsigned int Resource::getResourceId(){
    return m_id;
}

std::string Resource::getFilePath(){
    return m_file_path;
}

std::string Resource::getName(){
    return m_name;
}

void Resource::setId(int id){
    m_id = id;
}

void Resource::setName(std::string name){
    m_name = name;
}

void Resource::setFilePath(std::string file_path){
    m_file_path = file_path;
}


} // namespace yage