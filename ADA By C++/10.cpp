#include <iostream>
#include <vector>

using namespace std;

struct point {
   long long xCoor, yCoor;
};
long long n {}, lone {}, ltwo {}, rone {}, rtwo {}, neg {1};

void merge(vector<point> &airP, int left, int mid, int right){
    long long leftSize {mid - left + 1};
    long long rightSize {right - mid};
    point leftArr[leftSize], rightArr [rightSize];
    for (int i = 0; i < leftSize; ++i)
        leftArr[i] = airP[left + i];
    for (int i = 0; i < rightSize; ++i)
        rightArr[i] = airP[mid + 1 + i];
    long long iLeft {}, iRight {}, iArr {left};
    while (iLeft < leftSize && iRight < rightSize) {
        if (leftArr[iLeft].xCoor < rightArr[iRight].xCoor) {
            airP[iArr] = leftArr[iLeft];
            ++iLeft;
        }
        else if (leftArr[iLeft].xCoor == rightArr[iRight].xCoor) {
            if (leftArr[iLeft].yCoor <= rightArr[iRight].yCoor) {
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
    long long mid = head + (tail - head) / 2;
    mergeSort(airP, head, mid);
    mergeSort(airP, mid + 1, tail);
    merge(airP, head, mid, tail);
    return;
}

long long imerge(vector<point> &airP, vector<point> &airPP, long long low, long long mid, long long high) {
    long long iArr = low, iLeft = low, iRight = mid + 1;
    long long iCount = 0;
    while (iLeft <= mid && iRight <= high) {
        if (airP[iLeft].yCoor <= airP[iRight].yCoor) {
            airPP[iArr] = airP[iLeft];
            ++iLeft;
        } else {
            airPP[iArr] = airP[iRight];
            ++iRight;
            iCount += (mid - iLeft + 1);
        }
        iArr++;
    }
    while (iLeft <= mid){
        airPP[iArr] = airP[iLeft];
        iLeft++;
        iArr++;
    }
    for (int i = low; i <= high; i++){
        airP[i] = airPP[i];
        //cout << airPP[i].xCoor << airPP[i].yCoor << ' ';
    }//cout << "a\n" << iCount << "a\n";
    return iCount;
}

long long imergesort(vector<point> &airP, vector<point> &airPP, long long low, long long high) {
    if (high == low)
        return 0;
    long long mid = (high + low) / 2;
    long long iCount = 0;
    iCount += imergesort(airP, airPP, low, mid);
    iCount += imergesort(airP, airPP, mid + 1, high);
    iCount += imerge(airP, airPP, low, mid, high);
    //cout << iCount << "b\n";
    return iCount;
}

int main() {
    cin >> n >> lone >> ltwo >> rone >> rtwo;
    if ((lone * rtwo - ltwo * rone) < 0) neg = -1;
    vector <point> airP, airPP;
    airP.resize(n), airPP.resize(n);
    for(int i = 0; i < n; ++i){
        long long x {}, y {};
        cin >> x >> y;
        airP[i].xCoor = (rone * x - rtwo * y) * neg, airP[i].yCoor = (- lone * x + ltwo * y) * neg;
    }
    mergeSort(airP, 0, n - 1);
    //for(int i = 0; i < n; ++i) cout << airP[i].xCoor << " " << airP[i].yCoor << " " << "\n"; 
    
    for (int i = 0; i < n; ++i) airPP[i] = airP[i]; 
    long long ans = imergesort(airP, airPP, 0, n - 1);
    cout << ((n * (n - 1) / 2) - ans) ; 
    return 0;
}