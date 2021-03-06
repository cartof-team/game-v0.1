#ifndef APPLICATION_H
#define APPLICATION_H
#include <SFML/Graphics.hpp>
#include <iostream>
class Application
{
    public:
        Application();
        ~Application();
        void MainLoop();
        sf::RenderTarget& getMainWindow();
        sf::RectangleShape& getRectangle();
    private:
        //render handlers
        void renderAllObjs();
        void render(sf::RenderTarget& window, sf::RectangleShape Shape);
        void render(sf::RenderTarget& window, sf::CircleShape Shape);
        void render(sf::RenderTarget& window, sf::ConvexShape Shape);
        void render(sf::RenderTarget& window, sf::Sprite Shape);
        //
        int WindowX=800, WindowY=600;
        sf::RenderWindow app_window;
        sf::RectangleShape rect;
        int GameState=1;
};

#endif // APPLICATION_H
