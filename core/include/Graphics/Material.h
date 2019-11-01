#pragma once

#include <glm/vec4.hpp>
#include <Graphics/OpenGL/Texture.h>
#include "Resource.h"
#include "Shader.h"
namespace yage {
    class Material : public Resource {
    public:
        Material(Ref <Shader> shader);

        Ref<Shader> getShader();

        void activate();
        void setAmbientTexture(Ref<Texture> texture);

    private:
        glm::vec4 mAmbientColor;
        glm::vec4 mDiffuseColor;
        glm::vec4 mSpecularColor;

        Ref<Texture> mAmbientTexture;

        Ref <Shader> mShader;

    };
} // namespace yage