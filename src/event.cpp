#include <Event.hpp>

Event::Event(std::string type) : _type(type) {}

std::string Event::getType() const
{
    return this->_type;
}