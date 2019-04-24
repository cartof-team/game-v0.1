#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "util.h"
#include "rooms.h"
#include "Application.h"

int Size=100;
int WindowX=800;
int WindowY=600;
int pX,pY;
int lT;

int drx[4]= {0,1,0,-1};
int dry[4]= {1,0,-1,0};

int connected[100][4];
int con=0;
int ok;

sf::CircleShape Truth(1);
sf::CircleShape pl(1);

sf::RenderWindow window(sf::VideoMode(WindowX,WindowY),"Step 3 - advanced collisions and teleportation");
class Tile
{
public:
    Tile()
    {
        type=0;
        X=0;
        Y=0;
        room=0;
        conected=false;
    }

    int type;
    int X,Y;
    int room;
    bool conected;
    void SetConected(int x,int y)
    {

        connected[con][0]=X;
        connected[con][1]=Y;
        connected[con][2]=x;
        connected[con][3]=y;
        conected=true;
        con++;
    }
    void SetPosition(int x,int y)
    {
        X=x;
        Y=y;
    }
    void SetType(int tp)
    {
        type=tp;
    }

};

std::array <Tile,10000> TheMap;

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
class Map
{
public:
    Map()
    {
        int i,j;
        for(i=0;i<Size;i++)
        {
            for(j=0;j<Size;j++)
            {
                TheMap[i+j*Size].SetPosition(i,j);
            }
        }
    }

    int ch,chX,chY;
    void NewRoom()
    {
        int h,w,ok=0;
        ch=random(1,6);
        if(ch<=3)
        {
            h=6;
            w=6;
        }
        else
        {
            h=9;
            w=9;
        }
        for(int g=0; g<100&&ok==0; g++)
        {
            chX=random(2,99-w-2);
            chY=random(2,99-h-2);
            ok=1;
            for(i=chX-2; i<=chX+w+2; i++)
            {
                for(j=chY-2; j<=chY+h+2; j++)
                {
                    if(TheMap[i+j*Size].type!=0)
                        ok=0;
                }
            }
        }
        if(ok==1)
        {
            for(i=chX; i<chX+w; i++)
            {
                for(j=chY; j<chY+h; j++)
                {
                    switch(ch)
                    {
                    case 1:
                        TheMap[i+j*Size].type=Room1[i-chX][j-chY];
                        break;
                    case 2:
                        TheMap[i+j*Size].type=Room2[i-chX][j-chY];
                        break;
                    case 3:
                        TheMap[i+j*Size].type=Room3[i-chX][j-chY];
                        break;
                    case 4:
                        TheMap[i+j*Size].type=Room4[i-chX][j-chY];
                        break;
                    case 5:
                        TheMap[i+j*Size].type=Room5[i-chX][j-chY];
                        break;
                    case 6:
                        TheMap[i+j*Size].type=Room6[i-chX][j-chY];
                        break;
                    }
                    TheMap[i+j*Size].room=y;
                }
            }
        }
    }
    void MakeTunnels(int sX,int sY,int fX,int fY)
    {
        int currFloor=TheMap[sX+sY*Size].room,oldFloor=-1;
        int mn,ok;
        int tx=sX,ty=sY,dx,dy;
        int msx,msy,mfx,mfy;
        while(currFloor!=TheMap[fX+fY*Size].room&&currFloor>0)
        {
            mn=-1;
            ok=1;
            for(i=1; i<Size; i++)
            {
                for(j=0; j<Size; j++)
                {
                    if(TheMap[i+j*Size].room==currFloor&&TheMap[i+j*Size].room!=0&&TheMap[i+j*Size].conected==false)
                    {
                        if((mn>getDis(i,j,fX,fY)||mn==-1)&&TheMap[i+j*Size].type>=3&&TheMap[i+j*Size].type<=6)
                        {
                            tx=i;
                            ty=j;
                            mn=getDis(i,j,fX,fY);
                        }
                    }
                }
            }
            mn=-1;

            switch (TheMap[tx+ty*Size].type)
            {
            case 3:
                msx=0;
                msy=0;
                mfx=tx;
                mfy=Size;
                break;
            case 5:
                msx=tx+1;
                msy=0;
                mfx=Size;
                mfy=Size;
                break;
            case 4:
                msx=0;
                msy=ty+1;
                mfx=Size;
                mfy=Size;
                break;
            case 6:
                msx=0;
                msy=0;
                mfx=Size;
                mfy=ty;
                break;
            }
            for(i=msx; i<mfx; i++)
            {
                for(j=msy; j<mfy; j++)
                {
                    if(TheMap[i+j*Size].room!=currFloor&&TheMap[i+j*Size].room!=oldFloor&&TheMap[i+j*Size].room!=0&&TheMap[i+j*Size].conected==false)
                    {
                        if((mn>getDis(i,j,tx,ty)||mn==-1)&&TheMap[i+j*Size].type>2&&TheMap[i+j*Size].type<7)
                        {
                            dx=i;
                            dy=j;
                            mn=getDis(i,j,tx,ty);
                        }
                    }
                }
            }
            TheMap[tx+ty*Size].SetConected(dx,dy);
            TheMap[dx+dy*Size].conected=true;
            for(i=0;i<Size;i++)
            {
                for(j=0;j<Size;j++)
                {
                    if (TheMap[i+j*Size].room==currFloor)
                        TheMap[i+j*Size].room*=-1;
                }
            }
            tx=dx;
            ty=dy;
            oldFloor=currFloor*-1;
            currFloor=TheMap[tx+ty*Size].room;
        }
    }
    void Randomize()
    {
        for(i=0; i<Size; i++)
            for(j=0; j<Size; j++)
                TheMap[i+j*Size].type=0;
        int dX,dY; //digger positions and finish positions
        chX=random(0,93);
        chY=random(0,93);
        for(j=0; j<5; j++)
            for(i=0; i<5; i++)
            {

               TheMap[i+chX+(j+chY)*Size].type=StartRoom[i][j];

                 TheMap[i+chX+(j+chY)*Size].room=1;

                if(StartRoom[i][j]==9)
                {
                    pX=i+chX;
                    pY=j+chY;
                }

            }
        chX=random(0,93);
        chY=random(0,93);
        while(getDis(pX,pY,chX+2,chY+2)<Size/2) //makes sure that the start and end are far enough
        {
            chX=random(0,93);
            chY=random(0,93);
        }
        for(j=0; j<5; j++)
            for(i=0; i<5; i++)
            {
                TheMap[i+chX+(j+chY)*Size].type=EndRoom[i][j];
                 TheMap[i+chX+(j+chY)*Size].room=2;
                if(EndRoom[i][j]==8)
                {
                    dX=i+chX; //the digger starts here
                    dY=j+chY;
                }
            }
        for(y=3; y<1003; y++)
            NewRoom();
        MakeTunnels(dX,dY,pX,pY);
        int ro1X,ro1Y,ro2X,ro2Y;
        ro1X=random(0,99);
        ro1Y=random(0,99);
        while(TheMap[ro1X+ro1Y*Size].room<=0)
        {
            ro1X=random(0,99);
            ro1Y=random(0,99);
        }
        ro2X=random(0,99);
        ro2Y=random(0,99);
        while(TheMap[ro2X+ro2Y*Size].room<=0)
        {
            ro2X=random(0,99);
            ro2Y=random(0,99);
        }
        MakeTunnels(ro1X,ro1Y,pX,pY);
        MakeTunnels(ro2X,ro2Y,pX,pY);
    }
private:
    int i,j,y;
};
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
    float cmX,cmY;
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
