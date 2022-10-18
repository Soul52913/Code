#include <iostream>
#include <vector>
using namespace std;
 
long long Sub (vector<long long> nums, long long n)
{
    long long temp = nums[0];
    long long Max = nums[0];
    for (long long i = 1; i < n; ++i) {
        temp = max(nums[i], nums[i] + temp);
        Max = max(Max, temp);
    }
    return Max;
}

int main(){
    long long n, num;
    cin >> n;
    vector <long long> arr;
    arr.reserve(n);
    for(long long i = 0; i < n; ++i) {
        cin >> num;
        arr.push_back(num);
    }
    long long ans {Sub(arr, n)};
    cout << ans;
    return 0;
}