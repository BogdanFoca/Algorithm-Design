#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

ifstream fin("p2.in");
ofstream fout("p2.out");

struct Edge
{
    int x, y, w, idx;
    bool operator<(Edge e) const
    {
        return w < e.w;
    }
};

int *father, *dis, *backEdge, *ans, *sizes;
bool *mark;
vector<pair<int, int>> *adj;
Edge *edges;

int N;
int M;

void ReadData();

int find(int x)
{
    if (father[x] == x)
        return x;
    return find(father[x]);
}

void merge(Edge e)
{
    int x = find(e.x);
    int y = find(e.y);
    if (x != y)
    {
        if (sizes[x] > sizes[y])
            swap(x, y);
        father[x] = y;
        sizes[y] += sizes[x];
    }
}

int main(){
    ReadData();
    int i;
    for(i = 0; i < N; i++)
    {
        father[i] = i;
        sizes[i] = 1;
    }
}

void ReadData(){
    fin >> N;
    fin >> M;
    father = new int[N];
    dis = new int[N];
    backEdge = new int[N];
    ans = new int[N];
    sizes = new int[N];
    mark = new bool[N];
    adj = new vector<pair<int, int>>[N];
    edges = new Edge[N];
    int fst, scd, w, i;
    for(i = 0; i < M; i++){
        fin >> fst;
        fin >> scd;
        fin >> w;
        edges[i].x = fst;
        edges[i].y = scd;
        edges[i].w = w;
    }
    fin.close();
}
