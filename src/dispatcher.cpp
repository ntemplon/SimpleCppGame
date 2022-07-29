#include <Dispatcher.hpp>

void Dispatcher::subscribe(std::string type, const std::function<void(const Event &)> &observer)
{
    _observers[type].push_back(observer);
}

void Dispatcher::post(Event &event)
{
    if (_observers.find(event.getType()) == _observers.end())
    {
        return;
    }
    else
    {
        for (std::function<void(const Event &)> &observer : _observers[event.getType()])
        {
            observer(event);
        }
    }
}