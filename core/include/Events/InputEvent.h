#pragma once
#include "Event.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class KeyEvent : public Event {
public:
    KeyEvent(int key_code) : m_key_code(key_code){};

    int getKeyCode() const { return m_key_code;};
protected:
    const int m_key_code;
};

class KeyPressEvent : public KeyEvent {
public:
    KeyPressEvent(int key_code) : KeyEvent(key_code){};
    EVENT_CLASS_TYPE(KeyPressEvent);
};

class KeyReleaseEvent : public KeyEvent {
public:
    KeyReleaseEvent(int key_code) : KeyEvent(key_code){};
    EVENT_CLASS_TYPE(KeyReleaseEvent);
};

class KeyRepeatEvent : public KeyEvent {
public:
    KeyRepeatEvent(int key_code) : KeyEvent(key_code){};
    EVENT_CLASS_TYPE(KeyRepeatEvent);
};

class MouseButtonEvent : public Event{
public:
    MouseButtonEvent(int button) : m_button(button){};

    int getButton() const { return m_button;};

protected:
    const int m_button;
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
    MouseMoveEvent(glm::vec2 pos) : m_mouse_pos(pos){};
    EVENT_CLASS_TYPE(MouseMoveEvent);

    glm::vec2 getMousePosition() const {return m_mouse_pos;};
private:
    const glm::vec2 m_mouse_pos;
};

class MouseScrollEvent : public Event{
public:
    MouseScrollEvent(glm::vec2 delta) : m_delta(delta){};
    EVENT_CLASS_TYPE(MouseScrollEvent);

    glm::vec2 getScrollDelta() const {return m_delta;};

protected:
    const glm::vec2 m_delta;

};