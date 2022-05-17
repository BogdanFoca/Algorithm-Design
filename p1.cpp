#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("redundant.in");
ofstream fout("redundant.out");

int N;
int M;
bool** adjacencyMatrix;
bool** pathMatrix;

void ReadData();
void TransitiveReduction();
void ComputePathMatrix();

void PrintMatrix(bool** matrix, int size){
    for (int i = 1; i < size; i++) {
		for (int j = 1; j < size; j++) {
            cout << matrix[i][j] << " ";
		}
        cout << "\n";
	}
}

int main(){
    ReadData();
    PrintMatrix(adjacencyMatrix, N);
    ComputePathMatrix();
    TransitiveReduction();
}

void ReadData(){
    fin >> N;
    fin >> M;
    adjacencyMatrix = new bool*[N];
    for (int i = 0; i < N; i++){
        adjacencyMatrix[i] = new bool[N];
    }
    int fst, scd;
    for(int i = 0; i < M; i++){
        fin >> fst;
        fin >> scd;
        adjacencyMatrix[fst][scd] = true;
    }
}

void ComputePathMatrix(){
    /*pathMatrix = new bool*[N];
    for (int i = 0; i < N; i++){
        pathMatrix[i] = new bool[N];
    }*/
    for (int k = 1; k < M; k++) {
		
		for (int i = 1; i < M; i++) {
		
			for (int j = 1; j < M; j++) {

				adjacencyMatrix[i][j] = (adjacencyMatrix[i][j] || (adjacencyMatrix[i][k] && adjacencyMatrix[k][j]));
			}
		}
	}
}

void TransitiveReduction(){
    for(int i = 0; i < N; i++){
        adjacencyMatrix[i][i] = false;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(adjacencyMatrix[j][i]){
                for(int k = 0; k < N; k++){
                    if(adjacencyMatrix[i][k]){
                        adjacencyMatrix[j][k] = false;
                    }
                }
            }
        }
    }
}