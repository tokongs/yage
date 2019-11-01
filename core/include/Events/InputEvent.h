#pragma once
#include "Event.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class KeyEvent : public Event {
public:
    KeyEvent(int keyCode) : mKeyCode(keyCode){};

    int getKeyCode() const { return mKeyCode;};
protected:
    const int mKeyCode;
};

class KeyPressEvent : public KeyEvent {
public:
    KeyPressEvent(int keyCode) : KeyEvent(keyCode){};
    EVENT_CLASS_TYPE(KeyPressEvent);
};

class KeyReleaseEvent : public KeyEvent {
public:
    KeyReleaseEvent(int keyCode) : KeyEvent(keyCode){};
    EVENT_CLASS_TYPE(KeyReleaseEvent);
};

class KeyRepeatEvent : public KeyEvent {
public:
    KeyRepeatEvent(int keyCode) : KeyEvent(keyCode){};
    EVENT_CLASS_TYPE(KeyRepeatEvent);
};

class MouseButtonEvent : public Event{
public:
    MouseButtonEvent(int button) : mButton(button){};

    int getButton() const { return mButton;};

protected:
    const int mButton;
};

class MouseButtonPressEvent : public MouseButtonEvent{
public:
    MouseButtonPressEvent(int button) : MouseButtonEvent(button){};
    EVENT_CLASS_TYPE(MouseButtonPressEvent);
};

class MouseButtonReleaseEvent : public MouseButtonEvent{
public:
    MouseButtonReleaseEvent(int button) : MouseButtonEvent(button){};
    EVENT_CLASS_TYPE(MouseButtonReleaseEvent);
};

class MouseButtonRepeatEvent : public MouseButtonEvent{
public:
    MouseButtonRepeatEvent(int button) : MouseButtonEvent(button){};
    EVENT_CLASS_TYPE(MouseButtonRepeatEvent);
};

class MouseMoveEvent : public Event{
public:
    MouseMoveEvent(glm::vec2 pos) : mMousePos(pos){};
    EVENT_CLASS_TYPE(MouseMoveEvent);

    glm::vec2 getMousePosition() const {return mMousePos;};
private:
    const glm::vec2 mMousePos;
};

class MouseScrollEvent : public Event{
public:
    MouseScrollEvent(glm::vec2 delta) : mDelta(delta){};
    EVENT_CLASS_TYPE(MouseScrollEvent);

    glm::vec2 getScrollDelta() const {return mDelta;};

protected:
    const glm::vec2 mDelta;

};