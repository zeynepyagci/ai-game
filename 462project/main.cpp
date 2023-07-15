#include <iostream>
#include <cstdlib>
#include <ctime>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;

int board[7][7];
int current_marker;
int player_id = 1;
int ai_id = 2;
int remove_cellpoint_x;
int remove_cellpoint_y;
int turn_id;
int move_cellpoint_x;
int move_cellpoint_y;
int checking[7][7];
bool flag = true;
bool flag2 = true;
bool flag3 = true;
int prevmovement[7][7];
int prow,pcol;
int airow,aicol;
int temp;


void fill_board(){

   int value = 5;
    for (int i=0; i<7; i++){
        for (int j=0; j<7; j++){
            board[i][j] = value;
        }
    }

}

void printUI(){

    cout<<"-----------------------------\n";
    for (int i=0; i<7; i++){
            cout<<"| ";
        for (int j=0; j<7; j++){
            cout<<board[i][j]<<" | ";
        }
        cout<<"\n-----------------------------\n";
    }

}

int isMovesLeft(int row, int column){

    int best=0;

    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if (board[i][j]== 5)
                best++;
        }
    }
    return best;


}


void delete_tiles(int remove_cellpoint_x, int remove_cellpoint_y){

    int row = remove_cellpoint_x-1;
    int col = remove_cellpoint_y-1;

    if(checking[row][col]!=board[row][col] && prevmovement[row][col]!=board[row][col]){

        board[row][col] = current_marker;
        checking[row][col]=board[row][col];
        flag=true;

    }
    else{
        flag=false;
    }


}


void move_players(int move_cellpoint_x, int move_cellpoint_y){

    int row = move_cellpoint_x-1;
    int col = move_cellpoint_y-1;



    if(prevmovement[row][col]!=board[row][col] && checking[row][col]!=board[row][col]){

        board[prow][pcol] = 5;
        board[row][col] = player_id;
        prow = row;
        pcol = col;
        prevmovement[row][col] = board[row][col];
        flag2=true;


    }
    else{
        flag2=false;
    }


}

void swap_player(){

    if(player_id==1){
        player_id=2;
    }
    else{
        player_id=1;
    }

}

void ai_delete(){

    int prevaicol;
    int prevairow;
    int maxcolumn;
    int maxrow;
    int maxvalue;

    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(board[prow+i][pcol+j]==5 && prow+i<7 && pcol+j<7 && prow+i>0 && pcol+j>0){
                if(maxvalue<=isMovesLeft(prow+i,pcol+j)){
                    maxrow=prow+i;
                    maxcolumn=pcol+j;
                }
            }

        }
    }



    prevairow=maxrow;
    prevaicol=maxcolumn;

    cout<<"Row: "<<prevairow+1<<endl;
    cout<<"Column: "<<prevaicol+1<<endl;

    board[prevairow][prevaicol] = 8;



}

void ai_move(){

    int maxcolumn;
    int maxrow;
    int maxvalue;

    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(board[airow+i][aicol+j]==5 && airow+i<7 && aicol+j<7 && airow+i>0 && aicol+j>0){
                if(maxvalue<=isMovesLeft(airow+i,aicol+j)){
                    maxrow=airow+i;
                    maxcolumn=aicol+j;
                }
            }

        }
    }

    board[airow][aicol] = 5;

    airow=maxrow;
    aicol=maxcolumn;

    cout<<"Row: "<<airow+1<<endl;
    cout<<"Column: "<<aicol+1<<endl;

    board[airow][aicol] = ai_id;

}


int check_ai_win(){

    if((board[prow][pcol+1] == 8) && (board[prow+1][pcol+1] == 8) && (board[prow+1][pcol] == 8) && (board[prow+1][pcol-1]) == 8 && (board[prow][pcol-1] == 8) && (board[prow-1][pcol-1] == 8) && (board[prow-1][pcol] == 8) && (board[prow-1][pcol+1] == 8)){

        cout<<"AI win the game"<<endl;
        exit(0);

    }
    else{
        return 0;
    }

}

int check_player_win(){

    if((board[airow][aicol+1] == 8) && (board[airow+1][aicol+1] == 8) && (board[airow+1][aicol] == 8) && (board[airow+1][aicol-1]) == 8 && (board[airow][aicol-1] == 8) && (board[airow-1][aicol-1] == 8) && (board[airow-1][aicol] == 8) && (board[airow-1][aicol+1] == 8)){

        cout<<"You win the game"<<endl;
        exit(0);

    }
    else{
        return 0;
    }

}


void game(){


    if(turn_id==0){
        board[0][3] = player_id;
        prevmovement[0][3]=1;
        prow=0;
        pcol=3;

        board[6][3] = ai_id;
        prevmovement[6][3]=2;
        airow=6;
        aicol=3;

        turn_id++;

    }


    printUI();

    for(int i=0; i<49; i++){
    if(player_id==1){
    while(flag3==true){
        cout<<"Turn: "<<turn_id<<endl;
        cout<<"Player "<<player_id<<" enter the tile you want to move in x coordinates: ";
        cin >> move_cellpoint_x;
        cout<<"Player "<<player_id<<" enter the tile you want to move in y coordinates: ";
        cin >> move_cellpoint_y;

        while((2<move_cellpoint_x-prow) || (move_cellpoint_x-prow<-2) || (2<move_cellpoint_y-pcol) || (move_cellpoint_y-pcol<-2)){
            cout<<"You can't move there"<<endl;
            cout<<"Player "<<player_id<<" enter the tile you want to move in x coordinates: ";
            cin >> move_cellpoint_x;
            cout<<"Player "<<player_id<<" enter the tile you want to move in y coordinates: ";
            cin >> move_cellpoint_y;
        }
        move_players(move_cellpoint_x, move_cellpoint_y);
        flag3=false;
    }

        if(flag2==true){
            printUI();
            cout<<"Player "<<player_id<<" enter the tile you want to delete in x coordinates: ";
            cin >> remove_cellpoint_x;
            cout<<"Player "<<player_id<<" enter the tile you want to delete in y coordinates: ";
            cin >> remove_cellpoint_y;
            delete_tiles(remove_cellpoint_x,remove_cellpoint_y);

            if(flag==true){
                swap_player();
                printUI();
                turn_id++;
                flag3=true;
            }
            else{
                while(flag==false){
                    cout << "It's already deleted, choose another tile to delete"<<endl;
                    cout<<"Player "<<player_id<<" enter the tile you want to delete in x coordinates: ";
                    cin >> remove_cellpoint_x;
                    cout<<"Player "<<player_id<<" enter the tile you want to delete in y coordinates: ";
                    cin >> remove_cellpoint_y;
                    delete_tiles(remove_cellpoint_x,remove_cellpoint_y);
                }
                printUI();
                swap_player();
                turn_id++;
                flag3=true;
            }

        }
        else{
            while(flag2==false){
                cout << "Choose another tile to move"<<endl;
                cout<<"Player "<<player_id<<" enter the tile you want to move in x coordinates: ";
                cin >> move_cellpoint_x;
                cout<<"Player "<<player_id<<" enter the tile you want to move in y coordinates: ";
                cin >> move_cellpoint_y;
                move_players(move_cellpoint_x, move_cellpoint_y);
            }
            flag3=false;
            printUI();

        }




    }

    else{

        check_player_win();
        cout << "AI's turn"<< endl;
        cout << "AI moving"<<endl;
        ai_move();
        cout << "AI deleting a tile"<< endl;
        ai_delete();
        check_ai_win();
        printUI();
        swap_player();
        turn_id;

    }
    }

}



int main()
{
    fill_board();
    cout << "\n";
    current_marker=8;
    game();
    printUI();
}
