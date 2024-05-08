#include<bits/stdc++.h>
using namespace std;

class Graph {
    int n;
    vector<vector<int>>graph;

    public:

    Graph(int v) {
        n=v;
        graph.resize(n,vector<int>(n,0));
    }

    void addEdge(int u,int v,int w){
        graph[u][v]=w;
        graph[v][u]=w;
    }

    int find(vector<int> &parent,int i){
        while(parent[i]!=i)
            i=parent[i];
        return i;
    }

    void makeUnion(vector<int> &parent,int u,int v){
        int a = find(parent,u);
        int b = find(parent,v);
        parent[a] = b; 
    }

    int minDistance(vector<bool>&sptSet,vector<int>&dist){
        int mind=INT_MAX,index=0;
        for(int i=0;i<n;i++){
            if(!sptSet[i] && dist[i]<mind){
                mind=dist[i];
                index=i;
            }
        }
        return index;
    }

    int prims(vector<vector<int>>&);
    int krushkals(vector<vector<int>>&);
    void dijktras(int,vector<int>&);
};

int Graph::prims(vector<vector<int>> &ans1){

    vector<bool>visited(n,false);
    visited[0]=true;

    int minCost=0,totalCost=0,u=0,v=0;

    int count=n-1;
    while(count--){
        minCost=999;
        for(int i=0;i<n;i++){
            if(visited[i]){
                for(int j=0;j<n;j++){
                    if(!visited[j]){
                        if(graph[i][j]!=0 && graph[i][j]<=minCost){
                            minCost=graph[i][j];
                            u=i;
                            v=j;
                        }
                    }
                }
            }
        }
        visited[v]=true;
        ans1.push_back({u,v,minCost});
        totalCost+=minCost;
    }
    return totalCost;
}

int Graph::krushkals(vector<vector<int>>&ans2){

    vector<int>parent(n);
    for(int i=0;i<n;i++) parent[i]=i;

    int minCost=0,totalCost=0,u=0,v=0;

    int count=n-1;
    while(count--){
        minCost=999;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(find(parent,i)!=find(parent,j) && graph[i][j]!=0 && graph[i][j]<minCost){
                    minCost=graph[i][j];
                    u=i;
                    v=j;
                }
            }
        }
        makeUnion(parent,u,v);
        ans2.push_back({u,v,minCost});
        totalCost+=minCost;
    }
    return totalCost;
}

void Graph::dijktras(int src,vector<int>&dist){
    vector<bool>sptSet(n,false);
    dist[src]=0;

    int count=n-1;
    while(count--){
        int u = minDistance(sptSet,dist);
        sptSet[u] = true;

        for(int v=0;v<n;v++){
            if(!sptSet[v] && graph[u][v] && dist[u]!=INT_MAX && (dist[u]+graph[u][v])<dist[v]){
                dist[v]=dist[u]+graph[u][v];
            }
        }
    }
}

int main(){

    Graph g(5);
    g.addEdge(0,1,7);
    g.addEdge(0,3,2);
    g.addEdge(1,2,5);
    g.addEdge(1,3,6);
    g.addEdge(2,4,2);
    g.addEdge(3,4,4);

    vector<vector<int>>ans1,ans2;
    int total=0;
    
    cout<<"\nUsing Prims Algorithm: "<<endl;
    total = g.prims(ans1);
    cout<<"Minimum lenth of wire required to connect all cities and to form network: "<<endl;
    for(int i=0;i<ans1.size();i++){
        cout<<"From city "<<ans1[i][0]<<" to city "<<ans1[i][1]<<" : "<<ans1[i][2]<<endl;
    }
    cout<<"Total length of wire "<<total<<endl;

    cout<<"\nUsing Krushkals Algorithm: "<<endl;
    total = g.krushkals(ans2);
    cout<<"Minimum lenth of wire required to connect all cities and to form network: "<<endl;
    for(int i=0;i<ans2.size();i++){
        cout<<"From city "<<ans2[i][0]<<" to city "<<ans2[i][1]<<" : "<<ans2[i][2]<<endl;
    }
    cout<<"Total length of wire "<<total<<endl;


    vector<int>dist(5,INT_MAX);
    cout<<"\nUsing Dijktras Algorithm: "<<endl;
    g.dijktras(0,dist);
    cout<<"Minimum path from city 0 to all other cities: "<<endl;
    for(int i=0;i<5;i++){
        cout<<"From city 0 to city "<<i<<" : "<<dist[i]<<endl;
    }

    return 0;
}
