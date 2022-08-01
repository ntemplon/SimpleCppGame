#include <Dispatcher.hpp>

#include <iostream>

void Dispatcher::subscribe(const std::string type, const std::function<void(const Event &)> &observer)
{
    // Push to back so the call order matches subscriber order
    _observers[type].push_back(observer);
}

void Dispatcher::dispatch(const Event &event)
{
    if (_observers.find(event.getType()) == _observers.end())
    {
        // Case - there are no observers subscribed to the event, so do nothing
        return;
    }
    else
    {
        // Case - one or more observers has subscribed to this event
        // Iterate through all of them and invoke each one in order
        for (std::function<void(const Event &)> &observer : _observers.at(event.getType()))
        {
            observer(event);
        }
    }
}