#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
this->imageCount = imageCount;
this->switchTime = switchTime;

uvRect.width = texture->getSize().x/float(imageCount.x);
uvRect.height = texture->getSize().y/float(imageCount.y);

currentImage.x=0;
totalTime=0.0f;
}

Animation::~Animation()
{
    //dtor
}

void Animation::Update(int row, float deltaTime)
{
    currentImage.y = row;
    totalTime += deltaTime;
    if(totalTime>=switchTime)
    {
        totalTime-=switchTime;
        currentImage.x++;

        if(currentImage.x>=imageCount.x)
            currentImage.x=1;
    }

    uvRect.left = currentImage.x *uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
}
