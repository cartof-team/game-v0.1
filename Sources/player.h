#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "VarsAndWindow.h"

sf::CircleShape pl(1);
class Player
{
public:

    void init(int Size,sf::Color clr)
    {
        pl.setRadius(Size/2);
        pl.setOrigin(Size/2,Size/2);
        pl.setFillColor(clr);
    }
    void MovePlayer(sf::Vector2f Poz)
    {
        pl.setPosition(Poz);
    }
    void Update()
    {
        window.draw(pl);
    }
};

#endif // PLAYER_H_INCLUDED
