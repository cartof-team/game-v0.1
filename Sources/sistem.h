#ifndef SISTEM_H_INCLUDED
#define SISTEM_H_INCLUDED

#include "player.h"
#include "map.h"
#include "VarsAndWindow.h"

class Sistem
{
public:
    Sistem()
    {
        timer.restart();

        p.init(tileSize/2,sf::Color(0,255,255));
        p.MovePlayer(sf::Vector2f(WindowX/2,WindowY/2));
    }
    float getDeltaTime()
    {
        return DeltaTime;
    }
    void update()
    {
        CameraUpdate();
        Show();
        p.Update();
        DeltaTime=timer.restart().asSeconds();
    }
    void initShow()
    {
        cameraX=-pX*tileSize+WindowX/2;
        cameraY=-pY*tileSize+WindowY/2;
        Truth.setOrigin(tileSize/2,tileSize/2);
    }
private:
    Player p;
    const int tileSize=50;
    const int sac=2;
    const int smx=100;
    float angle=-255,T;
    float cameraX,
          cameraY;
    float cmX=0,cmY=0;
    sf::Clock timer;
    sf::Text conn;
    float ocX,ocY;
    int port=0;
    float DeltaTime;
    sf::Vertex a;
    sf::Vertex b;
    int moved;

    int CheckCol()
    {
        int ok=1;
        /*if(WindowX/2+tileSize/4>=Truth.getPosition().x+tileSize/2&&WindowX/2-tileSize/4<=Truth.getPosition().x+tileSize/2)
            ok=0;
        if(WindowX/2-tileSize/4<=Truth.getPosition().x-tileSize/2&&WindowX/2+tileSize/4>=Truth.getPosition().x-tileSize/2)
            ok=0;
        if(WindowY/2+tileSize/4>=Truth.getPosition().y+tileSize/2&&WindowY/2-tileSize/4<=Truth.getPosition().y+tileSize/2)
            ok=0;
        if(WindowY/2-tileSize/4<=Truth.getPosition().y-tileSize/2&&WindowY/2+tileSize/4>=Truth.getPosition().y-tileSize/2)
            ok=0;*/ //send help
        if(getDis(WindowX/2,WindowY/2,Truth.getPosition().x,Truth.getPosition().y)<tileSize*0.75)
            ok=0;
        return ok;
    }
    void Show()
    {
        int i,j;
        if(angle==-255)
        for(i=0;i<Size;i++)
            for(j=0;j<Size;j++)
            {
                Truth.setPosition(i*tileSize+cameraX,j*tileSize+cameraY);
                if(CheckCol()==0&&TheMap[i+j*Size].type>=2&&TheMap[i+j*Size].type<=6&&TheMap[i+j*Size].conected==false)
                {

                    if(WindowX/2+tileSize/2>=Truth.getPosition().x-tileSize/2&&WindowX/2-tileSize/2<=Truth.getPosition().x-tileSize/2)
                        cmX=15*DeltaTime;
                    if(WindowX/2-tileSize/2<=Truth.getPosition().x+tileSize/2&&WindowX/2+tileSize/2>=Truth.getPosition().x+tileSize/2)
                        cmX=-15*DeltaTime;
                    if(WindowY/2+tileSize/2>=Truth.getPosition().y-tileSize/2&&WindowY/2-tileSize/2<=Truth.getPosition().y-tileSize/2)
                        cmY=15*DeltaTime;
                    if(WindowY/2-tileSize/2<=Truth.getPosition().y+tileSize/2&&WindowY/2+tileSize/2>=Truth.getPosition().y+tileSize/2)
                        cmY=-15*DeltaTime;
                }
                if(CheckCol()==0&&ok==1&&TheMap[i+j*Size].type==1)
                    lT=-1;
            }
        for(i=0;i<Size;i++)
        {
            for(j=0;j<Size;j++)
            {
            if(i*tileSize+cameraX>-tileSize/2&&i*tileSize+cameraX<WindowX+tileSize/2&&j*tileSize+cameraY>-tileSize/2&&j*tileSize+cameraY<WindowY+tileSize/2)
            {
             if(TheMap[i+j*Size].type==0)
                    Truth.setFillColor(sf::Color::Black);
                if(TheMap[i+j*Size].type==1)
                    Truth.setFillColor(sf::Color::Black);
                if(TheMap[i+j*Size].type>=2)
                    Truth.setFillColor(sf::Color(0,255,255));
                if(TheMap[i+j*Size].type==7)
                    Truth.setFillColor(sf::Color(155,155,155));
                if(TheMap[i+j*Size].type==9)
                    Truth.setFillColor(sf::Color::Blue);
                if(TheMap[i+j*Size].type==8)
                    Truth.setFillColor(sf::Color::Red);
                if(TheMap[i+j*Size].conected==true)
                    {
                        srand(TheMap[i+j*Size].conected);
                        Truth.setFillColor(sf::Color(random(0,255),random(0,255),random(0,255)));
                    }

                Truth.setPosition(i*tileSize+cameraX,j*tileSize+cameraY);

                Truth.setRadius(tileSize/2);
                window.draw(Truth);
            }
            }
        }
        ok=1;
        for(i=0;i<con;i++)
        {
                if((
                    connected[i][0]*tileSize+cameraX>-tileSize/2&&
                    connected[i][0]*tileSize+cameraX<WindowY+tileSize/2&&
                    connected[i][1]*tileSize+cameraY>-tileSize/2&&
                    connected[i][1]*tileSize+cameraY<WindowX+tileSize/2)||
                    (
                    connected[i][2]*tileSize+cameraX>-tileSize/2&&
                    connected[i][2]*tileSize+cameraX<WindowY+tileSize/2&&
                    connected[i][3]*tileSize+cameraY>-tileSize/2&&
                    connected[i][3]*tileSize+cameraY<WindowX+tileSize/2
                     ))
                {
                    a.position = sf::Vector2f(connected[i][0]*tileSize+cameraX,connected[i][1]*tileSize+cameraY);
                                    b.position = sf::Vector2f(connected[i][2]*tileSize+cameraX,connected[i][3]*tileSize+cameraY);
                    srand(TheMap[i+j*Size].conected);
                    a.color = sf::Color(random(0,255),random(0,255),random(0,255));
                    srand(TheMap[i+j*Size].conected);
                    b.color = sf::Color(random(0,255),random(0,255),random(0,255));
                        Truth.setPosition(connected[i][0]*tileSize+cameraX,connected[i][1]*tileSize+cameraY);
                        if(getDis(WindowX/2,WindowY/2,Truth.getPosition().x,Truth.getPosition().y)<tileSize/3)
                        {
                            ok=0;
                            if(lT==i&&T==2)
                            {
                                if(getDis(WindowX/2,WindowY/2,Truth.getPosition().x,Truth.getPosition().y)<tileSize/10)
                                angle=-255;
                            }
                            else
                            {

                            if(lT!=i)
                            {cameraX=-connected[i][0]*tileSize+WindowX/2;
                            cameraY=-connected[i][1]*tileSize+WindowY/2;}
                            lT=i;
                            T=1;
                            angle=atan2(connected[i][1]-connected[i][3],connected[i][0]-connected[i][2]);
                            }
                        }
                        else
                        {
                            Truth.setPosition(connected[i][2]*tileSize+cameraX,connected[i][3]*tileSize+cameraY);
                             if(getDis(WindowX/2,WindowY/2,Truth.getPosition().x,Truth.getPosition().y)<tileSize/3)
                            {
                                ok=0;
                                if(lT==i&&T==1)
                                {
                                    if(getDis(WindowX/2,WindowY/2,Truth.getPosition().x,Truth.getPosition().y)<tileSize/10)
                                    angle=-255;
                                }
                                else
                                {
                                if(lT!=i)
                                {cameraX=-connected[i][2]*tileSize+WindowX/2;
                                cameraY=-connected[i][3]*tileSize+WindowY/2;}
                                lT=i;
                                T=2;
                                angle=atan2(connected[i][3]-connected[i][1],connected[i][2]-connected[i][0]);
                                }
                            }
                        }
                    sf::Vertex c[]=
                    {
                        a,b
                    };
                    window.draw(c,2,sf::Lines);
                }
        }
        ocY=cameraY;
        ocX=cameraX;
    }
    void CameraUpdate()
    {
        if(angle<=-255)
        {
        moved=0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            cmY-=sac*DeltaTime;
            moved=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            cmY+=sac*DeltaTime;
            moved=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            cmX+=sac*DeltaTime;
            moved=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            cmX-=sac*DeltaTime;
            moved=1;
        }
        if(moved==0)
        {
            cmY*=0.99;
            cmX*=0.99;
        }
        cameraX+=cmX;
        cameraY+=cmY;
        }
        if(angle>-255)
        {
            cameraX+=cos(angle)*getDis(connected[lT][0],connected[lT][1],connected[lT][2],connected[lT][3])*tileSize*DeltaTime;
            cameraY+=sin(angle)*getDis(connected[lT][0],connected[lT][1],connected[lT][2],connected[lT][3])*tileSize*DeltaTime;
            if(T==1)
            {
                switch(TheMap[connected[lT][2]+connected[lT][3]*Size].type)
                {
                case 3:
                    cmX=-tileSize*10*DeltaTime;
                    cmY=0;
                    break;
                case 5:
                    cmX=tileSize*10*DeltaTime;
                    cmY=0;
                    break;
                case 6:
                    cmX=0;
                    cmY=-tileSize*10*DeltaTime;
                    break;
                case 4:
                    cmX=0;
                    cmY=tileSize*10*DeltaTime;
                    break;
                }
            }
            else
            {
                switch(TheMap[connected[lT][0]+connected[lT][1]*Size].type)
                {
                case 3:
                    cmX=-tileSize*10*DeltaTime;
                    cmY=0;
                    break;
                case 5:
                    cmX=tileSize*10*DeltaTime;
                    cmY=0;
                    break;
                case 6:
                    cmX=0;
                    cmY=-tileSize*10*DeltaTime;
                    break;
                case 4:
                    cmX=0;
                    cmY=tileSize*10*DeltaTime;
                    break;
                }
            }

        }
    }

};

#endif // SISTEM_H_INCLUDED
