#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "tile.h"
#include "VarsAndWindow.h"

std::array <Tile,10000> TheMap;

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
        int mn;
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
#endif // MAP_H_INCLUDED
