//
// Created by tokongs on 20.10.2019.
//

#ifndef YAGE_MOVINGCAMERA_H
#define YAGE_MOVINGCAMERA_H


#include "../../core/include/Events/EventListener.h"
#include "../../core/include/Graphics/Camera.h"
#include "../../core/include/Events/InputEvent.h"
#include <GLFW/glfw3.h>


class MovingCamera : public yage::Camera, public EventListener{
public:
    MovingCamera();
    ~MovingCamera();

    virtual void handleEvent(Event* event) override;
};


#endif //YAGE_MOVINGCAMERA_H
