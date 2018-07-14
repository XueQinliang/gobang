//by liang_jk
#include<boardwindow.h>
#include<iostream>
#include <string.h>
/*
 * You need to complete this function.
 *
 * The first parameter you've got describes a board,
 * you can use "at(x,y)" to know whether there is a stone at (x,y) and what color it is.
 *
 * You can use "board_size" as a const number. Actually it has been defined as 19.
 *
 * If it returns 0, it means there is a stone belongs to you.
 * If it returns 1, it means there is a stone belongs to the player.
 * If it returns -1, it means there is no stone.
 * If it returns -2, it means the position is invalid.
 *
 * After you decide where to put your stone, please use "make_move" function.
 * Use it like this "Game->make_move(x,y)" if you decide to put your stone at (x,y).
 *
 * The coordinates begin from 0.
 * Make sure the coordinate you give is valid, or the application will crash!!!
 *
 * Here is a example for you with a random algorithm.
*/

// Include headers you need here.
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;
bool isdanger(const Board &board, int x, int y);
bool isattack(const Board &board, int x, int y){
    int isDanger=0;
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){
            if(isdanger(board,i,j)==true)
                isDanger=1;
        }
    }
    if(isDanger==1)
        return false;
    else if(isDanger==0){
        int dx[4]={1,1,0,1};
        int dy[4]={0,-1,1,1};
        if(board.at(x,y)==-1){
            for(int i=0;i<4;i++){
                cout<<i<<endl;
                char set[12];
                int kk=0;
                for(int k=-5;k<=5;k++){//从一个点周围五个点开始搜
                    if(board.at(x+k*dx[i],y+k*dy[i])==1){
                        set[kk]='1';
                    }else if(board.at(x+k*dx[i],y+k*dy[i])==-1){
                        set[kk]='*';
                    }else if(board.at(x+k*dx[i],y+k*dy[i])==0){
                        set[kk]='0';
                    }
                    if(k==0)set[kk]='&';
                    kk++;
                }
                set[11]='\0';
                if(strstr(set,"*000&")!=NULL||strstr(set,"&000*")!=NULL||strstr(set,"&00001")!=NULL||strstr(set,"10000&")!=NULL
                 ||strstr(set,"*00&0*")!=NULL||strstr(set,"*0&00*")!=NULL||strstr(set,"00&00")!=NULL||strstr(set,"&0000")!=NULL||strstr(set,"1111&")!=NULL){
                    return true;
                }
            }
            return false;
        }
    }
}

bool isdanger(const Board &board, int x, int y){
    int dx[4]={1,1,0,1};
    int dy[4]={0,-1,1,1};
    if(board.at(x,y)==-1){
        for(int i=0;i<4;i++){
            char set[12];
            int kk=0;
            for(int k=-5;k<=5;k++){
                if(board.at(x+k*dx[i],y+k*dy[i])==1){
                    set[kk]='1';
                }else if(board.at(x+k*dx[i],y+k*dy[i])==-1){
                    set[kk]='*';
                }else if(board.at(x+k*dx[i],y+k*dy[i])==0){
                    set[kk]='0';
                }
                if(k==0)set[kk]='&';
                kk++;
            }
            set[11]='\0';
            if(strstr(set,"*111&")!=NULL||strstr(set,"&111*")!=NULL||strstr(set,"&11110")!=NULL||strstr(set,"01111&")!=NULL||strstr(set,"111&1")!=NULL||strstr(set,"1&111")!=NULL
             ||strstr(set,"*11&1*")!=NULL||strstr(set,"*1&11*")!=NULL||strstr(set,"11&11")!=NULL||strstr(set,"&1111")!=NULL||strstr(set,"1111&")!=NULL){
                return true;
            }
        }
        return false;
    }
}

int value(const Board &board, int x, int y){//对单点进行估值
    int VALUE[4]={0};
    int VALUENUM=0;
    int hidedanger=0;
    int hideattack=0;
    int dx[4]={1,1,0,1};
    int dy[4]={0,-1,1,1};
    if(board.at(x,y)==-1){
        for(int i=0;i<4;i++){
            char set[12];
            int kk=0;
            for(int k=-5;k<=5;k++){
                if(board.at(x+k*dx[i],y+k*dy[i])==1){
                    set[kk]='1';
                }else if(board.at(x+k*dx[i],y+k*dy[i])==-1){
                    set[kk]='*';
                }else if(board.at(x+k*dx[i],y+k*dy[i])==0){
                    set[kk]='0';
                }else if(k==0)
                    set[kk]='&';
                kk++;
            }
            set[11]='\0';
            if(strstr(set,"00000")!=NULL)VALUE[VALUENUM]+=50000000;
            if(strstr(set,"10000&")!=NULL||strstr(set,"&00001")!=NULL||strstr(set,"00&001")!=NULL||strstr(set,"100&00")!=NULL||strstr(set,"000&0")!=NULL||strstr(set,"0&000")!=NULL
                    ||strstr(set,"0&0001")!=NULL||strstr(set,"1000&0")!=NULL||strstr(set,"000&01")!=NULL||strstr(set,"10&000")!=NULL||strstr(set,"00&00")!=NULL){
                VALUE[VALUENUM]+=5000000;
            }
            if(strstr(set,"*00&00*")!=NULL||strstr(set,"*000&0*")!=NULL||strstr(set,"*0&000*")!=NULL){
                VALUE[VALUENUM]+=5000000;
            }
            if(strstr(set,"*&000*")!=NULL||strstr(set,"*000&*")!=NULL||strstr(set,"*0&00*")!=NULL||strstr(set,"*00&0*")!=NULL){
                VALUE[VALUENUM]+=50000;
                hideattack++;
            }
            if(strstr(set,"*&0001")!=NULL||strstr(set,"1000&*")!=NULL||strstr(set,"*0&001")!=NULL||strstr(set,"100&0*")!=NULL||strstr(set,"*0*&0*")!=NULL||strstr(set,"*0&*0*")!=NULL
                    ||strstr(set,"00&01")!=NULL||strstr(set,"10&00")!=NULL||strstr(set,"*00&*")!=NULL||strstr(set,"*&00*")!=NULL||strstr(set,"*0&0*")!=NULL){
                VALUE[VALUENUM]+=500;
                hideattack++;
            }
            if(strstr(set,"&0*")!=NULL||strstr(set,"*0&**")!=NULL||strstr(set,"100&**")!=NULL||strstr(set,"**&001")!=NULL) {
                VALUE[VALUENUM]+=50;
            }
            if(strstr(set,"11111")!=NULL)VALUE[VALUENUM]+=60000000;
            if(strstr(set,"01111&")!=NULL||strstr(set,"&11110")!=NULL||strstr(set,"11&110")!=NULL||strstr(set,"011&11")!=NULL
                    ||strstr(set,"1&1110")!=NULL||strstr(set,"0111&1")!=NULL||strstr(set,"111&10")!=NULL||strstr(set,"01&111")!=NULL||strstr(set,"11&11")!=NULL){
                VALUE[VALUENUM]+=6000000;
            }
            if(strstr(set,"*11&11*")!=NULL||strstr(set,"*111&1*")!=NULL||strstr(set,"*1&111*")!=NULL){
                VALUE[VALUENUM]+=6000000;
            }
            if(strstr(set,"*&111*")!=NULL||strstr(set,"*111&*")!=NULL||strstr(set,"*1&11*")!=NULL||strstr(set,"*11&1*")!=NULL){
                VALUE[VALUENUM]+=60000;
                hidedanger++;
            }
            if(strstr(set,"*&1110")!=NULL||strstr(set,"0111&*")!=NULL||strstr(set,"*1&110")!=NULL||strstr(set,"011&1*")!=NULL||strstr(set,"*1*&1*")!=NULL||strstr(set,"*1&*1*")!=NULL
                    ||strstr(set,"11&10")!=NULL||strstr(set,"01&11")!=NULL||strstr(set,"*11&*")!=NULL||strstr(set,"*&11*")!=NULL||strstr(set,"*1&1*")!=NULL){
                VALUE[VALUENUM]+=600;
                hidedanger++;
            }
            if(strstr(set,"&1*")!=NULL||strstr(set,"*1&**")!=NULL||strstr(set,"011&**")!=NULL||strstr(set,"**&110")!=NULL) {
                VALUE[VALUENUM]+=60;
            }
            VALUENUM++;
        }
    }else return 0;
    int totalvalue=0;
    for(int i=0;i<VALUENUM;i++){
        totalvalue+=VALUE[i];
    }
    totalvalue+=(hidedanger/2)*6000000;
    totalvalue+=(hideattack/2)*6000000;
    return totalvalue+100/(abs((board_size/2-x)*(board_size/2-x)+(board_size/2-y)*(board_size/2-y))+1);//同等条件下中间点分数高
}
int scoretable(int number,int empty1)//计分板
{
    if(number>=5)	return 100000;
    else if(number==4)
    {
        if(empty1==2)	return 10000;
        else if(empty1==1)	return 1000;
    }
    else if(number==3)
    {
        if(empty1==2)	return 1000;
        else if(empty1==1)	return 100;
    }
    else if(number==2)
    {
        if(empty1==2)	return 100;
        else if(empty1==1)	return 10;
    }
    else if(number==1&&empty1==2)	return 10;
    return 0;
}
int countscore(vector<int> n,int turn)//正斜线、反斜线、横、竖，均转成一维数组来计算
{
    int scoretmp=0;
    int len=n.size();
    int empty1=0;
    int number=0;
    if(n[0]==0)	++empty1;
    else if(n[0]==turn)	++number;
    int i=1;
    while(i<len)
    {
        if(n[i]==turn)	++number;
        else if(n[i]==0)
        {
            if(number==0)	empty1=1;
            else
            {
                scoretmp+=scoretable(number,empty1+1);
                empty1=1;
                number=0;
            }
        }
        else
        {
            scoretmp+=scoretable(number,empty1);
            empty1=0;
            number=0;
        }
        ++i;
    }
    scoretmp+=scoretable(number,empty1);
    return scoretmp;
}
int evaluate_minmax_noalphabeta(const Board &board)//评估函数，评估局势
{
    int scorecomputer=0;
    int scorehumber=0;
    //横排们
    for(int i=0;i<board_size;++i)
    {
        vector<int> n;
        for(int j=0;j<board_size;++j)
            n.push_back(board.at(i,j));
        scorecomputer+=countscore(n,0);
        scorehumber+=countscore(n,1);
        n.clear();
    }
    //竖排们
    for(int j=0;j<board_size;++j)
    {
        vector<int> n;
        for(int i=0;i<board_size;++i)
            n.push_back(board.at(i,j));
        scorecomputer+=countscore(n,0);
        scorehumber+=countscore(n,1);
        n.clear();
    }
    //上半正斜线们
    for(int i=0;i<board_size;++i)
    {
        int x,y;
        vector<int> n;
        for(x=i,y=0;x<board_size&&y<board_size;++x,++y)
            n.push_back(board.at(y,x));
        scorecomputer+=countscore(n,0);
        scorehumber+=countscore(n,1);
        n.clear();
    }
    //下半正斜线们
    for(int j=1;j<board_size;++j)
    {
        int x,y;
        vector<int> n;
        for(x=0,y=j;y<board_size&&x<board_size;++x,++y)
            n.push_back(board.at(y,x));
        scorecomputer+=countscore(n,0);
        scorehumber+=countscore(n,1);
        n.clear();
    }
    //上半反斜线们
    for(int i=0;i<board_size;++i)
    {
        vector<int> n;
        int x,y;
        for(y=i,x=0;y>=0&&x<16;--y,++x)
            n.push_back(board.at(y,x));
        scorecomputer+=countscore(n,0);
        scorehumber+=countscore(n,1);
        n.clear();
    }
    //下半反斜线们
    for(int j=1;j<board_size;++j)
    {
        vector<int> n;
        int x,y;
        for(y=j,x=board_size-1;y<board_size&&x>=0;++y,--x)
            n.push_back(board.at(x,y));
        scorecomputer+=countscore(n,0);
        scorehumber+=countscore(n,1);
        n.clear();
    }
    return scorecomputer-scorehumber;
}
int TotalValue(const Board &board){//对全局进行估值
    int aifour=0,aithree=0,aidthree=0,ailtwo=0,aidtwo=0;
    int plfour=0,plthree=0,pldthree=0,plltwo=0,pldtwo=0;
    int dx[4]={0,1,1,-1};
    int dy[4]={1,0,1,1};
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){
            for(int k=0;k<4;k++)
            if(board.at(i,j)==0&&board.at(i+dx[k],j+dy[k])==0){
                if(board.at(i,j)==0&&board.at(i+dx[k],j+dy[k])==0&&(board.at(i-dx[k],j-dy[k])==1))aidtwo++;
                if(board.at(i,j)==0&&board.at(i+dx[k],j+dy[k])==0&&(board.at(i-dx[k],j-dy[k])==-1&&board.at(i+2*dx[k],j+2*dy[k])==-1)){
                    ailtwo++;
                }
                if(board.at(i,j)==0&&board.at(i+dx[k],j+dy[k])==0&&board.at(i+2*dx[k],j+2*dy[k])==0){
                    if(board.at(i-dx[k],j-dy[k])==-1&&board.at(i+3*dx[k],j+3*dy[k])==-1||(board.at(i-dx[k],j-dy[k])==1&&board.at(i+3*dx[k],j+3*dy[k])==0))
                        aithree++;
                    else if(board.at(i-dx[k],j-dy[k])==1||board.at(i+3*dx[k],j+3*dy[k])==1)
                        aidthree++;
                    if(board.at(i-dx[k],j-dy[k])==-1&&board.at(i+3*dx[k],j+3*dy[k])==1)
                        aifour++;
                }
                if(board.at(i,j)==0&&board.at(i+dx[k],j+dy[k])==0&&board.at(i+2*dx[k],j+2*dy[k])==0&&board.at(i+3*dx[k],j+3*dy[k])==0&&board.at(i+4*dx[k],j+4*dy[k])==0)
                    return 9000000000;
            }
        }
    }
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){
            for(int k=0;k<4;k++)
                if(board.at(i,j)==1&&board.at(i+dx[k],j+dy[k])==1){
                    if(board.at(i,j)==1&&board.at(i+dx[k],j+dy[k])==1&&(board.at(i-dx[k],j-dy[k])==0))pldtwo++;
                    if(board.at(i,j)==1&&board.at(i+dx[k],j+dy[k])==1&&(board.at(i-dx[k],j-dy[k])==-1&&board.at(i+2*dx[k],j+2*dy[k])==-1)){
                        plltwo++;
                    }
                    if(board.at(i,j)==1&&board.at(i+dx[k],j+dy[k])==1&&board.at(i+2*dx[k],j+2*dy[k])==1){
                        if(board.at(i-dx[k],j-dy[k])==-1&&board.at(i+3*dx[k],j+3*dy[k])==-1||(board.at(i-dx[k],j-dy[k])==0&&board.at(i+3*dx[k],j+3*dy[k])==1))
                            plthree++;
                        else if(board.at(i-dx[k],j-dy[k])==0||board.at(i+3*dx[k],j+3*dy[k])==0)
                            pldthree++;
                        if(board.at(i-dx[k],j-dy[k])==-1&&board.at(i+3*dx[k],j+3*dy[k])==0)
                            plfour++;
                    }
                    if(board.at(i,j)==1&&board.at(i+dx[k],j+dy[k])==1&&board.at(i+2*dx[k],j+2*dy[k])==1&&board.at(i+3*dx[k],j+3*dy[k])==1&&board.at(i+4*dx[k],j+4*dy[k])==1)
                        return -9000000000;
                }
        }
    }
    return (aifour-plfour)*1000000+(aithree-plthree)*10000+(ailtwo-plltwo)*100+(aidthree-pldthree)*10+(aidtwo-pldtwo)*1;
}
const int MAX = 10000000;
const int MIN = -10000000;
int getValue(int x,int y,int deep,int alpha,int beta,Board board){//递归的函数
    if(deep==3){
        return TotalValue(board);
    }
    if(deep==0){
        board.set(x,y,deep%2);
        deep++;
    }
    if(deep%2==0){//极大
        int best = MIN;
        for(int i=x-2;i<x+3;i++)
            for (int j=y-2; j<y+3;j++){
                if(board.at(i,j)!=-1)
                    continue;
                Board NEW=board;
                NEW.set(i,j,(deep)%2);
                if(board.check_winner(0))//判断模拟下棋方是否已分胜负
                    return 900000000;
                if(board.check_winner(1))
                    return -900000000;
                int val = getValue(i,j,deep+1,alpha,beta,NEW);
                best = max(best, val);
                alpha = max(alpha, best);
          // Alpha Beta Pruning
            if (beta <= alpha)
                break;
            }
            return best;
    }else
    {//极小
    int best = MAX;
    for(int i=x-2;i<x+3;i++)
        for (int j=y-2;j<y+3;j++){
            if(board.at(i,j)!=-1)
                continue;
            Board NEW=board;
            NEW.set(i,j,(deep)%2);
            if(board.check_winner(0))//判断模拟下棋方是否已分胜负
                return 900000000;
            if(board.check_winner(1))
                return -900000000;
            int val = getValue(i,j,deep+1,alpha,beta,NEW);
    best = min(best, val);
    beta = min(beta, best);
  // Alpha Beta Pruning
    if (beta <= alpha)
        break;
    }
    return best;
    }
}
int max(int a,int b){
    return (a>b)?a:b;
}
int min(int a,int b){
    return (a<b)?a:b;
}
int way(int x,int y,Board board){//循环贪心算法
    int deep=0;
    int best=0;
    int mx=x;
    int my=y;
    int maxdeep=4;
    while(deep<=maxdeep){
        if(deep==maxdeep)
            return TotalValue(board);
        board.set(mx,my,deep%2);
        if(board.check_winner(0))//判断模拟下棋方是否已分胜负
            return 9000000000;
        if(board.check_winner(1))
            return -9000000000;
        deep++;
        int MX=mx;
        int MY=my;
        int n;
        for(int i=MX-4;i<MX+5;i++){
            for(int j=MY-4;j<MY+5;j++){
                if(board.at(i,j)==-1)
                if((n=value(board,i,j))>best){
                    mx=i;
                    my=j;
                    best=n;
                }
            }
        }
    }
}

void solve1(const Board& board,BoardWindow*Game)
{
    int mx=0,my=0,mv=-20000000;
    int danger[2][10]={0};
    int dangernum=0;
    static bool isempty=true;
    for(int i=0;i<board_size;i++){
        for(int j=0;j<board_size;j++){
            if(board.at(i,j)==1||board.at(i,j)==0){//棋盘是否为空
                isempty=false;
            }
            if(board.at(i,j)<=-1&&board.at(i-1,j-1)<=-1&&board.at(i,j-1)<=-1&&
                    board.at(i-1,j)<=-1&&board.at(i+1,j+1)<=-1&&board.at(i+1,j)<=-1&&
                    board.at(i,j+1)<=-1&&board.at(i-1,j+1)<=-1&&board.at(i+1,j-1)<=-1){
                continue;
            }

            /*if(board.at(i,j)==-1&&(isdanger(board,i,j)==true||isattack(board,i,j)==true)){//如果有危险或自己能成的直接下
                mx=i;
                my=j;
                danger[0][dangernum]=mx;
                danger[1][dangernum]=my;
                dangernum++;
            }*/
            if(board.at(i,j)==-1&&(board.at(i+1,j)>-1||board.at(i-1,j)>-1||board.at(i,j+1)>-1||board.at(i,j-1)>-1||
                                   board.at(i+1,j-1)>-1||board.at(i-1,j+1)>-1||board.at(i+1,j+1)>-1||board.at(i-1,j-1)>-1)){
            int Try;
            Board newboard=board;
            //下面是四种方法
            if(board.at(i,j)==-1&&(Try=getValue(i,j,0,MIN,MAX,newboard))>=mv){//1、通过多层minimax递归+alpha/beta剪枝
            //if(board.at(i,j)==-1&&(Try=evaluate_minmax_noalphabeta(board))>=mv){//2、TODO:这个评分函数还有问题
            //if(board.at(i,j)==-1&&(Try=way(i,j,board))>=mv){//3、通过多次循环，以单点分数为标准贪心算法
            //if(board.at(i,j)==-1&&(Try=value(board,i,j))>=mv){//4、直接单层搜索
                mv=Try;
                mx=i;
                my=j;
                }
            }
        }
    }
    if(isempty==true)
    {//棋盘为空下在中间
        mx=9;
        my=9;
    }
    if(dangernum!=0){//如果有危险的话
        int bestnum=0;
        for(int i=0;i<dangernum;i++){
            if(value(board,danger[0][i],danger[1][i])>bestnum){//通过单点价值判断下在哪里
                my=danger[1][i];
                mx=danger[0][i];
            }
        }
    }
    Game->make_move(mx,my);
}
