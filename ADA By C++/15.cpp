#include <iostream>
#include <vector>
#include <algorithm>

struct makeAndEat{
    long long make;
    long long eat;
};

bool mycompare(makeAndEat one, makeAndEat two){
   return one.eat > two.eat;
}

using namespace std;

int main(){
    int N {};
    cin >> N;
    vector <long long> makeTotalTime;
    for (int i = 0; i <= N; ++i) {
        makeTotalTime.push_back(0);
    }
    vector <long long> eatTotalTime;
    for (int i = 0; i <= N; ++i) {
        eatTotalTime.push_back(0);
    }
    vector <long long> firstTime;
    for (int i = 0; i <= N; ++i) {
        firstTime.push_back(0);
    }
    vector <long long> lastTime;
    for (int i = 0; i <= N; ++i) {
        lastTime.push_back(0);
    }
    vector <long long> Ppl;
    for (int i = 0; i <= N; ++i) {
        Ppl.push_back(0);
    }
    for (int i = 1; i <= N; ++i) {
        cin >> Ppl[i];
        vector <makeAndEat> list;
        for (int j = 0; j < Ppl[i]; ++j) {
            makeAndEat cus;
            cin >> cus.make >> cus.eat;
            list.push_back(cus);
        }
        long long makeTotal = 0, maxEat = INT64_MIN;
        sort(list.begin(), list.end(), mycompare);
        for (int j = 0; j < Ppl[i]; ++j) {
            makeTotal += list[j].make;
            if (maxEat < makeTotal + list[j].eat) maxEat = makeTotal + list[j].eat;
        }
        makeTotalTime[i] = maxEat * Ppl[i];
    }
    cout << makeTotalTime[1];
    return 0;
}