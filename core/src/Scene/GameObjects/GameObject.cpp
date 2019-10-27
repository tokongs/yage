#include "GameObject.h"

namespace yage{
GameObject::GameObject(int id, std::string name)
 : mId(id), mName(name){

}

std::string GameObject::getName() {
    return mName;
}

int GameObject::getId(){
    return mId;
}

}