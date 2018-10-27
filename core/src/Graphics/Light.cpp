#include "Light.h"

namespace yage
{
Light::Light(LIGHT_TYPE type)
    : m_light_type(type)
{
    m_postition = glm::vec3(10.0f, 10.0f, 10.0f);
    m_direction = glm::vec3(0.0f, -1.0f, 0.0f);

    m_ambient_color = glm::vec3(1.0f, 1.0f, 1.0f);
    m_diffuse_color = glm::vec3(1.0f, 1.0f, 1.0f);
    m_specular_color = glm::vec3(1.0f, 1.0f, 1.0f);

    m_constant = 1.0f;
    m_linear = 0.1f;
    m_quadratic = 0.05f;

    m_cut_off = cos(3.14/12);
}
} // namespace yage