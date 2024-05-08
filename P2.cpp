#include<bits/stdc++.h>
using namespace std;

struct PuzzleState {
    int puzzle[3][3];
    int moves;
    int hcost;
    int row;
    int col;
};

struct Compares {
    bool operator()(const PuzzleState &p1,const PuzzleState &p2) const {
        return (p1.moves + p1.hcost) > (p2.moves + p2.hcost);
    }
};

bool isGoalstate(int puzzle[3][3], int goal[3][3]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(puzzle[i][j]!=goal[i][j]) return false;
        }
    }
    return true;
}

void printState(PuzzleState &p){
    cout<<"\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<p.puzzle[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"Moves: "<<p.moves<<"\nHeuristic Cost: "<<p.hcost<<endl;
}

string convertStr(int puzzle[3][3]){
    string str = "";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            str += to_string(puzzle[i][j]) + " ";
        }
    }
    return str;
}

bool isSafe(int nrow,int ncol) {
    return (0<=nrow && nrow<=2) && (0<=ncol && ncol<=2);
}

int calculateHcost(int puzzle[3][3], int goal[3][3]){
    int count = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(puzzle[i][j]!=0 && puzzle[i][j]!=goal[i][j]) count++;
        }
    }
    return count;
}

PuzzleState createState(int puzzle[3][3], int nrow, int ncol, int row, int col, int moves, int goal[3][3]){
    PuzzleState nstate;
    nstate.row = nrow; 
    nstate.col = ncol;
    nstate.moves = moves+1;
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            nstate.puzzle[i][j] = puzzle[i][j];
        }
    }
    
    swap(nstate.puzzle[row][col],nstate.puzzle[nrow][ncol]);
    nstate.hcost = calculateHcost(nstate.puzzle,goal);
    return nstate;
}

void solvePuzzle(PuzzleState &initial, PuzzleState &goal) {
    priority_queue<PuzzleState, vector<PuzzleState>, Compares> pq;
    map<string,bool>visited;

    pq.push(initial);

    while(!pq.empty()){
        PuzzleState curr = pq.top();
        pq.pop();

        printState(curr);
        if(isGoalstate(curr.puzzle,goal.puzzle)){
            cout<<"\nSolution Found!"<<endl;
            return;
        }

        visited[convertStr(curr.puzzle)] = true;

        int m1[4] = {-1,1,0,0};
        int m2[4] = {0,0,-1,1};

        for(int i=0; i<4; i++) {
            int nrow = m1[i] + curr.row;
            int ncol = m2[i] + curr.col;

            if(isSafe(nrow,ncol)){
                PuzzleState nstate = createState(curr.puzzle,nrow,ncol,curr.row,curr.col,curr.moves,goal.puzzle);

                if(!visited[convertStr(nstate.puzzle)]){
                    pq.push(nstate);
                    visited[convertStr(nstate.puzzle)]=true;
                }
            }
        }
    }

    cout<<"\nSolution not found"<<endl;
}

int main(){
    PuzzleState initial = PuzzleState{
        {{1,2,3},{4,5,6},{7,8,0}},
        0,0,2,2
    };

    PuzzleState goal = PuzzleState{
        {{1,2,3},{4,6,0},{7,5,8}},
        0,0,1,2
    };

    cout<<"\nInitial State: "<<endl;
    printState(initial);

    cout<<"\nGoal State: "<<endl;
    printState(goal);

    cout<<"\nSolving Puzzle ..."<<endl;
    solvePuzzle(initial,goal);

    return 0;
}