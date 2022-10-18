#include <iostream>
#include <vector>

using namespace std;

struct point {
   long long xCoor, yCoor;
};
long long n {}, lone {}, ltwo {}, rone {}, rtwo {}, neg {1};

void merge(vector<point> &airP, int left, int mid, int right){
    int leftSize {mid - left + 1};
    int rightSize {right - mid};
    point leftArr[leftSize], rightArr [rightSize];
    for (int i = 0; i < leftSize; ++i)
        leftArr[i] = airP[left + i];
    for (auto j = 0; j < rightSize; ++j)
        rightArr[j] = airP[mid + 1 + j];
    int iLeft {}, iRight {}, iArr {left};
    while (iLeft < leftSize && iRight < rightSize) {
        if ((rtwo * leftArr[iLeft].xCoor - rone * leftArr[iLeft].yCoor) * neg < 
        (rtwo * rightArr[iRight].xCoor - rone * rightArr[iRight].yCoor) * neg) {
            airP[iArr] = leftArr[iLeft];
            ++iLeft;
        }
        else if ((rtwo * leftArr[iLeft].xCoor - rone * leftArr[iLeft].yCoor) * neg == 
        (rtwo * rightArr[iRight].xCoor - rone * rightArr[iRight].yCoor) * neg) {
            if ((- ltwo * leftArr[iLeft].xCoor + lone * leftArr[iLeft].yCoor) * neg <=
             (- ltwo * rightArr[iRight].xCoor + lone * rightArr[iRight].yCoor) * neg) {
                airP[iArr] = leftArr[iLeft];
                ++iLeft;
            } else {
                airP[iArr] = rightArr[iRight];
                ++iRight;
            }
        }
        else {
            airP[iArr] = rightArr[iRight];
            ++iRight;
        }
        iArr++;
    }
    while (iLeft < leftSize) {
        airP[iArr] = leftArr[iLeft];
        iLeft++;
        iArr++;
    }
    while (iRight < rightSize) {
        airP[iArr] = rightArr[iRight];
        iRight++;
        iArr++;
    }
    return;
}

void mergeSort(vector<point> &airP, int head, int tail){
    if (head >= tail)
        return;
    int mid = head + (tail - head) / 2;
    mergeSort(airP, head, mid);
    mergeSort(airP, mid + 1, tail);
    merge(airP, head, mid, tail);
    return;
}

int imerge(vector<point> &airP, vector<point> &airPP, int low, int mid, int high) {
    int iArr = low, iLeft = low, iRight = mid + 1;
    int notiCount = 0, total = 0;
    while (iLeft <= mid && iRight <= high) {
        if ((- ltwo * airP[iLeft].xCoor + lone * airP[iLeft].yCoor) * neg <=
         (- ltwo * airP[iRight].xCoor + lone * airP[iRight].yCoor) * neg) {
            airPP[iArr] = airP[iLeft];
            ++iLeft;
            ++notiCount;
        } else {
            airPP[iArr] = airP[iRight];
            ++iRight;
            total += notiCount;
        }
        iArr++;
    }
    if (iLeft > mid) total += (notiCount * (high - iRight + 1));
    while (iLeft <= mid){
        airPP[iArr] = airP[iLeft];
        iLeft++;
        iArr++;
    }
    for (int i = low; i <= high; i++){
        airP[iLeft] = airPP[iLeft];
    }
    return total;
}

int imergesort(vector<point> &airP, vector<point> &airPP, int low, int high) {
    if (high == low)
        return 0;
    int mid = low + (high - low) / 2;
    int notiCount = 0;
    notiCount += imergesort(airP, airPP, low, mid); //cout << notiCount << '\n';
    notiCount += imergesort(airP, airPP, mid + 1, high); //cout << notiCount << '\n';
    notiCount += imerge(airP, airPP, low, mid, high); //cout << notiCount << '\n';
    return notiCount;
}

int main() {
    cin >> n >> lone >> ltwo >> rone >> rtwo;
    if ((lone * rtwo - ltwo * rone) < 0) neg = -1;
    vector <point> airP, airPP;
    airP.resize(n), airPP.resize(n);
    for(int i = 0; i < n; ++i){
        int x {}, y {};
        cin >> airP[i].xCoor >> airP[i].yCoor;
    }
    mergeSort(airP, 0, n - 1);
    //for(int i = 0; i < n; ++i) cout << airP[i].xCoor << " " << airP[i].yCoor << " " << "\n"; 
    
    for (int i = 0; i < n; ++i) airPP[i] = airP[i]; 
    cout << imergesort(airP, airPP, 0, n - 1);
    return 0;
}