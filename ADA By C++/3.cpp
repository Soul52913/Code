#include <string>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct huffNode {
    int index;
    long long freq;
    string code;
    bool mark;
    struct huffNode *left;
    struct huffNode *right;
};

struct compare {
    bool operator()(huffNode *a, huffNode *b){
        return (a->freq > b->freq);
    }
};

huffNode * leftRotate(huffNode *cursor){
    huffNode * y = cursor->right;
    if(y->left != NULL){
            cursor->right = y->left;
    }
    else
            cursor->right = NULL;
    y->left = cursor;
    return y;
}

void coding(huffNode *cursor, string pwd) {
    if (!cursor) return;
    if (!cursor->left || !cursor->right) cursor->code = pwd;
    coding(cursor->left, pwd + "0");
    coding(cursor->right, pwd + "1");
}

int main() {
    int N {};
    cin >> N;
    vector <huffNode *> print;
    priority_queue <huffNode *, vector <huffNode *>, compare> save;
    for(int i = 0; i < N; ++i){
        huffNode *temp = new huffNode;
        temp->index = i, temp->code = "", temp->mark = 0, temp->left = NULL, temp->right = NULL;
        cin >> temp->freq;
        save.push(temp);
        print.push_back(temp);
    } 
    while (save.size() != 1) {
        huffNode *left = save.top();
        save.pop();
        huffNode *right = save.top();
        save.pop();
        //cout << left->freq << ' ' << right->freq << endl;
        huffNode *temp = new huffNode;
        temp->index = -1, temp->code = "", temp->mark = 1, temp->left = left, temp->right = right;
        temp->freq = left->freq + right->freq;
        save.push(temp);
        //cout << temp->left->freq << ' ' << temp->right->freq << endl;
    }
    huffNode *root = save.top();
    //for (int i = 0; i < N / 5; ++i) if(root->right) root = leftRotate (root);
    coding(root, "");
    for(int i = 0; i < N; ++i) cout << print[i]->code << endl;
    if (N == 1) cout << 0;
    return 0;
}