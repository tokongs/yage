#include "Material.h"

namespace yage
{
Material::Material()
    : m_ambient_color(glm::vec4(1, 0, 1, 1)), m_diffuse_color(glm::vec4(1, 0, 1, 1)),
      m_specular_color(glm::vec4(1, 0, 1, 1)), m_ambient_texture(nullptr),
      m_diffuse_texture(nullptr), m_specular_texture(nullptr)
{
}

Material::~Material()
{
}

void Material::enable()
{
    m_shader_program->setVec3("ambient_color", m_ambient_color);
    m_shader_program->setVec3("diffuse_color", m_diffuse_color);
    m_shader_program->setVec3("specular_color", m_specular_color);

    m_shader_program->setFloat("shininess", m_shininess);

    m_shader_program->setInt("diffuse_texture", m_diffuse_texture->getTextureUnit());
    m_shader_program->setInt("ambient_texture", m_ambient_texture->getTextureUnit());
    m_shader_program->setInt("specular_texture", m_specular_texture->getTextureUnit());

    m_diffuse_texture->bind();
    m_ambient_texture->bind();
    m_specular_texture->bind();
}

ProgramPtr Material::getProgram()
{
    return m_shader_program;
}

void Material::setAmbientColor(glm::vec4 color)
{
    m_ambient_color = color;
}

void Material::setDiffuseColor(glm::vec4 color)
{
    m_diffuse_color = color;
}

void Material::setSpecularColor(glm::vec4 color)
{
    m_specular_color = color;
}

void Material::setShininess(float shine){
    m_shininess = shine;
}

void Material::setAmbientTexture(TexturePtr texture){
    m_ambient_texture = texture;
}

void Material::setDiffuseTexture(TexturePtr texture){
    m_diffuse_texture = texture;
}

void Material::setSpecularTexture(TexturePtr texture){
    m_specular_texture = texture;
}

glm::vec4 Material::getAmbientColor(){
    return m_ambient_color;   
}

glm::vec4 Material::getDiffuseColor(){
    return m_diffuse_color;   
}

glm::vec4 Material::getSpecularColor(){
    return m_specular_color;   
}

float Material::getShininess(){
    return m_shininess;
}

TexturePtr Material::getAmbientTexture(){
    return m_ambient_texture;
}

TexturePtr Material::getDiffuseTexture(){
    return m_diffuse_texture;
}
TexturePtr Material::getSpecularTexture(){
    return m_specular_texture;
}

} // namespace yage
