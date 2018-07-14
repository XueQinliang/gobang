#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <boardwindow.h>
class state{
public:state(int x,int y,int color,Board board){
        board.set(x,y,color);
        this->board=board;
        this->x=x;
        this->y=y;
        this->color=color;
    }
protected:Board board;
    int x,y,color;

};

#endif // STATE_H
