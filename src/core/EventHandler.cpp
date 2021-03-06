#include "EventHandler.h"

namespace Vulture2D {
    int EventHandler::addListener(EventType type, Callback cb) {
        Listener listener;
        listener.type = type;
        listener.cb = cb;
        listener.id = lastID++;

        listeners.push_back(listener);

        return lastID;
    }

    void EventHandler::removeListener(int id) {
        for (size_t i = 0; i < listeners.size(); i++) {
            if (listeners.at(i).id == id) {
                listeners.erase(listeners.begin() + i);
            }
        }
    }

    void EventHandler::dispatchEvent(Event* event) {
        for (int i = 0; i < listeners.size(); i++) {
            if (listeners.at(i).type == event->getType())
                if(listeners.at(i).cb)
                    listeners.at(i).cb(event);
        }
    }
}
