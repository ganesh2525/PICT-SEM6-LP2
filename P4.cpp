#include<bits/stdc++.h>
using namespace std;

void printSolution(vector<vector<int>>&board, int N) {
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(board[i][j])
                cout<<"Q";
            else
                cout<<" . ";
        }
        cout<<endl;
    }
    cout<<endl;
}

bool isSafe(vector<vector<int>>&board, int row, int col, int N){
    int i,j;

    for(i=0;i<col;i++)
        if(board[row][i]) return false;

    for(i=row,j=col; i>=0 && j>=0; i--,j--)
        if(board[i][j]) return false;

    for(i=row,j=col; i<N && j>=0; i++,j--)
        if(board[i][j]) return false;

    return true;
}

bool Nqueen(vector<vector<int>>&board, int col, int N){

    if(col>=N) return true;

    for(int i=0;i<N;i++){
        if(isSafe(board,i,col,N)){
            board[i][col]=1;
            if(Nqueen(board,col+1,N)) return true;
            board[i][col]=0;
        }
    }
    
    return false;
}

void solve(int N){
    vector<vector<int>>board(N,vector<int>(N,0));
    
    if(Nqueen(board,0,N)){
        printSolution(board,N);
        return;
    }
    cout<<"Solution not found!"<<endl;
}

int main(){
    int N;
    while(true){
        cout<<"N = ";
        cin>>N;
        if(N==-1) break;
        solve(N);
    }
    return 0;
}