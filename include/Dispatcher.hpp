#pragma once

#include <Event.hpp>

#include <functional>
#include <map>
#include <string>
#include <vector>

/**
 * @brief A class for managing events.
 *
 * The Dispatcher is the main class of the event system. Publishers use the Dispatcher to post their events and subscribers use
 * the Dispatcher to receive their events.
 *
 */
class Dispatcher
{
public:
    /**
     * @brief Construct a new Dispatcher object
     *
     */
    Dispatcher() = default;

    /**
     * @brief Subscribe a specific listener to a specific event type.
     *
     * @param type The string identifying the type of event. This is idiomatically declared as a static member in the class that produces
     * the event.
     * @param observer The function to be invoked when the event is dispatched. It is assumed this function's lifetime will be at least as long
     * as that of the dispatcher.
     */
    void subscribe(const std::string type, const std::function<void(const Event &)> &observer);

    /**
     * @brief Dispatches an event
     *
     * Dispatches the provided event to all subscribed observers. All observer that subscribed to event.getType() will be invoked in the same
     * order that they subscribed.
     *
     * @param event The event to dispatch
     */
    void dispatch(const Event &event);

private:
    std::map<std::string, std::vector<std::function<void(const Event &)>>> _observers;
};