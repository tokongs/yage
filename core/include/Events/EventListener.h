#pragma once
#include <memory>
#include "Event.h"

class EventListener {

public:
    virtual void handleEvent(Event* event) = 0;
};