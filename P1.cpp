#include<bits/stdc++.h>
using namespace std;

class Graph {
    private: unordered_map<int,vector<int>> graph;

    public: 

    void addEdge(int u,int v){
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    void dfsUtil(int v,int lv,unordered_map<int,bool>&visited){
        visited[v]=true;
        cout<<" { "<<lv<<" , "<<v<<" } "<<endl;
        for(int ng:graph[v]){
            if(!visited[ng]){
                dfsUtil(ng,lv+1,visited);
            }
        }
    }

    void dfs(int s){
        unordered_map<int,bool>visited;
        for(auto x:graph){
            visited[x.first]=false;
        }
        dfsUtil(s,0,visited);
    }

    void bfs(int s){
        unordered_map<int,bool>visited;
        for(auto x:graph){
            visited[x.first]=false;
        }

        queue<pair<int,int>>q;
        q.push({s,0});

        while(!q.empty()){
            int v=q.front().first;
            int lv=q.front().second;
            q.pop();

            if(!visited[v]){
                visited[v]=true;
                cout<<" { "<<lv<<" , "<<v<<" } "<<endl;
                for(int ng:graph[v]){
                    if(!visited[ng]){
                        q.push({ng,ng+1});
                    }
                }
            }
        }
    }
};

class FileSystem{
    private: unordered_map<string,vector<string>>system;

    public:

    void addData(const string &folder,const string &data){
        system[folder].push_back(data);
    }

    bool searchFile(const string &folder,const string &target_file,bool &found){
        for(string file:system[folder]){
            if(file==target_file){
                cout<<"\nFile "<<target_file<<" found in folder "<<folder;
                found=true;
            }
        }

        for(string subFolder:system[folder]){
            searchFile(subFolder,target_file,found);
        }
    }
};

class NetworkRouter{

    private: unordered_map<int,vector<int>>graph;

    public:

    void addEdge(int u,int v){
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> shortestPath(int s,int d){
        queue<int>q;
        unordered_map<int,int>parent;
        unordered_map<int,int>dist;

        for(auto x:graph){
            dist[x.first]=INT_MAX;
        }

        q.push(s);
        parent[s]=-1;
        dist[s]=0;

        while(!q.empty()){
            int v = q.front();
            q.pop();

            if(v==d) break;

            for(int x:graph[v]){
                if(dist[x]==INT_MAX){
                    q.push(x);
                    parent[x]=v;
                    dist[x]=dist[v]+1;
                }
            }
        }

        vector<int>ans;
        int curr=d;
        while(curr!=-1){
            ans.push_back(curr);
            curr = parent[curr];
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};

int main(){
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    cout<<"\nDepth first search: "<<endl;
    cout<<"{Level,Value}"<<endl;
    g.dfs(0);

    cout<<"\nBreadth first search: "<<endl;
    cout<<"{Level,Value}"<<endl;
    g.bfs(0);

    FileSystem fs;
    fs.addData("/","F1");
    fs.addData("/","F2");
    fs.addData("F1","F1-F1");
    fs.addData("F1","F1-F2");
    fs.addData("F2","F2-F1");
    fs.addData("F2","F2-F2");
    fs.addData("F2-F2","target.txt");

    bool found=false;
    fs.searchFile("F2","target.txt",found);
    if(!found) cout<<"\nFile not found!"<<endl;

    found=false;
    fs.searchFile("F1","target.txt",found);
    if(!found) cout<<"\nFile not found!"<<endl;

    NetworkRouter network;
    // Adding edges to represent the network topology
    network.addEdge(0, 1);
    network.addEdge(0, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);
    network.addEdge(4, 5);

    int source = 0;
    int destination = 5;

    vector<int> shortest_path = network.shortestPath(source, destination);

    if (!shortest_path.empty()) {
        cout << "\nShortest path from router " << source << " to router " << destination << endl;
        for (int router : shortest_path) {
            cout << router << " ";
        }
        cout << endl;
    } else {
        cout << "\nNo path exists from router " << source << " to router " << destination << endl;
    }
    return 0;
}