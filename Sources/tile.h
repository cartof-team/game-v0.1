#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

int connected[100][4];
int con=0;

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

#endif // TILE_H_INCLUDED
