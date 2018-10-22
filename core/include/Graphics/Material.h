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
    glm::vec4 m_ambient_color;
    glm::vec4 m_diffuse_color;
    glm::vec4 m_specular_color;

    //Texture m_ambient_texture;
    //Texture m_diffuse_texture;
    //Texture m_specular_texture;



    Program m_shader_program;
    
};
} // namespace yage