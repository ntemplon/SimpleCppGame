#pragma once

#include <string>

class Event
{
public:
    Event(std::string type);
    virtual ~Event(){};
    std::string getType() const;

private:
    std::string _type;
};