#pragma once
#include <glm/vec4.hpp>
#include "Resource.h"
#include "Program.h"

namespace yage
{
class Material : public Resource
{
    public:
    Material();
    ~Material();

    void activate();

    private:
    glm::vec4 mAmbientColor;
    glm::vec4 mDiffuseColor;
    glm::vec4 mSpecularColor;


    Program m_shader_program;
    
};
} // namespace yage