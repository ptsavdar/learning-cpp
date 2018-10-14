//
// Created by panos on 18/06/18.
//

#include <iostream>
#include <vector>
using namespace std;

void print(const string &label, const vector<int>& values)
{
    cout << label << flush;
    for (int v : values)
    {
        cout << v << " " << flush;
    }
    cout << endl;
}

void fibonacci(int x, int y, vector<int>& v, int n)
{
    v.push_back(x);
    v.push_back(y);
    int last = y, prev = x;
    for (unsigned int i = 2; i < n - 1; ++i)
    {
        int next = last + prev;
        if (next < last)
            return;
        v.push_back(next);
        prev = last;
        last = next;
    }
}

void fibrec(vector<int> &v, int cur, int max)
{
    if (cur < max) {
        v.push_back(v.at(cur - 1) + v.at(cur - 2));
        fibrec(v, cur + 1, max);
    }
}

void fibonacci_rec(int x, int y, vector<int> & v, int n)
{
    v.push_back(x);
    v.push_back(y);
    fibrec(v, 2, n);
}



int main() {
    vector<int> v, q;

    fibonacci(1, 2, v, 10);
    fibonacci_rec(1, 2, q, 10);

    print("Fibonaccis ite: ", v);
    print("Fibonaccis req: ", q);

    return 0;
}
