#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
char player1='o';
char player2='x';
struct Move{ 
    int row, col; 
};
bool isMovesLeft(char board[][4]){ 
    for (int i=0;i<4;i++) 
        for (int j=0;j<4;j++) 
            if (board[i][j]=='_') 
                return true; 
    return false; 
} 
int evalution(char board[][4]){
	for (int row = 0; row<4; row++) 
    { 
        if (board[row][0]==board[row][1] && 
            board[row][1]==board[row][2] && 
            board[row][2]==board[row][3]) 
        { 
            if (board[row][0]==player1) 
                return 100; 
            else if (board[row][0]==player2) 
                return -100; 
        } 
    }
    for (int col = 0; col<4; col++) 
    { 
        if (board[0][col]==board[1][col]  && 
            board[1][col]==board[2][col]  && 
            board[2][col]==board[3][col]) 
        { 
            if (board[0][col]==player1) 
                return 100; 
  
            else if (board[0][col]==player2) 
                return -100; 
        } 
    }
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[2][2]==board[3][3]) 
    { 
        if (board[0][0]==player1) 
            return 100; 
        else if (board[0][0]==player2)
            return -100; 
    } 
  
    if (board[0][3]==board[1][2] && board[1][2]==board[2][1] && board[2][1]==board[3][0]) 
    { 
        if (board[0][3]==player1) 
            return 100; 
        else if (board[0][3]==player2) 
            return -100; 
    }
    return 0;
}
int minimax(char board[][4], int depth,int alpha, int beta, bool isplayer){
	int score=evalution(board);
	if(score==100)
		return 100-depth;
	if(score==-100)
		return -100+depth;
	if(!isMovesLeft(board))
		return 0;
	if(isplayer){
		int value_best=-1000;
		int value=-1000;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(board[i][j]=='_'){
					board[i][j] = player1;
					value = minimax(board, depth+1, alpha, beta, !isplayer);
					value_best = max(value, value_best);
					board[i][j] = '_';
					alpha = max(value, alpha);
					if(beta <= alpha)
						break;
				}
			}
		}
		return value_best;
	}
	else{
		int value_worst=1000;
		int value=1000;
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				if(board[i][j]=='_'){
					board[i][j] = player2;
					value = minimax(board, depth+1, alpha, beta, !isplayer);
					value_worst = min(value, value_worst);
					board[i][j] = '_';
					beta = min(beta, value);
					if(beta <= alpha)
						break;
				}
			}
		}
		return value_worst;
	}
}
Move findbestmove(char board[][4]){
	int bestVal = -1000; 
    Move bestMove; 
    bestMove.row = -1; 
    bestMove.col = -1; 
    for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if (board[i][j]=='_'){
				board[i][j]=player1;
				int moveVal = minimax(board, 0, -1000, 1000, false);
				board[i][j] = '_';
				if (moveVal > bestVal){ 
                    bestMove.row = i; 
                    bestMove.col = j; 
                    bestVal = moveVal; 
                }
                else if(moveVal == bestVal&&rand()%2){
                	bestMove.row = i; 
                    bestMove.col = j;
				}
			}
		}
	}
	return bestMove; 
}
void printboard(char board[][4]){
	for(int i=0;i<4;i++)
	for(int j=0;j<4;j++){
		if(j==3)
			cout<<board[i][j]<<endl;
		else
			cout<<board[i][j]<<' ';
	}
}
int main(){
	srand(time(NULL));
	char board[4][4]={'_','_','_','_',
					  '_','_','_','_',
					  '_','_','_','_',
					  '_','_','_','_'};
	Move choose, opponent;
	while(isMovesLeft){
		cin>>choose.row>>choose.col;
		while(board[choose.row][choose.col]!='_'){
			cout<<"Error please enter again"<<endl;
			cin>>choose.row>>choose.col;
		}
		board[choose.row][choose.col]=player2;
		printboard(board);
		cout<<endl;
		if(evalution(board)==-100){
			cout<<"player2 win"<<endl;
			break;
		}
		opponent=findbestmove(board);
		board[opponent.row][opponent.col]=player1;
		printboard(board);
		cout<<endl;
		if(evalution(board)==100){
			cout<<"computer win"<<endl;
			break;
		}
		if(!isMovesLeft(board)){
			cout<<"tie"<<endl;
			break;
		}
	}
	system("PAUSE");
    return 0; 
}
