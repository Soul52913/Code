#include <limits.h>
#include <iostream>
#include <vector>

using namespace std;

struct City {
    int city;
    int dist;
};

struct Point {
    vector <City> cities;
};

vector <Point> points;
int N {}, M {};

int minDistance(vector <int> &dist, vector <bool> &inSmallest){
	int min {INT_MAX}, minI {};
	for (int i = 1; i <= N; ++i)
		if (inSmallest[i] == false && dist[i] <= min)
			min = dist[i], minI = i;
	return minI;
}

int dijkstra() {
    int total {};
	vector <int> dist(N + 1, INT_MAX);
	vector <bool> inSmallest(N + 1, false);
	dist[0] = 0, dist[1] = 0;
	for (int i = 0; i < N - 1; ++i) {
		int index = minDistance(dist, inSmallest);
		inSmallest[index] = true;
		for (int j = 0; j < points[index].cities.size(); ++j)
			if (!inSmallest[points[index].cities[j].city] && points[index].cities[j].dist && dist[index] != INT_MAX && dist[index] + points[index].cities[j].dist < dist[points[index].cities[j].city])
				dist[points[index].cities[j].city] = dist[index] + points[index].cities[j].dist;
	}
    for (int i = 1; i <= N; ++i){
        total += dist[i];
        cout << dist[i] << endl;
    }
        cout << "AA" << endl;
    return total;
}

int main() {
	int temp {}, min {INT_MAX};
    City input;
    Point first;
    points.push_back(first);
    cin >> N >> M;
    points.resize(N + 1);
    vector <vector <int>> inputs;
    vector <int> line (3, 0);
    for(int i = 0; i < M; ++i){
        cin >> line[0] >> line[1] >> line[2];
        inputs.push_back(line);
    }
    for(int i = 0; i < M; ++i){
        int change = inputs[i][2];
        inputs[i][2] = 0;
        temp = dijkstra();
        if (temp < min) min = temp;
        cout << temp << endl;
        inputs[i][2] = change;
    }
    cout << min;
	return 0;
}
