#pragma once
#include <glm/vec3.hpp>
#include "Program.h"

namespace yage
{

enum LIGHT_TYPE
{
    DIRECTIONAL,
    SPOT,
    POINT
};
class Light
{
  public:
    Light(LIGHT_TYPE type);
    ~Light();

  private:
    //For point light and spotlight
    glm::vec3 m_postition;

    //For directional light and spotlight
    glm::vec3 m_direction;

    //For all types
    glm::vec3 m_ambient_color;
    glm::vec3 m_specular_color;
    glm::vec3 m_diffuse_color;

    //for point lights
    float m_constant;
    float m_linear;
    float m_quadratic;

    //For spotlights
    float m_cut_off;

    LIGHT_TYPE m_light_type;
};

} // namespace yage