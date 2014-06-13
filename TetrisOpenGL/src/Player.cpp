#include "Player.h"

Player::Player(){
    isTurnOver=false;
}

Player::~Player(){

}

string Player::play(Board ghost, Board solid){
    int current = getCurrentRow(ghost);
    int target = getBestRow(solid);
    int move = target - current;
    if(move>0)
    {
        return "left";
    }
    else if(move<0)
    {
         return "right";
    }
}

int Player::getBestRow(Board solid){
    int rows[solid.getWidth()];
    for(int i=0;i<solid.getWidth();i++)
        rows[i]=0;


    for(int i=0;i<solid.getHeight();i++){
        for(int j=0;j<solid.getWidth();j++){
            rows[j]+=getByte(j,solid.getFloor(i));
        }
    }
    int best = 10000;
    int nbbest;
    for(int i=0;i<solid.getWidth();i++){
        if(rows[i]<best){
            best = rows[i];
            nbbest=i;
        }
    }
    return nbbest;
}

int Player::getByte(int byte, int nb){
    if((2 << byte)&nb)
        return 1;
    else
        return 0;
}

int Player::getCurrentRow(Board ghost){
    int biggestLine = 0;
    int sizeLine = 0;
    for(int i=0;i<ghost.getHeight();i++){
        if(getLineSize(ghost.getFloor(i),ghost.getWidth())>sizeLine){
            sizeLine=getLineSize(ghost.getFloor(i),ghost.getWidth());
            biggestLine=i;
        }
    }
    return biggestLine;
}

int Player::getLineSize(int l, int max){
    int sum=0;
    for(int i=0;i<max;i++){
        sum+=getByte(i,l);
    }
    return sum;
}
