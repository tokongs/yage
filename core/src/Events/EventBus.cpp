#include "Events/EventBus.h"

EventBus::EventBus() {

}
EventBus::~EventBus() {
    while(!m_event_queue.empty()){
        Event *event = m_event_queue.front();
        m_event_queue.pop();
        delete event;
    }
}
void EventBus::publish(Event* event) {
    m_event_queue.push(event);
}
void EventBus::subscribe(EventListener* listener, EventType type) {
    m_listeners[type].push_back(listener);
}


void EventBus::handleEvents() {
    while(!m_event_queue.empty()){
        Event *event = m_event_queue.front();

        ListenerList listeners = m_listeners[event->getEventType()];
        for(auto it : listeners){
            it->handleEvent(event);
        }
        m_event_queue.pop();
        delete event;
    }
}


