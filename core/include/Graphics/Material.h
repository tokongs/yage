#pragma once
#include <memory>
#include <glm/vec4.hpp>
#include "Resource.h"
#include "Program.h"
#include "Texture.h"

namespace yage
{
/**
 * @brief This describes how an object should be drawn
 * 
 */
class Material : public Resource
{
  public:
    Material();
    ~Material();

    /**
     * @brief The materials program needs to be active when calling this function.
     * 
     */
    void enable();

    ProgramPtr getProgram();

    void setAmbientColor(glm::vec4 color);
    void setDiffuseColor(glm::vec4 color);
    void setSpecularColor(glm::vec4 color);

    void setShininess(float shine);

    void setAmbientTexture(TexturePtr texture);
    void setDiffuseTexture(TexturePtr texture);
    void setSpecularTexture(TexturePtr texture);


    glm::vec4 getAmbientColor();
    glm::vec4 getDiffuseColor();
    glm::vec4 getSpecularColor();

    float getShininess();

    TexturePtr getAmbientTexture();
    TexturePtr getDiffuseTexture();
    TexturePtr getSpecularTexture();

  private:
    glm::vec4 m_ambient_color;
    glm::vec4 m_diffuse_color;
    glm::vec4 m_specular_color;

    float m_shininess;

    TexturePtr m_ambient_texture;
    TexturePtr m_diffuse_texture;
    TexturePtr m_specular_texture;

    ProgramPtr m_shader_program;
};

typedef std::shared_ptr<Material> MaterialPtr;
} // namespace yage