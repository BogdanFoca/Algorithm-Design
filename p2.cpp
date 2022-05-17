#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("cicluri.in");
ofstream fout("cicluri.out");

int N;
int M;
int** graph;

void ReadData();

void PrintMatrix(int** matrix, int size){
    for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
            cout << matrix[i][j] << " ";
		}
        cout << "\n";
	}
}

int main(){
    ReadData();
    free(graph);
    fout.close();
}

void ReadData(){
    fin >> N;
    fin >> M;
    graph = new int*[N + 1];
    for (int i = 1; i <= N; i++){
        graph[i] = new int[N + 1];
    }
    int fst, scd, w;
    for(int i = 0; i < M; i++){
        fin >> fst;
        fin >> scd;
        fin >> w;
        graph[fst][scd] = w;
    }
    fin.close();
}