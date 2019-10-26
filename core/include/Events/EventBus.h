#pragma once

#include <unordered_map>
#include <list>
#include <queue>
#include <typeindex>
#include <boost/shared_ptr.hpp>
#include "Event.h"
#include "EventListener.h"

typedef std::list<EventListener*> ListenerList;
class EventBus {
public:
    EventBus();
    ~EventBus();

    void publish(Event* event);
    void subscribe(EventListener* listener, EventType type);
    void handleEvents();

private:
    std::unordered_map<EventType, ListenerList> mListeners;
    std::queue<Event*> mEventQueue;
};