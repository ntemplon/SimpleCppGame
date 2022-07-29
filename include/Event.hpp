#pragma once

#include <string>

/**
 * @brief A class representing an event that has occurred
 *
 */
class Event
{
public:
    /**
     * @brief Construct a new Event object
     *
     * Constructs a new event of the specified type.
     *
     * @param type The type of the event, typically declared as a static member of the class creating the event.
     */
    Event(std::string type);

    /**
     * @brief Get the Type of the event
     *
     * @return The std::string indicating what type of event is being provided.
     */
    std::string getType() const;

private:
    std::string _type;
};