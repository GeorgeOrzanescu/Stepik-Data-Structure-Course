#include <iostream>
#include <deque>

using namespace std;

void printDeque(deque<int> &d)
{
    for (int i = 0; i < d.size(); i++)
    {
        cout << d[i] << " ";
    }
    cout << endl;
}

int main()
{

    deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.push_front(0);
    d.push_front(-1);

    printDeque(d);

    d.pop_back();
    d.pop_front();

    printDeque(d);
    return 0;
}