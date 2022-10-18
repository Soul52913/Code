#include <iostream>
#include <vector>

using namespace std;
#define zero 100001

vector<int> ltable, rtable; 

long long merge(vector<int> &arr, int left, int mid, int right){//cout << arr[left] << " " << arr[mid] << " " << arr[right] << "\n";
    int iLeft {mid}, iRight {mid + 1}, min {100001};
    long long pairCount {};
    while (left <= iLeft && iRight <= right) {
        if (arr[iLeft] <= min && arr[iRight] <= min) {
            if (arr[iLeft] <= arr[iRight]){
                min = arr[iRight];
                ++rtable[zero + arr[iRight]];
                pairCount += ltable[zero + arr[iRight] + min] + ltable[zero + arr[iRight] - min];//cout << min << ' ' << pairCount << "a\n";
                ++iRight;
            }
            else {
                min = arr[iLeft];
                ++ltable[zero + arr[iLeft]];
                pairCount += rtable[zero + arr[iLeft] + min] + rtable[zero + arr[iLeft] - min]; //cout << arr[iLeft] << ' '  << pairCount << "b\n";
                --iLeft;
            }
        }
        else {
            if (arr[iLeft] <= arr[iRight]){
                if (arr[iLeft] <= min){
                    ++rtable[zero + arr[iRight]];
                    pairCount += ltable[zero + arr[iRight] + min] + ltable[zero + arr[iRight] - min];//cout << arr[iRight] << ' '  << pairCount << "c\n";
                    ++iRight;
                }
                else {
                    ++ltable[zero + arr[iLeft]]; 
                    pairCount += rtable[zero + arr[iLeft] + min] + rtable[zero + arr[iLeft] - min];//cout << arr[iLeft] << ' '  << pairCount << "d\n";
                    --iLeft;
                }
            }
            else {
                if (arr[iRight] <= min){
                    ++ltable[zero + arr[iLeft]]; 
                    pairCount += rtable[zero + arr[iLeft] + min] + rtable[zero + arr[iLeft] - min];//cout << arr[iLeft] << ' '  << pairCount << "e\n";
                    --iLeft;
                }
                else {
                    ++rtable[zero + arr[iRight]];
                    pairCount += ltable[zero + arr[iRight] + min] + ltable[zero + arr[iRight] - min];//cout << arr[iRight] << ' '  << pairCount << "f\n";
                    ++iRight;
                }
            }
        }
    }
    if (iLeft < left) {
        min = arr[iRight];
        while (iRight <= right) {
            if (arr[iRight] < min)
                min = arr[iRight];
            pairCount += ltable[zero + arr[iRight] + min] + ltable[zero + arr[iRight] - min];//cout << pairCount << "g\n";
            ++iRight;
        }
    }
    else{
        min = arr[iLeft];
        while (iLeft >= left) {
            if (arr[iLeft] < min)
                min = arr[iLeft];
            pairCount += rtable[zero + arr[iLeft] + min] + rtable[zero + arr[iLeft] - min];//cout << pairCount << "h\n";
            --iLeft;
        }
    }
    for (int i = left; i <= right; ++i){
        ltable[zero + arr[i]] = 0, rtable[zero + arr[i]] = 0;
    }
    return pairCount;
}

long long  mergeSort(vector<int> &arr, int head, int tail){
    if (head >= tail)
        return 0;
    int mid = (head + tail) / 2;
    long long pairCount {};
    pairCount += mergeSort(arr, head, mid);
    pairCount += mergeSort(arr, mid + 1, tail);
    pairCount += merge(arr, head, mid, tail); 
    return pairCount;
}

int main() {
    int n {};
    cin >> n;
    vector <int> arr;
    ltable.resize(300001), rtable.resize(300001);
    arr.resize(n);
    for(int i = 0; i < n; ++i){
        int ai {}; cin >> ai;
        arr[i] = ai;
    }
    cout << mergeSort(arr, 0, n - 1);
    //for(int i = 0; i < n; ++i) cout << arr[i] << "\n";  cout << "a\n";
    return 0;
}