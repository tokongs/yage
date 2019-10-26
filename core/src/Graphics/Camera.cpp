#include "Camera.h"

namespace yage
{
Camera::Camera()
    : mPosition(glm::vec3(0, 0, 3.0f)), mTarget(glm::vec3(0, 0, 0)), mFront(glm::vec3(0, 0, -1)),
      mUpDir(glm::vec3(0, 1, 0)), mFov(3.14f / 6.0f), mAspectRatio(16.0f / 9.0f), mNearClip(0.1f), mFarClip(1000.0f)
{
    calculateViewMatrix();
    calculateProjectionMatrix();
}

Camera::Camera(glm::vec3 position, glm::vec3 target)
        : mPosition(position), mTarget(target), mDirection(glm::normalize(position - target)), mFront(glm::vec3(0, 0, -1)),
          mUpDir(glm::vec3(0, 1, 0)), mFov(3.14f / 6.0f), mAspectRatio(16.0f / 9.0f), mNearClip(0.1f), mFarClip(1000.0f)
{
    calculateViewMatrix();
    calculateProjectionMatrix();
}

Camera::~Camera()
{
}

glm::vec3 Camera::getPosition()
{
    return mPosition;
}

glm::mat4 Camera::getProjectionMatrix()
{
    calculateProjectionMatrix();
    return mProjectionMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
    calculateViewMatrix();

    return mViewMatrix;
}

glm::mat4 Camera::getProjectionViewMatrix()
{
    return getProjectionMatrix() * getViewMatrix();
}

void Camera::moveAbsolute(glm::vec3 movement)
{
    mPosition += movement;
    calculateViewMatrix();
}

void Camera::moveRelative(glm::vec3 movement)
{
    mPosition += mFront * movement.z;
    mPosition += mUpDir * movement.y;
    mPosition += glm::normalize(glm::cross(mFront, mUpDir)) * movement.x;
}

void Camera::rotate(float pitch, float yaw) {
    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    mFront = glm::normalize(front);
}

void Camera::setPosition(glm::vec3 position)
{
    mPosition = position;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::moveTarget(glm::vec3 movement)
{
    mTarget += movement;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setTarget(glm::vec3 position)
{
    mTarget = position;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setUpDirection(glm::vec3 direction)
{
    mUpDir = direction;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setFoV(float fov)
{
    mFov = fov;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setAspectRatio(float aspect_ratio)
{
    mAspectRatio = aspect_ratio;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setNearClipPlane(float clip)
{
    mNearClip = clip;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::setFarClipPlane(float clip)
{
    mFarClip = clip;
    calculateViewMatrix();
    calculateProjectionMatrix();
}

void Camera::calculateViewMatrix()
{
    mViewMatrix = glm::lookAt(mPosition, mPosition + mFront, mUpDir);
}

void Camera::calculateProjectionMatrix()
{
    mProjectionMatrix = glm::perspective(mFov, mAspectRatio, mNearClip, mFarClip);
}

} // namespace yage