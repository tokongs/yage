#include "Camera.h"

namespace yage
{
Camera::Camera()
    : mPosition(glm::vec3(0, 0, 3.0f)), mTarget(glm::vec3(0, 0, 0)), mFront(glm::vec3(0, 0, -1)),
      mUpDir(glm::vec3(0, 1, 0)), mFov(3.14f / 6.0f), mAspectRatio(16.0f / 9.0f), mNearClip(0.1f), mFarClip(1000.0f)
{
}

Camera::Camera(glm::vec3 position, glm::vec3 target)
        : mPosition(position), mTarget(target), mFront(glm::vec3(0, 0, -1)),
          mUpDir(glm::vec3(0, 1, 0)), mFov(3.14f / 6.0f), mAspectRatio(16.0f / 9.0f), mNearClip(0.1f), mFarClip(1000.0f)
{
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
}

void Camera::moveRelative(glm::vec3 movement)
{
    glm::vec3 dir = glm::normalize(mTarget - mPosition);
    mPosition += dir * movement.z;
    mPosition += mUpDir * movement.y;
    mPosition += glm::normalize(glm::cross(dir, mUpDir)) * movement.x;
    mTarget = mPosition +dir;
}

glm::vec3 Camera::getDirection(){
    return glm::normalize(mTarget - mPosition);
}
void Camera::rotate(float pitch, float yaw, float roll) {

    glm::vec3 dir = glm::normalize(mTarget - mPosition);
    glm::vec3 axis = glm::cross(dir, mUpDir);
    glm::quat qPitch = glm::angleAxis(pitch, axis);
    glm::quat qYaw = glm::angleAxis(yaw, mUpDir);
    glm::quat rotation = glm::normalize(glm::cross(qPitch, qYaw));
    dir = rotation * dir;
    mTarget = mPosition + dir;

    mViewMatrix = glm::lookAt(mPosition, mTarget, mUpDir);
}

void Camera::setPosition(glm::vec3 position)
{
    mPosition = position;
}

void Camera::moveTarget(glm::vec3 movement)
{
    mTarget += movement;
}

void Camera::setTarget(glm::vec3 position)
{
    mTarget = position;
}

void Camera::setUpDirection(glm::vec3 direction)
{
    mUpDir = direction;
}

void Camera::setFoV(float fov)
{
    mFov = fov;
}

void Camera::setAspectRatio(float aspect_ratio)
{
    mAspectRatio = aspect_ratio;
}

void Camera::setNearClipPlane(float clip)
{
    mNearClip = clip;
}

void Camera::setFarClipPlane(float clip)
{
    mFarClip = clip;
}

void Camera::calculateViewMatrix()
{

    mViewMatrix = glm::lookAt(mPosition, mTarget, mUpDir);
}

void Camera::calculateProjectionMatrix()
{
    mProjectionMatrix = glm::perspective(mFov, mAspectRatio, mNearClip, mFarClip);
}

} // namespace yage