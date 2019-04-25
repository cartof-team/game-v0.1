#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "util.h"
#include "rooms.h"
#include "tile.h"
#include "player.h"
#include "map.h"
#include "sistem.h"
#include "VarsAndWindow.h"

int main()
{
    window.setFramerateLimit(1000);
    Map m;

    Sistem s;

    sf::Clock c;
    c.restart();

    sf::Event e;
    srand(time(0));

    m.Randomize();
    s.initShow();
    while(window.isOpen())
    {
        while(window.pollEvent(e))
        {
            if(e.type==sf::Event::Closed)
                window.close();
        }
        if(c.getElapsedTime().asSeconds()>1)
        {
            c.restart();
        }
        window.clear();
        s.update();
        window.display();
    }
    return 0;
}
