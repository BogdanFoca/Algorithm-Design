#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

ifstream fin("p1.in");
ofstream fout("p1.out");

int N;
int M;
int M2;

vector<int> *adj; // An array of adjacency lists
vector<int> *rev_adj; // An array of adjacency lists
bool *visited;
int numComponents = 0;
stack<int> S;

vector<int> *components;

void ReadData();
void addEdge(int v, int w);
void addEdgeRev(int v, int w);
void kosaraju_dfs_1(int x);
void kosaraju_dfs_2(int x);
void Kosaraju();
bool hasCycle(int node, int adj[]);
int ComputeMinimumEdges();

int main(){
    ReadData();
    Kosaraju();
    fout << ComputeMinimumEdges();
    fout.close();
    return 0;
}

void ReadData(){
    fin >> N;
    fin >> M;
    adj = new vector<int>[N+1];
    rev_adj = new vector<int>[N+1];
    visited = new bool[N+1];
    components = new vector<int>[N+1];
    int fst, scd;
    for(int i = 0; i < M; i++){
        fin >> fst;
        fin >> scd;
        addEdge(fst, scd);
        addEdgeRev(scd, fst);
    }
    fin.close();
}

void addEdge(int v, int w){
    adj[v].push_back(w);
}

void addEdgeRev(int v, int w)
{
    rev_adj[v].push_back(w);
}

/* #region Kosaraju */
void kosaraju_dfs_1(int x)
{
    visited[x] = true;
    for (int i = 0; i < adj[x].size(); i++)
    {
        if (!visited[adj[x][i]])
            kosaraju_dfs_1(adj[x][i]);
    }
    S.push(x);
}

void kosaraju_dfs_2(int x)
{
    components[numComponents].push_back(x);
    visited[x] = true;
    for (int i = 0; i < rev_adj[x].size(); i++)
    {
        if (!visited[rev_adj[x][i]])
            kosaraju_dfs_2(rev_adj[x][i]);
    }
}

void Kosaraju()
{
    for (int i = 1; i <= N; i++)
    {
        if (!visited[i])
            kosaraju_dfs_1(i);
    }

    for (int i = 1; i <= N; i++)
    {
        visited[i] = false;
    }

    while (!S.empty())
    {
        int v = S.top();
        S.pop();
        if (!visited[v])
        {
            kosaraju_dfs_2(v);
            numComponents++;
        }
    }
}
/* #endregion */

vector<bool> visitedCycle;
vector<bool> onstack;

bool hasCycle(int node, vector<int> adj[])
{
    visitedCycle[node] = true;
    onstack[node] = true;

    for (int neighbour = 0; neighbour < adj[node].size(); neighbour++)
    {
        if (visitedCycle[adj[node][neighbour]] && onstack[adj[node][neighbour]])
        {
            // There is a circle
            return true;
        }
        else if (!visitedCycle[adj[node][neighbour]] && hasCycle(adj[node][neighbour], adj))
        {
            // There is a circle
            return true;
        }
    }
    onstack[node] = false;
    return false;
}

int ComputeMinimumEdges(){
    int edgesCount = 0;
    for (int i = 0; i < N; i++){
        // reached end if component is empty
        if(components[i].empty()){
            break;
        }

        if(components[i].size() == 1){
            edgesCount += 1;
            continue;
        }
        
        //find if component is cyclic
        bool isCyclic = false;
        visitedCycle.assign(N + 1, false);
        onstack.assign(N + 1, false);
        for (int node = 0; node < components[i].size(); node++)
        {
            if (!visitedCycle[components[i][node]])
            {
                vector<int> newAdj[N + 1];
                for (int k = 0; k < components[i].size(); k++){
                    newAdj[components[i][k]] = adj[components[i][k]];
                }

                isCyclic = isCyclic || hasCycle(components[i][node], newAdj);
                if (isCyclic){
                    break;
                }
            }
        }

        //add edges based on result
        if(isCyclic){
            edgesCount += components[i].size();
            cout << edgesCount << "\n";
        }
        else{
            edgesCount += components[i].size() - 1;
            cout << edgesCount << "\n";
        }
    }

    return edgesCount;
}