#pragma once

#include <Event.hpp>
#include <functional>
#include <map>
#include <string>
#include <vector>

class Dispatcher
{
public:
    Dispatcher() = default;
    void subscribe(std::string type, const std::function<void(const Event &)> &observer);
    void post(Event &event);

private:
    std::map<std::string, std::vector<std::function<void(const Event &)>>> _observers;
};