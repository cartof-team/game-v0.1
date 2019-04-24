#include "Application.h"

Application::Application()
{
app_window.create(sf::VideoMode(WindowX,WindowY), "The Game");
rect.setSize(sf::Vector2f(40,50));
rect.setFillColor(sf::Color::Blue);
}

Application::~Application()
{
    //dtor
}

void Application::MainLoop()
{
    while (app_window.isOpen())
    {
        sf::Event event;
        while (app_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GameState=0;
        }
        if(GameState==0)
            app_window.close();
        app_window.clear(sf::Color::Black);
        renderAllObjs();
        app_window.display();
    }
}


void Application::render(sf::RenderTarget& window, sf::RectangleShape Shape)
{
    window.draw(Shape);
}

void Application::render(sf::RenderTarget& window, sf::CircleShape Shape)
{
    window.draw(Shape);
}

void Application::render(sf::RenderTarget& window, sf::Sprite Shape)
{
    window.draw(Shape);
}

void Application::render(sf::RenderTarget& window, sf::ConvexShape Shape)
{
    window.draw(Shape);
}

void Application::renderAllObjs()
{
    render(app_window, rect);
}

sf::RectangleShape& Application::getRectangle()
{
    return rect;
}
