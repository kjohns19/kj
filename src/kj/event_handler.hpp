#ifndef INCLUDED_KJ_EVENT_HANDLER
#define INCLUDED_KJ_EVENT_HANDLER

#include <memory>

namespace sf {

class Event;

} // close namespace sf

namespace kj {

class EventHandler
{
public:
    EventHandler();
    EventHandler(std::shared_ptr<EventHandler> next);

    virtual ~EventHandler() {}

    void handle(const sf::Event& event);

private:
    virtual bool doHandle(const sf::Event& event) = 0;

    std::shared_ptr<EventHandler> d_next;
};

} // close namespace kj

#endif //INCLUDED_KJ_EVENT_HANDLER
