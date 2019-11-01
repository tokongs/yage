#include "Material.h"

namespace yage{
    Material::Material(yage::Ref<yage::Shader> shader)
    :mShader(shader){

    }

    Ref<Shader> Material::getShader(){
        return mShader;
    }

    void Material::activate(){
        mShader->activate();
        if(mAmbientTexture.get())
            mAmbientTexture->activate();
    }

    void Material::setAmbientTexture(yage::Ref<yage::Texture> texture) {
        mAmbientTexture = texture;
    }
}
