#include <limits.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct City {
    int city;
    long long dist;
};

typedef pair <long long, int> node;
vector <vector <City>> points;
int N {}, M {};

long long dijkstra() {
	vector <long long> dist(N + 1, INT64_MAX);
    priority_queue <node, vector <node>, greater <node>> pq;
	dist[0] = 0, dist[1] = 0;
    node tempp;
    pq.push(make_pair(dist[1], 1));
	while(pq.size()){
		int index = pq.top().second;
        pq.pop();
		for (int j = 0; j < points[index].size(); ++j){
            if ((dist[index] + points[index][j].dist) < dist[points[index][j].city] && index != points[index][j].city) {
                dist[points[index][j].city] = dist[index] + points[index][j].dist;
                pq.push(make_pair(dist[points[index][j].city], points[index][j].city));
            }
        }
	}
    long long total {};
    for (int i = 2; i <= N; ++i){
        total += dist[i];
    }
    return total;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	int temp {};
    long long min {INT64_MAX};
    cin >> N >> M;
    points.resize(N + 1);
    City input;
    input.city = -1, input.dist = -1;
    for(int i = 0; i < M; ++i){
        cin >> temp >> input.city >> input.dist;
        points[temp].push_back(input);
    }
    long long tempp {};
    if (N > 1){
        for(int i = 2; i <= N; ++i){
            input.city = i, input.dist = 0;
            points[1].push_back(input);
            tempp = dijkstra();
            if (tempp < min) min = tempp;
            points[1].pop_back();
        }
        cout << min;
    }
    else{
        cout << 0;
    }
	return 0;
}
