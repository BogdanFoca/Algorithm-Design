#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("p3.in");
ofstream fout("p3.out");

int N;
int M;
int** graph;

void ReadData();
int FloydWarshall(int** graph);

int main() {
    ReadData();
    fout << FloydWarshall(graph);
    delete[] graph;
    fout.close();
}

void ReadData() {
    fin >> N;
    fin >> M;
    graph = new int*[N + 1];
    int i, j;
    for (i = 1; i <= N; i++) {
        graph[i] = new int[N + 1];
        for (j = 1; j <= N; j++) {
            graph[i][j] = -1;
        }
    }
    int fst, scd, w;
    for (i = 0; i < M; i++) {
        fin >> fst;
        fin >> scd;
        fin >> w;
        graph[fst][scd] = w;
    }
    fin.close();
}

int FloydWarshall(int** graph) {
    int** dist;
    dist = new int*[N + 1];
    int i, j;
    for (i = 1; i <= N; i++) {
        dist[i] = new int[N + 1];
    }

    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            if (graph[i][j] !=-1) {
                dist[i][j] = graph[i][j];
            } else {
                dist[i][j] = 2147483647;
            }
            if (i == j) {
                dist[i][i] = 2147483647;
            }
        }
    }
    int k;
    for (k = 1; k <= N; k++) {
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= N; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) &&
                    (dist[k][j] != 2147483647 && dist[i][k] != 2147483647)) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    int min = 2147483647;
    for (i = 1; i <= N; i++) {
        if (dist[i][i] < min) {
            min = dist[i][i];
        }
    }
    delete[] dist;
    return min;
}
