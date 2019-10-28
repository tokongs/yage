#pragma once

#include <glm/vec4.hpp>
#include "Resource.h"
#include "Shader.h"
namespace yage {
    class Material : public Resource {
    public:
        Material(Ref <Shader> shader);

        Ref<Shader> getShader();

    private:
        glm::vec4 mAmbientColor;
        glm::vec4 mDiffuseColor;
        glm::vec4 mSpecularColor;

        Ref <Shader> mShader;

    };
} // namespace yage