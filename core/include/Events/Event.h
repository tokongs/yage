#pragma once

#include <string>

enum class EventType {
    None = 0,
    KeyPressEvent, KeyReleaseEvent, KeyRepeatEvent,
    MouseMoveEvent, MouseButtonPressEvent, MouseButtonReleaseEvent, MouseButtonRepeatEvent, MouseScrollEvent
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type;}\
                                virtual EventType getEventType() const override {return GetStaticType(); }\
                                virtual const char* getName() const override { return #type; }

class Event {

public:
    Event(){};
    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0;
    virtual std::string toString() const {return getName(); }
protected:
    bool mHandled = false;
};