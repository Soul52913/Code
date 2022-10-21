#include <iostream>
#include <vector>
#include <algorithm>

struct makeAndEat{
    long long make;
    long long eat;
};

struct makeLastEat{
    long long make;
    long long eat;
    long long ppl;
};

bool compareone(makeAndEat one, makeAndEat two){
    return one.eat > two.eat;
}

bool comparetwo(makeLastEat one, makeLastEat two){
    return one.make * two.ppl < two.make * one.ppl;
}

using namespace std;

int main(){
    int N {};
    cin >> N;
    vector <makeLastEat> makeTotalTime;
    for (int i = 0; i <= N; ++i) {
        makeLastEat temp;
        temp.make = 0, temp.eat = 0, temp.ppl = 0;
        makeTotalTime.push_back(temp);
    }
    for (int i = 1; i <= N; ++i) {
        long long ppl, totalmake {};
        cin >> ppl;
        vector <makeAndEat> list;
        for (int j = 0; j < ppl; ++j) {
            makeAndEat cus;
            cin >> cus.make >> cus.eat;
            list.push_back(cus);
            totalmake += cus.make;
        }
        long long makeTotal = 0, maxEat = INT64_MIN;
        sort(list.begin(), list.end(), compareone);
        for (int j = 0; j < ppl; ++j) {
            makeTotal += list[j].make;
            if (maxEat < makeTotal + list[j].eat) maxEat = makeTotal + list[j].eat;
        }
        makeTotalTime[i].make = totalmake;
        makeTotalTime[i].eat = maxEat - totalmake;
        makeTotalTime[i].ppl = ppl;
    }
    sort (makeTotalTime.begin() + 1, makeTotalTime.end(), comparetwo);
    long long ans {}, timePast {};
    for (int i = 1; i <= N; ++i){
        timePast += makeTotalTime[i].make;
        ans +=  (timePast + makeTotalTime[i].eat) * makeTotalTime[i].ppl;
    }
    cout << ans;
    return 0;
}