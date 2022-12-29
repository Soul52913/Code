#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    long long dist;
    int start;
    int end;
};

vector <Edge> Edges;

int N {}, M {};

int main() {
	int temp {};
    cin >> N >> M;
    Edges.resize(M);
    vector <vector <long long>> matrix;
    matrix.resize(M + 3 * N);
    vector <long long> row;
    row.resize(N + M);
    for (int i = 0; i < M + 3 * N; ++i) {
        matrix.push_back(row);
    }
    Edge input;
    for (int i = 0; i < M; ++i) {
        cin >> input.start >> input.end >> input.dist;
        Edges.push_back(input);
    }
    vector <long long> out;
    out.resize(M + 3 * N);
	for (int i = 0; i < M; ++i) {
        int start = Edges[i].start, end = Edges[i].end;
        matrix[start - 1][i] = -1;
        matrix[end - 1][i] = 1;
        matrix[start - 1 + N][i] = 1;
        matrix[end - 1 + N][i] = -1;
        matrix[start - 1 + N * 2][i] = 1;
        matrix[i + N * 3][i] = 10000;
        matrix[i + N * 3][M + start - 1] = 1;
        matrix[i + N * 3][M + end - 1] = -1;
        out[i + N * 3] = 9999;
        if (start == 1) {
            out[start - 1] = -1;
            out[start - 1 + N] = 1;
            out[start - 1 + N * 2] = 1;
        }
        else if (start == N) {
            out[start - 1] = 1;
            out[start - 1 + N] = -1;
            out[start - 1 + N * 2] = 0;
        }
        else {
            out[start - 1] = 0;
            out[start - 1 + N] = 0;
            out[start - 1 + N * 2] = 1;
        }
    }
	return 0;
}