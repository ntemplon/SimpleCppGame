#pragma once

#include <string>

class Event
{
public:
    std::string getId() const;

private:
    std::string _id;
};