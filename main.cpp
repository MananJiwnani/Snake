#include <bits/stdc++.h>
#include <thread>
#include <chrono>
using namespace std;

#define F first
#define S second

class Snake{
    public:
    pair<int,int> pos = {0,0};
    Snake* next = nullptr;

    Snake(){
        pos = {0,0};
        next = nullptr;
    }

    Snake(Snake* tail){
        pos = tail->getPos();
        next = nullptr;
    }
    
    void move(pair<int,int> z){
        if(next) next->move(pos);
        pos = z;
    }
    
    bool check(int boardSize){
        if(max(pos.F,pos.S)<boardSize && min(pos.F,pos.S)>=0) return true;
        return false;
    }

    pair<int,int> getPos(){
        return pos;
    }

    void makeBoard(vector<vector<char>>& board){
        board[pos.F][pos.S] = '0';
        if(next) next->makeBoard(board);
    }

    void setNext(Snake* temp){
        next = temp;
    }
    
};

pair<int,int> gen(int boardSize){
    int x = rand()%boardSize;
    int y = rand()%boardSize;

    return {x,y};
}

int main(){
    srand(time(0));

    Snake* head = new Snake();
    Snake* tail = head;

    int boardSize;
    cout<<"Board Size (N*N): ";
    cin>>boardSize;
    cout<<endl;

    char move = 'd';
    // w up
    // a left
    // s down
    // d right

    pair<int,int> food = gen(boardSize);
    
    while(true){
        cin>>move;
        cout<<endl;
        
        pair<int,int> nextH = head->getPos();

        switch (move)
        {
            case 'w':
            nextH.F--;
            break;
            case 'a':
            nextH.S--;
            break;
            case 's':
            nextH.F++;
            break;
            case 'd':
            nextH.S++;
            break;
            default:
            break;
        }

        head->move(nextH);

        if(!head->check(boardSize)){
            cout<<"Game Over!"<<endl;
            return 0;
        }

        if(nextH==food){
            food = gen(boardSize);
            Snake* temp = new Snake(tail);
            tail->setNext(temp);
            tail = temp;
        }
        
        
        // print board:
        vector<vector<char>> board(boardSize, vector<char>(boardSize, '.'));
        if(head->next) head->next->makeBoard(board);

        // if(board[nextH.F][nextH.S]=='0'){
        //     cout<<"Game Over!"<<endl;
        //     return 0;
        // }

        board[nextH.F][nextH.S] = 'S';
        board[food.F][food.S] = '1';
        
        for(int i=0;i<boardSize;i++){
            for(int j=0;j<boardSize;j++){
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        
    }

    return 0;
}
