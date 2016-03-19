#ifndef INCLUDED_SFML_WIDGET_HPP
#define INCLUDED_SFML_WIDGET_HPP

#include <kj/gtkmm_no_warning.hpp>

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <sigc++/connection.h>

#include <functional>

namespace kj {

class SFMLWidget : public Gtk::Widget
{
public:
    typedef std::function<void(SFMLWidget&)> DrawFunc;
    typedef std::function<void(sf::Event)> EventFunc;
protected:
    sf::VideoMode d_vMode;

    virtual void on_size_allocate(Gtk::Allocation& allocation);
    virtual void on_realize();
    virtual void on_unrealize();

    Glib::RefPtr<Gdk::Window> d_refGdkWindow;
public:
    SFMLWidget(sf::VideoMode mode, int size_request=-1);
    virtual ~SFMLWidget() {}

    void invalidate();
    void display();

    void onDraw(const DrawFunc& func);
    void onEvent(const EventFunc& func);

    sf::RenderWindow& window() { return d_renderWindow; }
    const sf::RenderWindow& window() const { return d_renderWindow; }

    void setFramerate(int framerate);

private:
    void doDraw();
    void doEvent();

    bool eventButton(GdkEventButton* ev);
    bool eventMotion(GdkEventMotion* ev);
    bool eventCrossing(GdkEventCrossing* ev);


    sf::RenderWindow d_renderWindow;
    DrawFunc d_drawFunc;
    EventFunc d_eventFunc;
    sigc::connection d_updateSignal;
};

}

#endif // INCLUDED_SFML_WIDGET_HPP
