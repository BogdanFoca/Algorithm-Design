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

list<int> *adj; // An array of adjacency lists
vector<vector<int>> connexParts;

void ReadData();
void GetConnected();
void fillOrder(int v, bool visited[], stack<int> &Stack);
void addEdge(int v, int w);
list<int>* getTranspose();
void DFSUtil(int v, bool visited[], int connexIndex);

void PrintMatrix(bool **matrix, int size)
{
    for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
            cout << matrix[i][j] << " ";
		}
        cout << "\n";
	}
}

int main(){
    ReadData();
    GetConnected();
    fout.close();
    return 0;
}

void ReadData(){
    fin >> N;
    fin >> M;
    int fst, scd;
    for(int i = 0; i < M; i++){
        fin >> fst;
        fin >> scd;
        addEdge(fst, scd);
    }
    fin.close();
}

void GetConnected(){
    stack<int> Stack;

    // Mark all the vertices as not visited (For first DFS)
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++){
        visited[i] = false;
    }

    // Fill vertices in stack according to their finishing times
    for (int i = 0; i < N; i++){
        if (visited[i] == false){
            fillOrder(i, visited, Stack);
        }
    }

    // Create a reversed graph
    list<int> *gr = getTranspose();

    // Mark all the vertices as not visited (For second DFS)
    for (int i = 0; i < N; i++){
        visited[i] = false;
    }

    int i = 0;
    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (visited[v] == false)
        {
            connexParts.push_back(vector<int>());
            DFSUtil(v, visited, i);
            i++;
        }
    }
}

void fillOrder(int v, bool visited[], stack<int> &Stack){
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i){
        if (!visited[*i]){
            fillOrder(*i, visited, Stack);
        }
    }

    // All vertices reachable from v are processed by now, push v
    Stack.push(v);
}

void addEdge(int v, int w){
    adj[v].push_back(w);
}

list<int> *getTranspose(){
    list<int> *g = new list<int>[N];
    for (int v = 0; v < N; v++)
    {
        // Recur for all the vertices adjacent to this vertex
        list<int>::iterator i;
        for (i = adj[v].begin(); i != adj[v].end(); ++i)
        {
            g[*i].push_back(v);
        }
    }
    return g;
}

void DFSUtil(int v, bool visited[], int connexIndex){
    // Mark the current node as visited and print it
    visited[v] = true;
    connexParts[connexIndex].push_back(v);

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i){
        if (!visited[*i]){
            DFSUtil(*i, visited, connexIndex);
        }
    }
}