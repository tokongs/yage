#include "Resource.h"

namespace yage
{
Resource::Resource(unsigned int id, std::string name, std::string path)
    : mID(id), mName(name), mFilePath(path)
{
}

Resource::Resource(){
    
}
Resource::~Resource(){

}

unsigned int Resource::getResourceId(){
    return mID;
}

std::string Resource::getFilePath(){
    return mFilePath;
}

std::string Resource::getName(){
    return mName;
}

void Resource::setId(int id){
    mID = id;
}

void Resource::setName(std::string name){
    mName = name;
}

void Resource::setFilePath(std::string file_path){
    mFilePath = file_path;
}


} // namespace yage