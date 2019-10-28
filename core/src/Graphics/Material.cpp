#include "Material.h"

namespace yage{
    Material::Material(yage::Ref<yage::Shader> shader)
    :mShader(shader){

    }

    Ref<Shader> Material::getShader(){
        return mShader;
    }
}
