#include <iostream>
#include <set>

using namespace std;

int main()
{
    int b = 4, c = 3, d = 8;
    set<int> a{c, d};
    int &x = b;
    a.insert(x);
    for (auto &c : a) {
        cout << c << " ";
    }
    cout << endl;

    cout << *(&x) << endl;

    return 0;
}

