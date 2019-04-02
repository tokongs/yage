#include "Camera.h"

namespace yage
{
Camera::Camera()
    : m_position(glm::vec3(0, 1, -1)), m_target(glm::vec3(0, 0, 0)),
      m_up_dir(glm::vec3(0, 1, 0)), m_fov(3.14f / 6.0f), m_aspect_ratio(16.0f / 9.0f), m_near_clip(0.1f), m_far_clip(1000.0f)
{
    calculateViewMatrix();
    calculateProjectionMatrix();
}

Camera::~Camera()
{
}

glm::vec3 Camera::getPosition()
{
    return m_position;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return m_projection_matrix;
}

glm::mat4 Camera::getViewMatrix()
{
    return m_view_matrix;
}

glm::mat4 Camera::getProjectionViewMatrix()
{
    return m_projection_matrix * m_view_matrix;
}

void Camera::move(glm::vec3 movement)
{
    m_position += movement;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setPosition(glm::vec3 position)
{
    m_position = position;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::moveTarget(glm::vec3 movement)
{
    m_target += movement;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setTarget(glm::vec3 position)
{
    m_target = position;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setUpDirection(glm::vec3 direction)
{
    m_up_dir = direction;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setFoV(float fov)
{
    m_fov = fov;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setAspectRatio(float aspect_ratio)
{
    m_aspect_ratio = aspect_ratio;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setNearClipPlane(float clip)
{
    m_near_clip = clip;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setFarClipPlane(float clip)
{
    m_far_clip = clip;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::calculateViewMatrix()
{
    m_view_matrix = glm::lookAt(m_position, m_target, m_up_dir);
}

void Camera::calculateProjectionMatrix()
{
    m_projection_matrix = glm::perspective(m_fov, m_aspect_ratio, m_near_clip, m_far_clip);
}

} // namespace yage