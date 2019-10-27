#include "Material.h"

namespace yage{
    Material::Material(yage::Ref<yage::Program> program)
    :mShaderProgram(program){

    }

    Ref<Program> Material::getShaderProgram(){
        return mShaderProgram;
    }
}
