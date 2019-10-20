//
// Created by tokongs on 20.10.2019.
//

#include "MovingCamera.h"


MovingCamera::MovingCamera() {

}

MovingCamera::~MovingCamera() {

}

void MovingCamera::handleEvent(Event *event) {
    switch(event->getEventType()){
        case EventType::KeyPressEvent:
            switch(((KeyPressEvent*)event)->getKeyCode()){
                case GLFW_KEY_W:
                    moveRelative(glm::vec3(0, 5, 0));
                    break;
                case GLFW_KEY_S:
                    moveRelative(glm::vec3(0, -5, 0));
                    break;
                case GLFW_KEY_D:
                    moveRelative(glm::vec3(5, 0, 0));
                    break;
                case GLFW_KEY_A:
                    moveRelative(glm::vec3(-5, 0, 0));
                    break;
                case GLFW_KEY_LEFT:
                    rotate(0, .1);
                    break;
            }
            break;

        case EventType::KeyRepeatEvent:
            switch(((KeyRepeatEvent*)event)->getKeyCode()){
                case GLFW_KEY_W:
                    moveRelative(glm::vec3(0, 5, 0));
                    break;
                case GLFW_KEY_S:
                    moveRelative(glm::vec3(0, -5, 0));
                    break;
                case GLFW_KEY_D:
                    moveRelative(glm::vec3(5, 0, 0));
                    break;
                case GLFW_KEY_A:
                    moveRelative(glm::vec3(-5, 0, 0));
                    break;
                case GLFW_KEY_LEFT:
                    rotate(0, .1);
                    break;
            }
            break;

        case EventType::MouseScrollEvent:
            moveRelative(glm::vec3(0, 0, ((MouseScrollEvent*)event)->getScrollDelta().y));
            break;
    }
}