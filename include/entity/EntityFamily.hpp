#pragma once

#include <Entity.hpp>

class EntityFamily
{
public:
    virtual bool isInFamily(const Entity &entity) const = 0;
};