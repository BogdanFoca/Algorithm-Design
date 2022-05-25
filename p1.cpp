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

vector<int> *adj; // An array of adjacency lists
vector<int> *undirectedAdj;
vector<int> *components;

void ReadData();
void addEdge(int v, int w);
void addEdgeUndirected(int v, int w);
bool hasCycle(int node, int adj[]);
int ComputeMinimumEdges();
void connectedComponents();

int main()
{
    ReadData();
    connectedComponents();
    fout << ComputeMinimumEdges();
    fout.close();
    return 0;
}

void ReadData()
{
    fin >> N;
    fin >> M;
    adj = new vector<int>[N+1];
    undirectedAdj = new vector<int>[N + 1];
    components = new vector<int>[N+1];
    int fst, scd;
    for(int i = 0; i < M; i++)
    {
        fin >> fst;
        fin >> scd;
        addEdge(fst, scd);
        addEdgeUndirected(fst, scd);
    }
    fin.close();
}

void addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void addEdgeUndirected(int v, int w)
{
    undirectedAdj[v].push_back(w);
    undirectedAdj[w].push_back(v);
}

/* #region Weakly Connected Parts */
void DFSConnected(int v, bool visited[], int index)
{
    // Mark the current node as visited and add it to component
    visited[v] = true;
    components[index].push_back(v);

    // Recur for all the vertices adjacent to this vertex
    for (int i = 0; i < undirectedAdj[v].size(); ++i)
    {
        if (!visited[undirectedAdj[v][i]])
        {
            DFSConnected(undirectedAdj[v][i], visited, index);
        }
    }
}

void connectedComponents()
{
    // Mark all the vertices as not visited
    bool *visited = new bool[N];
    for (int v = 1; v <= N; v++)
    {
        visited[v] = false;
    }

    int i = 0;
    for (int v = 1; v <= N; v++)
    {
        if (!visited[v])
        {
            DFSConnected(v, visited, i);
            i++;    //increment component index
        }
    }
    delete[] visited;
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
            // There is a cycle
            return true;
        }
        else if (!visitedCycle[adj[node][neighbour]] && hasCycle(adj[node][neighbour], adj))
        {
            // There is a cycle
            return true;
        }
    }
    onstack[node] = false;
    return false;
}

int ComputeMinimumEdges(){
    int edgesCount = 0;
    for (int i = 0; i < N; i++)
    {
        // reached end if component is empty
        if(components[i].empty())
        {
            break;
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
                for (int k = 0; k < components[i].size(); k++)
                {
                    newAdj[components[i][k]] = adj[components[i][k]];
                }

                isCyclic = isCyclic || hasCycle(components[i][node], newAdj);

                if (isCyclic)
                {
                    break;
                }
            }
        }

        //add edges based on result
        if(isCyclic)
        {
            edgesCount += components[i].size();
        }
        else
        {
            edgesCount += components[i].size() - 1;
        }
    }

    return edgesCount;
}