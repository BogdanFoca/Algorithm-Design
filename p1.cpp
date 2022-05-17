#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("redundant.in");
ofstream fout("redundant.out");

int N;
int M;
int M2;
bool** adjacencyMatrix;

void ReadData();
int TransitiveReduction();
void ComputePathMatrix();

void PrintMatrix(bool** matrix, int size){
    for (int i = 1; i <= size; i++) {
		for (int j = 1; j <= size; j++) {
            cout << matrix[i][j] << " ";
		}
        cout << "\n";
	}
}

int main(){
    ReadData();
    ComputePathMatrix();
    fout << TransitiveReduction();
    fout.close();
    free(adjacencyMatrix);
    return 0;
}

void ReadData(){
    fin >> N;
    fin >> M;
    adjacencyMatrix = new bool*[N + 1];
    for (int i = 1; i <= N; i++){
        adjacencyMatrix[i] = new bool[N + 1];
    }
    int fst, scd;
    for(int i = 1; i < M; i++){
        fin >> fst;
        fin >> scd;
        adjacencyMatrix[fst][scd] = true;
    }
    fin.close();
}

void ComputePathMatrix(){
    for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				adjacencyMatrix[i][j] = (adjacencyMatrix[i][j] || (adjacencyMatrix[i][k] && adjacencyMatrix[k][j]));
			}
		}
	}
}

int TransitiveReduction(){
    int number = 0;
    for (int i = 1; i <= N; ++i){
        if(adjacencyMatrix[i][i]){
            adjacencyMatrix[i][i] = false;
        }
    }

    for (int j = 1; j <= N; ++j){
        for (int i = 1; i <= N; ++i){
            if (adjacencyMatrix[i][j]){
                for (int k = 1; k <= N; ++k){
                    if (adjacencyMatrix[j][k]){
                        adjacencyMatrix[i][k] = false;
                    }
                }
            }
        }
    }
    for (int j = 1; j <= N; ++j){
        for (int i = 1; i <= N; ++i){
            if (adjacencyMatrix[i][j]){
                number++;
            }
        }
    }
    return number;
}