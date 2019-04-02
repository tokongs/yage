#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace yage
{
/**
 * @brief Camera base class. This is a simple camera that just has a 
 * position and a target to be directed towards, as well as a specified up 
 * direction
 * 
 */
class Camera
{
  public:
    Camera();
    ~Camera();

    void move(glm::vec3 movement);
    void setPosition(glm::vec3 position);

    void moveTarget(glm::vec3 movement);
    void setTarget(glm::vec3 position);

    void setUpDirection(glm::vec3 direction);
    void setFoV(float fov);
    void setAspectRatio(float aspect_ratio);
    void setNearClipPlane(float clip);
    void setFarClipPlane(float clip);

    glm::vec3 getPosition();

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
    glm::mat4 getProjectionViewMatrix();

  protected:
    void calculateViewMatrix();
    void calculateProjectionMatrix();

  protected:
    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;

    glm::vec3 m_position;

    float m_fov;
    float m_aspect_ratio;
    float m_near_clip;
    float m_far_clip;

  private:
    glm::vec3 m_target;
    glm::vec3 m_up_dir;
};
} // namespace yage