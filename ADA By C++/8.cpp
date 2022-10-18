#include <iostream>
using namespace std;

int count(int start, int end, int l){
    if (start == end){
        ++l;
        return l;
    }
    l = count (start, (end - start) / 2 + start, l);
    for (int i = 0; i < end - start + 1; ++i) ++l;
    for (int i = start; i <= (end - start) / 2 + start; ++i) ++l;
    for (int i = end; i >= (end - start) / 2 + start + 1; --i) ++l;
    l = count ((end - start) / 2 + start + 1, end, l);
    return l;
}

void solve(int start, int end)
{
    if (start == end){
        cout << "PHOTO" << '\n';
        return;
    }
    solve (start, (end - start) / 2 + start);
    for (int i = 0; i < end - start + 1; ++i) cout << "POP " << '\n';
    for (int i = start; i <= (end - start) / 2 + start; ++i) cout << "PLACE " << i << '\n';
    for (int i = end; i >= (end - start) / 2 + start + 1; --i) cout << "PLACE " << i << '\n';
    solve ((end - start) / 2 + start + 1, end);
    return;
}

int main (){
    int n;
    cin >> n;
    int l {n};
    l = count(1, n, l);
    cout << l << '\n';
    for (int i = n; i > 0; --i) cout << "PLACE " << i << '\n';
    solve (1, n);
    return 0;
}
