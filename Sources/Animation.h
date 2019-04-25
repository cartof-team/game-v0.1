#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <SFML/Graphics.hpp>
class Animation
{
    public:
        Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        virtual ~Animation();
        sf::IntRect uvRect;
        void Update(int row, float deltaTime);
    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;
        float totalTime;
        float switchTime;

};

#endif // ANIMATION_H

/*
cand faci o animatie creezi un object nou pt fiecare animatie, cu textura, (vector2u)numarul de coloane si linii ale animatie si timpul
in secunde intre animatii (de preferat 0.3 sau 0.1)
ex: Animation anim1(&AnimTXT1, sf::Vector2u(10,4), 0.1);

dupa folosesti functia Update ca sa treaca la urmatorul frame. Ca parametrii setezi coloana si deltaTime-ul
ex: anim1.Update(0, deltaTime);
//0 pt prima linie
  1 pt a doua etcc
*/
