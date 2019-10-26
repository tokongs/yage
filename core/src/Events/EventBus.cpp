#include "Events/EventBus.h"

EventBus::EventBus() {

}
EventBus::~EventBus() {
    while(!mEventQueue.empty()){
        Event *event = mEventQueue.front();
        mEventQueue.pop();
        delete event;
    }
}
void EventBus::publish(Event* event) {
    mEventQueue.push(event);
}
void EventBus::subscribe(EventListener* listener, EventType type) {
    mListeners[type].push_back(listener);
}


void EventBus::handleEvents() {
    while(!mEventQueue.empty()){
        Event *event = mEventQueue.front();

        ListenerList listeners = mListeners[event->getEventType()];
        for(auto it : listeners){
            it->handleEvent(event);
        }
        mEventQueue.pop();
        delete event;
    }
}


