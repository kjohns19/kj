#include <kj/event_handler.hpp>

namespace kj {

EventHandler::EventHandler() {}
EventHandler::EventHandler(std::shared_ptr<EventHandler> next)
: d_next(next) {}

void EventHandler::handle(const sf::Event& event)
{
    if (!doHandle(event) && d_next)
        d_next->handle(event);
}

} // close namespace frac
