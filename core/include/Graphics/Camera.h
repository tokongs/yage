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
    Camera(glm::vec3 position, glm::vec3 target);
    ~Camera();

    void moveAbsolute(glm::vec3 movement);
    void moveRelative(glm::vec3 movement);
    void rotate(float pitch, float yaw);
    void setPosition(glm::vec3 position);

    void moveTarget(glm::vec3 movement);
    void setTarget(glm::vec3 position);

    void setUpDirection(glm::vec3 direction);
    void setFoV(float fov);
    void setAspectRatio(float aspectRatio);
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
    glm::mat4 mViewMatrix;
    glm::mat4 mProjectionMatrix;

    glm::vec3 mPosition;
    glm::vec3 mDirection;

    float mFov;
    float mAspectRatio;
    float mNearClip;
    float mFarClip;

    glm::vec3 mTarget;
    glm::vec3 mUpDir;
    glm::vec3 mFront;
};
} // namespace yage