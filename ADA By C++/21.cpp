#include<bits/stdc++.h>
#include <limits.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct City {
    int city;
    long long dist;
    long long cost;
};

struct Node {
    long long dist;
    long long cost;
    int city;
};

struct cmp {
    bool operator()(Node a, Node b) {
        if (a.dist == b.dist)
            return a.cost > b.cost;
        else
            return a.dist > b.dist; 
    }
};

vector <vector <City>> points;
int N {}, M {};

long long prim(){
	priority_queue <Node, vector <Node>, cmp> pq;
	vector<long long> keyD(N, INT64_MAX);
	vector<long long> keyMaxD(N, INT64_MIN);
	vector<long long> keyC(N, INT64_MAX);
	vector<int> parent(N, -1);
	vector<bool> visited(N, false);
    Node node = {0, 0, 0};
	pq.push(node);
	keyD[0] = 0;
    keyMaxD[0] = 0;
    keyC[0] = 0;
	while (!pq.empty())	{
		int c = pq.top().city;
        long long cc = pq.top().cost;
        //cout << c << endl;
		pq.pop();
		if(visited[c])
			continue;
		visited[c] = true; //for(auto next : points[c])
        keyC[c] = cc;
		for (int i = 0; i < points[c].size(); ++i) {
			int toC {points[c][i].city};
			long long dist {points[c][i].dist};
            long long cost {points[c][i].cost};
			if (!(visited[toC]) && keyD[toC] >= dist){
                if (dist > keyMaxD[c]){
                    keyMaxD[toC] = dist;
                    keyC[toC] = cost;
                }
                else if (dist == keyMaxD[c]) {
                    keyMaxD[toC] = dist;
                    keyC[toC] = cost + keyC[c];
                }
                else {
                    keyMaxD[toC] = keyMaxD[c];
                    keyC[toC] = keyC[c];
                }
				keyD[toC] = dist;
                node.city = toC, node.dist = keyD[toC], node.cost = keyC[toC];
                //cout << node.city << " " << node.dist << endl;
				pq.push(node);
				parent[toC] = c;
			}
            //for (int i = 0; i < N; ++i){cout << keyD[i] << " ";}
		    //cout << "a" << endl;
		}//cout << "b" << endl;
	}
    long long min = {};
	for (int i = 0; i < N; ++i)
        min += keyC[i];
    return min;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	int temp {};
    cin >> N >> M;
    points.resize(N + 1);
    City input;
    for(int i = 0; i < M; ++i){
        cin >> temp >> input.city >> input.dist >> input.cost;
        points[temp].push_back(input);
        int tempp = temp;
        temp = input.city, input.city = tempp;
        points[temp].push_back(input);
    }
    cout << prim();
	return 0;
}