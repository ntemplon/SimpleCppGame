#pragma once

#include <string>
#include <map>
#include <memory>

class Entity
{
public:
    class Component
    {
    public:
        Component(const std::string id);
        virtual ~Component();
        const std::string getId() const;

    private:
        const std::string _id;
    };

    Entity();
    Entity(int id);
    int getId() const;
    void add(const std::shared_ptr<Component> &component);
    bool hasComponent(const std::string id) const;
    std::shared_ptr<Component> getComponent(const std::string id) const;

private:
    int _id;
    std::map<std::string, std::shared_ptr<Component>> _components;
};