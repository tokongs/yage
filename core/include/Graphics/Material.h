#pragma once

#include <glm/vec4.hpp>
#include "Resource.h"
#include "Program.h"

namespace yage {
    class Material : public Resource {
    public:
        Material(Ref <Program> program);

        Ref<Program> getShaderProgram();

    private:
        glm::vec4 mAmbientColor;
        glm::vec4 mDiffuseColor;
        glm::vec4 mSpecularColor;


        Ref <Program> mShaderProgram;

    };
} // namespace yage